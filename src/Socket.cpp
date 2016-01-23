/*
 * Socket.cpp
 *
 *  Created on: 02.09.2015
 *      Author: jdi
 */
#include <cstdlib>
#include <array>
#include <unistd.h>
#include "Socket.h"
#include "Packet.h"
#include "Constant.h"
#include "Host.h"
#include "Types.h"

Socket::Socket(boost::asio::io_service& io_service) :
        send_socket_(io_service), receive_socket_(io_service), timer(io_service) {
}
//, resolver(				io_service)
void Socket::init(short dst_port, short src_port) {
    if (initialized)
        return;

    if (options.flags & FLAG_REVERSE) {
        short p = dst_port;
        dst_port = src_port;
        src_port = p;
    }

    if (options.flags & FLAG_DEBUG)
        std::cout << "Local IP:\t" << local_ip << "\n";

    wildcard_endpoint_ = boost::asio::ip::udp::endpoint(
            boost::asio::ip::address_v4::from_string("0.0.0.0"), src_port);
    local_endpoint_ = boost::asio::ip::udp::endpoint(
            boost::asio::ip::address_v4(local_ip), src_port);
    broadcast_endpoint_ = boost::asio::ip::udp::endpoint(
            boost::asio::ip::address_v4::from_string("255.255.255.255"),
            dst_port);

    send_socket_.open(boost::asio::ip::udp::v4());
    send_socket_.set_option(boost::asio::socket_base::broadcast(true));
    send_socket_.set_option(boost::asio::socket_base::reuse_address(true));
    send_socket_.bind(local_endpoint_);

    receive_socket_.open(boost::asio::ip::udp::v4());
    receive_socket_.set_option(boost::asio::socket_base::broadcast(true));
    receive_socket_.set_option(boost::asio::socket_base::reuse_address(true));
    receive_socket_.bind(wildcard_endpoint_);

    if (options.timeout != 0) {
        timer.expires_from_now(
                boost::posix_time::milliseconds(options.timeout));
        timer.async_wait([this](const boost::system::error_code& error)
        {
            if (!error)
            {
                receive_socket_.close();
            }
        });
    }

    initialized = 1;
}

void Socket::setHostIp(ipAddr ip) {
    local_ip = ip;
}

void Socket::send(Packet p) {
    bytes data = p.getBytes();
    p.encode(data);
    unsigned char * a = &data[0];
    send_socket_.async_send_to(boost::asio::buffer(a, data.size()),
            broadcast_endpoint_,
            [this](boost::system::error_code ec, std::size_t bytes_sent)
            {
                listen();
            });
}

void Socket::listen() {
    data.resize(MAX_LENGTH);
    receive_socket_.async_receive_from(boost::asio::buffer(data, MAX_LENGTH),
            remote_endpoint_,
            [this](boost::system::error_code ec, std::size_t bytes_recvd)
            {
                if (ec || bytes_recvd == 0) {
                    //listen();
                    // TODO distinguish error codes
                } else {
                    data.resize(bytes_recvd);
                    Packet p = Packet(Packet::NONE);
                    p.encode(data);
                   // std::cout << "err" << p.getErrorCode() <<std::endl;
                    p.parse(data);
                    //std::cout << "err" << p.getErrorCode() <<std::endl;
                    if(!callback(p)) {
                        //TODO do something
                    }
                    listen();
                }
            });
}
