/*
 * Host.cpp
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <linux/if_link.h>
#include "Utils.h"
#include "Host.h"

Host::Host() {
	// TODO Auto-generated constructor stub

}

bytes Host::getMac() {
	return {0x08,0x3e,0x8e,0x16,0x17,0x2c};
}

bytes Host::getIp(std::string iface) {
	struct ifaddrs *ifaddr, *ifa;
	int n;
	bytes data = { 0, 0, 0, 0 };

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
		if (ifa->ifa_addr == NULL)
			continue;

		if (ifa->ifa_addr->sa_family == AF_INET) {
			if (iface.compare(ifa->ifa_name) == 0) {
				data.resize(4);
				memcpy(&data[0], &ifa->ifa_addr->sa_data[2], 4);
				return data;
			}
		}
	}

	freeifaddrs(ifaddr);

	return data;
}

