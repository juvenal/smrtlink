/*
 * Socket.h
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <map>
#include <boost/asio.hpp>
#include "Packet.h"
#include "Filter.h"
#include "Types.h"

#define SRC_PORT 29809
#define DST_PORT 29808

#define MAX_LENGTH 1024

typedef std::function<int(Packet)> Listener;
typedef std::pair<Filter, Listener> ListenerPair;

class Socket {
public:
    Socket(boost::asio::io_service&);
    virtual ~Socket();
    void init(short, short);
    void send(Packet);
    void setHostIp(ipAddr);
    void listen(Listener l, Filter f = Filter());

private:
    void receive();
    void settimeout();
    boost::asio::ip::udp::socket send_socket_;
    boost::asio::ip::udp::socket receive_socket_;
    boost::asio::ip::udp::endpoint broadcast_endpoint_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::asio::ip::udp::endpoint wildcard_endpoint_;
    boost::asio::ip::udp::endpoint local_endpoint_;
    boost::asio::deadline_timer timer;
    bytes data = bytes(MAX_LENGTH);
    ipAddr local_ip;
    std::map<Filter, Listener> callback = { };

};

#endif /* SOCKET_H_ */
