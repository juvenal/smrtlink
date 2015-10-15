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

#define SRC_PORT 29809
#define DST_PORT 29808

#define MAX_LENGTH 1024

class Socket {
public:
	Socket(asio::io_service&);
	virtual ~Socket() {
	}
	void init(short, short);
	void send(bytes);
	void listen();
	void setHostIp(ipAddr);
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
	ipAddr local_ip;

};

#endif /* SOCKET_H_ */
