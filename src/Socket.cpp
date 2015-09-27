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
#include <sys/types.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <asio.hpp>
#include "Socket.h"
#include "Packet.h"
#include "Types.h"
#include "Utils.h"
#include "Options.h"
#include "Host.h"

Socket::Socket(asio::io_service& io_service) :
		send_socket_(io_service), receive_socket_(io_service), resolver(
				io_service) {
}

void Socket::init(short dst_port, short src_port) {

	if (options.flags & FLAG_REVERSE) {
		short p = dst_port;
		dst_port = src_port;
		src_port = p;
	}


    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    /* Walk through linked list, maintaining head pointer so we
       can free list later */

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        /* Display interface name and family (including symbolic
           form of the latter for the common families) */

        printf("%-8s %s (%d)\n",
               ifa->ifa_name,
               (family == AF_PACKET) ? "AF_PACKET" :
               (family == AF_INET) ? "AF_INET" :
               (family == AF_INET6) ? "AF_INET6" : "???",
               family);

        /* For an AF_INET* interface address, display the address */

        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(ifa->ifa_addr,
                    (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                          sizeof(struct sockaddr_in6),
                    host, NI_MAXHOST,
                    NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }

            printf("\t\taddress: <%s>\n", host);

        } /*else if (family == AF_PACKET && ifa->ifa_data != NULL) {
            struct rtnl_link_stats *stats = ifa->ifa_data;

            printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
                   "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                   stats->tx_packets, stats->rx_packets,
                   stats->tx_bytes, stats->rx_bytes);
        }*/
    }

    freeifaddrs(ifaddr);

	/*
	asio::ip::udp::resolver::query query(asio::ip::host_name(), "");
	asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
	asio::ip::udp::resolver::iterator end;
	while (iter != end) {
		asio::ip::udp::endpoint ep = *iter++;
		std::cout << "IP: " << ep << std::endl;
	}*/

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
