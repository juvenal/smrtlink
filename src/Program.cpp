/*
 * Program.cpp
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */
#include <iostream>
#include <algorithm>

#include "Options.h"
#include "Program.h"
#include "Host.h"
#include "Socket.h"
#include "Switch.h"
#include "Packet.h"
#include "Lookup.h"

int Program::list() {

	std::cout << "List:\n";
	Packet p = Packet(Packet::DISCOVERY);
	p.setHostMac(host.getMac());
	p.setPayload( { });
	bytes a = p.getBytes();
	p.encode(a);

	try {
		asio::io_service io_service;
		Socket s(io_service);
		s.setHostIp(host.getIp());
		s.init(DST_PORT, SRC_PORT);
		s.callback =
				[](Packet a) {
					if (options.flags & FLAG_HEADER) {
						if (options.flags & FLAG_HEX) {
							std::cout <<"Received Header:\n"<< a.getHead() <<"\n";
						} else {
							a.printHeader();
							std::cout<<"\n";
						}
					}
					if (options.flags & FLAG_HEX) {
						std::cout <<"Received Payload:\n"<<a.getBody()<<"\n";
					} else {
						datasets d =a.getPayload();
						Switch s = Switch();
						s.parse(d);
						std::cout <<"Devices:\n\t"<<s.settings.hostname<<" ("<< s.device.type<<")\tMAC: "<<s.device.mac<<"\tIP: "<<s.settings.ip_addr<<"\n";
					}
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
		s.setHostIp(host.getIp());
		s.init(DST_PORT, SRC_PORT);
		s.callback =
				[](Packet p) {
					std::cout <<"Packet:\n\t"<<p.opCodeToString()<<"\n";
					if (options.flags & FLAG_HEADER) {
						if (options.flags & FLAG_HEX) {
							std::cout <<"Received Header:\n\t"<< p.getHead() <<"\n";
						} else {
							p.printHeader();
							printf("\n");
						}
					}
					if (options.flags & FLAG_HEX) {
						std::cout <<"Received Payload:\n\t"<<p.getBody()<<"\n";
					} else {
						for(auto a : p.getPayload()) {
							dataset d = a.second;
							auto lookup=(options.flags & FLAG_REVERSE)?snd_lookup:rcv_lookup;
							if(lookup.exists(d.type)) {
								if(d.len>0) {
									std::cout<<std::dec<<"\t++"<<std::hex<<d.type<<std::dec<<"++\n";
								} else {
									std::cout<<std::dec<<"#"<<d.type<<"\tLength: "<<d.len<<"\n";
									std::cout<<std::hex<< "\tHex: " <<d.value<<"\n";
									d.value.push_back(0U);
									std::cout<<"\tString: " <<&d.value[0]<<"\n";
								}
							} else {
								std::cout<<"###"<<lookup[d.type]<<"\n";
							}
						}
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
	std::cout << d << std::endl;
	return 0;
}

int Program::setProperty() {
	return 0;
}
int Program::getProperty() {
	printf("Get:\n");
	Packet p = Packet(Packet::GET);
	macAddr d = { 0x14, 0xcc, 0x20, 0x49, 0x5e, 0x07 };
	p.setSwitchMac(d);
	p.setHostMac(host.getMac());
	datasets t = { { 2305, 0, { } } };
	p.setPayload(t);
	bytes a = p.getBytes();
	p.encode(a);

	try {
		asio::io_service io_service;
		Socket s(io_service);
		s.setHostIp(host.getIp());
		s.init(DST_PORT, SRC_PORT);
		s.callback =
				[](Packet a) {
					if (options.flags & FLAG_HEADER) {
						if (options.flags & FLAG_HEX) {
							std::cout <<"Received Header:\n"<< a.getHead() <<"\n";
						} else {
							a.printHeader();
							std::cout<<"\n";
						}
					}
					if (options.flags & FLAG_HEX) {
						std::cout <<"Received Payload:\n"<<a.getBody()<<"\n";
					} else {
						datasets d =a.getPayload();
						Switch s = Switch();
						s.parse(d);
						std::cout <<"Devices:\n\t"<<s.settings.hostname<<" ("<< s.device.type<<")\tMAC: "<<s.device.mac<<"\tIP: "<<s.settings.ip_addr<<"\n";
					}
					return 1;
				};
		s.send(a);
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 1;
}
int Program::save() {
	Switch sw = Switch();
	std::string str = sw.toString();
//File = fopen(otions.file)

	return 0;
}
int Program::restore() {

	const char str[] =
			" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	printf("Original JSON:\n %s\n", str);
	Switch sw = Switch();
	sw.parse(str);
//File = fopen(otions.file)
	return 1;
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
void Program::init() {
	if (options.interface.compare("") == 0)
		options.interface = host.getIface();
}
