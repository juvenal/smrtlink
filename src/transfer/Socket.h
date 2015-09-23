/*
 * Socket.h
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <asio.hpp>
#include "../Types.h"

class Socket {
public:
	Socket(asio::io_service&, short, short);
	virtual ~Socket();
	void send(bytes);
	void listen();
private:
	asio::ip::udp::socket socket_;
	asio::ip::udp::endpoint broadcast_endpoint_;
	asio::ip::udp::endpoint remote_endpoint_;
	asio::ip::udp::endpoint local_endpoint_;
	enum {
		max_length = 1024
	};
	char data_[max_length];

};

#endif /* SOCKET_H_ */
