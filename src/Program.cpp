/*
 * Program.cpp
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */
#include <cstdio>
#include <algorithm>

#include "Options.h"
#include "Program.h"
#include "Host.h"
#include "Socket.h"
#include "Switch.h"
#include "Packet.h"

int Program::list() {

	//Device d = Device();
	//printf(" %d\n", d.getName());

	Host h = Host();
	printf("List:\n");
	Packet p = Packet(Packet::DISCOVERY);
	p.setHostMac(h.getMac());
	p.setPayload( { });
	bytes a = p.getBytes();
	p.encode(a);

	try {
		asio::io_service io_service;
		Socket s(io_service);
		s.setHostIp(h.getIp());
		s.init(DST_PORT, SRC_PORT);
		s.callback = [](Packet a) {
			if (options.flags & FLAG_HEADER) {
				std::cout <<"Received Header:\t"<< a.getHead() <<"\n";
			}
			if (options.flags & FLAG_HEX) {
				std::cout <<"Received Payload:\t"<<a.getBody()<<"\n";
			}
			datasets d =a.getPayload();
			std::cout <<"\t"<<d[2].value <<"("<< d[1].value<<")\tMAC: "<<d[3].value<<"\tIP: "<<d[4].value<<"\n";
			Switch s = Switch();
			std::cout <<"\t"<<s.settings.hostname<<"("<< s.device.type<<")\tMAC: "<<s.device.mac<<"\tIP: "<<s.settings.ip_addr<<"\n";
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
		Host h = Host();
		Socket s(io_service);
		s.setHostIp(h.getIp());
		s.init(DST_PORT, SRC_PORT);
		s.callback = [](Packet p) {
			if (options.flags & FLAG_HEADER) {
				if (options.flags & FLAG_HEX) {
					std::cout <<"Received Header:\t"<< p.getHead() <<"\n";
				} else {
					p.printHeader();
					printf("\n");
				}
			}
			if (options.flags & FLAG_HEX) {
				std::cout <<"Received Payload:\t"<<p.getBody()<<"\n";
			}
			for(auto a : p.getPayload()) {
				dataset d = a.second;
				printf("#%d\tLength: %d\n\tHex: ",d.type,d.len);
				std::cout << d.value;
				printf("\n\tDec: ");
				std::cout <<d.value;
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

int Program::encode(std::string s) {
	bytes d(s);
	Packet p = Packet(Packet::DISCOVERY);
	p.encode(d);
	printf("%x", d[0]);
	for (unsigned i = 1; i < d.size(); i++) {
		printf(":%x", d[i]);
	}
	printf("\n");
	return 0;
}

int Program::setProperty() {
	return 0;
}
int Program::getProperty() {

	return 0;
}
int Program::save() {
	//File = fopen(otions.file)
	return 0;
}
int Program::restore() {
	//File = fopen(otions.file)
	return 0;
}
int Program::flash() {

	return 0;
}
int Program::reboot() {

	return 0;
}
int Program::reset() {

	return 0;
}
