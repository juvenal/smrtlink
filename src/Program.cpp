/*
 * Program.cpp
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */
#include <stdio.h>

#include "Utils.h"
#include "Program.h"
#include "device/Device.h"
#include "device/Host.h"
#include "transfer/Socket.h"
#include "transfer/Packet.h"

Program::Program() {
	// TODO Auto-generated constructor stub
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

int Program::list() {

	printf("List:\n");
	//Device d = Device();
	//printf(" %d\n", d.getName());

	Host h = Host();
	Packet p = Packet(Packet::DISCOVERY);
	p.setHostMac(h.getMac());
	p.setPayload( { });
	bytes a = p.getBytes();
	p.encode(a);

	try {
		asio::io_service io_service;
		Socket s(io_service);
		s.init(dst_port, src_port);
		s.callback = [](Packet a) {
			datasets d =a.getPayload();
			printf("%s (%s)\tMAC: ", &d[2].value[0], &d[1].value[0]);
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
		s.init(src_port, dst_port);
		s.callback = [](Packet p) {
			printf("Receive Head:\t");
			utils::printHex(p.getHead());
			printf("\nReceive Body:\t");
			utils::printHex(p.getBody());
			printf("\n");
			for(auto a : p.getPayload()) {
				dataset d = a.second;
				printf("#%d\tLength: %d Value: %s\n",d.type,d.len,&d.value[0]);
			}
			printf("\n");
			printf("\n");
			printf("\n");
			return 0;
		};
		s.listen();
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 1;
}
