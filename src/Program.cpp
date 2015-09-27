/*
 * Program.cpp
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */
#include <cstdio>
#include <algorithm>

#include "Utils.h"
#include "Options.h"
#include "Program.h"
#include "Device.h"
#include "Host.h"
#include "Socket.h"
#include "Packet.h"

Program::Program() {
	// TODO Auto-generated constructor stub
}

int Program::list() {

	//Device d = Device();
	//printf(" %d\n", d.getName());

	Host h = Host();
	printf("IP:\t");
	utils::printDec(h.getIp(options.interface));
	printf("\nList:\n");
	Packet p = Packet(Packet::DISCOVERY);
	p.setHostMac(h.getMac());
	p.setPayload( { });
	bytes a = p.getBytes();
	p.encode(a);

	try {
		asio::io_service io_service;
		Socket s(io_service);
		s.init(DST_PORT, SRC_PORT);
		s.callback = [](Packet a) {
			if (options.flags & FLAG_HEADER) {
				printf("Received Header:\t");
				utils::printHex(a.getHead());
				printf("\n");
			}
			if (options.flags & FLAG_HEX) {
				printf("Received Payload:\t");
				utils::printHex(a.getBody());
				printf("\n");
			}
			datasets d =a.getPayload();
			printf("\t%s (%s)\tMAC: ", &d[2].value[0], &d[1].value[0]);
			utils::printHex(d[3].value);
			printf("\tIP: ");
			utils::printDec(d[4].value);
			printf("\n");
			return 1;
		};
		s.send(a);
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 1;
}

int Program::sniff() {
	printf("Listening:\n");
	try {
		asio::io_service io_service;
		Socket s(io_service);
		s.init(DST_PORT,SRC_PORT);
		s.callback = [](Packet p) {
			if (options.flags & FLAG_HEADER) {
				if (options.flags & FLAG_HEX) {
				printf("Received Header:\t");
				utils::printHex(p.getHead());
				}else{
					p.printHeader();
				}
				printf("\n");
			}
			if (options.flags & FLAG_HEX) {
				printf("Received Payload:\t");
				utils::printHex(p.getBody());
				printf("\n");
			}
			for(auto a : p.getPayload()) {
				dataset d = a.second;
				printf("#%d\tLength: %d\n\tHex: ",d.type,d.len);
				utils::printHex(d.value);
				printf("\n\tDec: ");
				utils::printDec(d.value);
				d.value.push_back(0U);
				printf("\n\tString: %s\n",&d.value[0]);
			}
			return 0;
		};
		s.listen();
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 1;
}

int Program::encode(std::string s){
	std::string delimiter = ":";
	std::string token;
	size_t pos = 0;
	bytes arr = { };
	int hex;
	byte b;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		sscanf(token.c_str(), "%x", &hex);
		s.erase(0, pos + delimiter.length());
		b = hex & 0xFF;
		arr.push_back(b);
	}
	sscanf(s.c_str(), "%x", &hex);
	b = hex & 0xFF;
	arr.push_back(b);

	Packet p = Packet(Packet::DISCOVERY);
	p.encode(arr);
	printf("%x", arr[0]);
	for (unsigned i = 1; i < arr.size(); i++) {
		printf(":%x", arr[i]);
	}
	printf("\n");
}
