/*
 * Socket.cpp
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <asio.hpp>
#include "Socket.h"
#include "../Types.h"

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

	//socket_.open(asio::ip::udp::v4());

	//socket_.set_option(asio::ip::multicast::outbound_interface(local_addr)); // TODO broadcast outbound interface
	socket_.set_option(asio::socket_base::broadcast(true));
	socket_.set_option(asio::socket_base::reuse_address(true));

}

Socket::~Socket() {
// TODO Auto-generated destructor stub
}
void Socket::send(bytes data) {

	unsigned char * a = &data[0];
	/*socket_.async_send_to(asio::buffer(a, data.size()), broadcast_endpoint_,
	 [this](asio::error_code ec, std::size_t bytes_sent)
	 {
	 listen();
	 });
	 */
	remote_endpoint_ = broadcast_endpoint_;
	printf("Send\n");
	socket_.send_to(asio::buffer(a, data.size()), remote_endpoint_);

	char reply[max_length];
	size_t reply_length = socket_.receive_from(asio::buffer(reply, max_length),
			remote_endpoint_);
	printf("Received %d\n", reply_length);

	reply_length = socket_.receive_from(asio::buffer(reply, max_length),
			remote_endpoint_);
	printf("Received %d\n", reply_length);
//asio::buffer(data_, length)

}

void Socket::listen() {
	socket_.async_receive_from(asio::buffer(data_, max_length),
			remote_endpoint_,
			[this](asio::error_code ec, std::size_t bytes_recvd)
			{
				listen();

				if (!ec && bytes_recvd > 0)
				{
					printf("Receive %s\n", data_);
					bytes a = {72, 97, 108, 108, 111, 32, 87, 101, 108, 116, 33};
					send(a); //bytes_recvd
				}

			});

	printf("Listen\n");

}
