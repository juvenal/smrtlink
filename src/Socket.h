/*
 * Socket.h
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <asio.hpp>
#include "Packet.h"
#include "Types.h"

#define MAX_LENGTH 1024

class Socket {
public:
	Socket(asio::io_service&);
	virtual ~Socket() {
	}
	void init(short, short);
	void send(bytes);
	void listen();
	int (*callback)(Packet)=[](Packet a) {
		return 0;
	};

private:
	asio::ip::udp::socket send_socket_;
	asio::ip::udp::socket receive_socket_;
	//asio::ip::udp::resolver resolver;
	asio::ip::udp::endpoint broadcast_endpoint_;
	asio::ip::udp::endpoint remote_endpoint_;
	asio::ip::udp::endpoint wildcard_endpoint_;
	asio::ip::udp::endpoint local_endpoint_;
	bytes data = bytes(MAX_LENGTH);

};

#endif /* SOCKET_H_ */
