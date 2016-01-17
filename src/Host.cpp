/*
 * Host.cpp
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

//TODO clean up
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_link.h>
#include <net/if.h>

#include "Options.h"
#include "Host.h"
#include "Types.h"

macAddr Host::getMac() {
	int s;
	struct ifreq buffer;
	macAddr data { 0, 0, 0, 0, 0, 0 };
	if (options.interface != "") {
		s = socket(PF_INET, SOCK_DGRAM, 0);
		memset(&buffer, 0x00, sizeof(buffer));
		strcpy(buffer.ifr_name, options.interface.c_str());
		ioctl(s, SIOCGIFHWADDR, &buffer);
		close(s);
		memcpy(&data[0], &buffer.ifr_hwaddr.sa_data[0], 6);
	}
	return data;
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
		if (ifa->ifa_addr->sa_family == AF_INET)
			if (options.interface.compare(ifa->ifa_name) == 0) {
				memcpy(&data[0], &ifa->ifa_addr->sa_data[2], 4);
				return data;
			}
	}
	/*
	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
		if (ifa->ifa_addr == NULL)
			continue;
		if (ifa->ifa_addr->sa_family == AF_INET)
			if (getIface().compare(ifa->ifa_name) == 0) {
				memcpy(&data[0], &ifa->ifa_addr->sa_data[2], 4);
				return data;
			}
	}
	*/
	freeifaddrs(ifaddr);
	return data;
}

std::string Host::getIface() {
	std::string defaultInterface;
	std::ifstream routeFile("/proc/net/route", std::ios_base::in);
	if (!routeFile.good())
		return "";
	std::string line;
	std::vector<std::string> tokens;
	if (std::getline(routeFile, line))
		while (std::getline(routeFile, line)) {
			std::istringstream stream(line);
			std::string delimiter = "\t";
			size_t pos = 0;
			std::string token;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				tokens.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			if ((tokens.size() >= 2)
					&& (tokens[1] == std::string("00000000"))) {
				defaultInterface = tokens[0];
				break;
			}
			tokens.clear();
		}
	routeFile.close();
	return defaultInterface;
}
