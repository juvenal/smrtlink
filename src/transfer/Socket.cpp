/*
 * Socket.cpp
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <asio.hpp>
#include "Socket.h"
#include "../Types.h"
#include "../Utils.h"
#include "../device/Host.h"
#include "Packet.h"

Socket::Socket(asio::io_service& io_service) :
		send_socket_(io_service), receive_socket_(io_service) {
}

void Socket::init(short dst_port, short src_port) {

	wildcard_endpoint_ = asio::ip::udp::endpoint(
			asio::ip::address::from_string("0.0.0.0"), src_port);
	local_endpoint_ = asio::ip::udp::endpoint(
			asio::ip::address::from_string("192.168.0.3"), src_port);
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
	receive_socket_.async_receive_from(asio::buffer(data_, MAX_LENGTH),
			remote_endpoint_,
			[this](asio::error_code ec, std::size_t bytes_recvd)
			{
				if (ec || bytes_recvd == 0) {
					listen();
				} else {
					data_.resize(bytes_recvd);
					Packet p = Packet(Packet::DISCOVERY);
					p.encode(data_);
					p.parse(data_);
					datasets l = p.getPayload();
					utils::printSets(l);

					/*
					 sleep(1);
					 bytes b = {255, 255, 0, 0};
					 Host h = Host();
					 p = Packet(Packet::DISCOVERY);
					 p.setBody(b);
					 p.setHostMac(h.getMac());
					 bytes a = p.getBytes();
					 p.encode(a);
					 send(a);
					 */
					listen();
				}
			});

	//printf("Listen\n");

}
