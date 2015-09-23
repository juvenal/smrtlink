/*
 * Socket.cpp
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <asio.hpp>
#include "Socket.h"
#include "../Types.h"
#include "../device/Host.h"
#include "Packet.h"

Socket::Socket(asio::io_service& io_service, short dst_port, short src_port) :
		socket_(io_service) {

	local_endpoint_ = asio::ip::udp::endpoint(
			asio::ip::address::from_string("192.168.0.3"), src_port); //a
	remote_endpoint_ = asio::ip::udp::endpoint(
			asio::ip::address_v4::from_string("255.255.255.255"), dst_port);
	broadcast_endpoint_ = asio::ip::udp::endpoint(
			asio::ip::address_v4::from_string("255.255.255.255"), dst_port);
	asio::ip::address_v4 local_addr = asio::ip::address_v4::from_string(
			"192.168.0.3");

	socket_.open(asio::ip::udp::v4());
	socket_.bind(local_endpoint_); //TODO reuse Address

	//socket_.set_option(asio::ip::multicast::outbound_interface(local_addr)); // TODO broadcast outbound interface
	socket_.set_option(asio::socket_base::broadcast(true));
	socket_.set_option(asio::socket_base::reuse_address(true));

}

Socket::~Socket() {
// TODO Auto-generated destructor stub
}
void Socket::send(bytes data) {

	unsigned char * a = &data[0];

	socket_.async_send_to(asio::buffer(a, data.size()), broadcast_endpoint_,
			[this](asio::error_code ec, std::size_t bytes_sent)
			{
				listen();
			});

	printf("Send\n");

}

void Socket::listen() {
	socket_.async_receive_from(asio::buffer(data_, max_length),
			remote_endpoint_,
			[this](asio::error_code ec, std::size_t bytes_recvd)
			{
				if (ec || bytes_recvd == 0) {
					listen();
				} else {
					printf("Receive %s\n", data_);
					bytes b = { 255, 255, 0, 0};
					Host h = Host();
					Packet p = Packet(Packet::DISCOVERY);
					p.setBody(b);
					p.setHostMac(h.getMac());
					bytes a = p.getBytes();
					p.encode(a);
					send(a);
				}
			});

	printf("Listen\n");

}
