/*
 * Socket.h
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <boost/asio.hpp>
#include "Packet.h"
#include "Types.h"

#define SRC_PORT 29809
#define DST_PORT 29808

#define MAX_LENGTH 1024

class Socket {
public:
	Socket(boost::asio::io_service&);
	virtual ~Socket() {
	}
	void init(short, short);
	void send(Packet);
	void listen();
	void setHostIp(ipAddr);
	std::function<int(Packet)> callback = [](Packet a) {
		return 0;
	};

private:
	boost::asio::ip::udp::socket send_socket_;
	boost::asio::ip::udp::socket receive_socket_;
	boost::asio::ip::udp::endpoint broadcast_endpoint_;
	boost::asio::ip::udp::endpoint remote_endpoint_;
	boost::asio::ip::udp::endpoint wildcard_endpoint_;
	boost::asio::ip::udp::endpoint local_endpoint_;
	boost::asio::deadline_timer timer;
	bytes data = bytes(MAX_LENGTH);
	ipAddr local_ip;
	int initialized = 0;

};

#endif /* SOCKET_H_ */
