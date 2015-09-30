/*
 * Socket.cpp
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <array>
#include <unistd.h>
#include <asio.hpp>
#include "Socket.h"
#include "Packet.h"
#include "Types.h"
#include "Utils.h"
#include "Options.h"
#include "Host.h"

Socket::Socket(asio::io_service& io_service) :
		send_socket_(io_service), receive_socket_(io_service) {
}
//, resolver(				io_service)
void Socket::init(short dst_port, short src_port) {

	if (options.flags & FLAG_REVERSE) {
		short p = dst_port;
		dst_port = src_port;
		src_port = p;
	}

	printf("IP:\t");
	utils::print(local_ip);
	printf("\n");

	wildcard_endpoint_ = asio::ip::udp::endpoint(
			asio::ip::address_v4::from_string("0.0.0.0"), src_port);
	local_endpoint_ = asio::ip::udp::endpoint(asio::ip::address_v4(local_ip),
			src_port);
	broadcast_endpoint_ = asio::ip::udp::endpoint(
			asio::ip::address_v4::from_string("255.255.255.255"), dst_port);

	send_socket_.open(asio::ip::udp::v4());
	send_socket_.set_option(asio::socket_base::broadcast(true));
	send_socket_.set_option(asio::socket_base::reuse_address(true));
	send_socket_.bind(local_endpoint_); //TODO reuse Address

	receive_socket_.open(asio::ip::udp::v4());
	receive_socket_.set_option(asio::socket_base::broadcast(true));
	receive_socket_.set_option(asio::socket_base::reuse_address(true));
	receive_socket_.bind(wildcard_endpoint_); //TODO reuse Address

}

void Socket::setHostIp(inetAddr ip) {
	local_ip=ip;
}

void Socket::send(bytes data) {
	unsigned char * a = &data[0];
	send_socket_.async_send_to(asio::buffer(a, data.size()),
			broadcast_endpoint_,
			[this](asio::error_code ec, std::size_t bytes_sent)
			{
				listen();
			});
}

void Socket::listen() {
	data.resize(MAX_LENGTH);
	receive_socket_.async_receive_from(asio::buffer(data, MAX_LENGTH),
			remote_endpoint_,
			[this](asio::error_code ec, std::size_t bytes_recvd)
			{
				if (ec || bytes_recvd == 0) {
					listen();
				} else {
					data.resize(bytes_recvd);
					Packet p = Packet(Packet::READ);
					p.encode(data);
					p.parse(data);
					datasets l = p.getPayload();
					if(!callback(p)) {
						listen();
					}
				}
			});
}
