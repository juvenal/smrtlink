/*
 * Host.cpp
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */


//TODO clean up
#include <cstdio>
//#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
//#include <linux/if_link.h>
#include "Options.h"
#include "Host.h"
#include "Types/Types.h"
//#include "bytes.h"

macAddr Host::getMac() {
	macAddr ret { 0x6a,0x49,0x16,0x17,0x2e,0x8d }; //TODO find actual MAC Address
	return ret;
}

ipAddr Host::getIp() {
	struct ifaddrs *ifaddr, *ifa;
	int n;
	ipAddr data { 0, 0, 0, 0 };

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
		if (ifa->ifa_addr == NULL)
			continue;

		if (ifa->ifa_addr->sa_family == AF_INET) {
			if (options.interface.compare(ifa->ifa_name) == 0) {
				memcpy(&data[0], &ifa->ifa_addr->sa_data[2], 4);
				return data;
			}
		}
	}

	freeifaddrs(ifaddr);
	return data;
}

