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
#include "File.h"
#include "Host.h"
#include "Socket.h"
#include "Switch.h"
#include "Packet.h"
#include "Lookup.h"

int printHeader(Packet p) {
	if (options.flags & FLAG_HEADER) {
		if (options.flags & FLAG_HEX) {
			std::cout << "Received Header:\n\t" << p.getHead() << "\n";
		} else {
			p.printHeader();
			printf("\n");
		}
	}
	return 0;
}

int printPacket(Packet p) {
	if (options.flags & FLAG_HEX) {
		std::cout << "Received Payload:\n\t" << p.getBody() << "\n";
	} else {
		for (auto a : p.getPayload()) {
			dataset d = a.second;
			auto lookup =
					(options.flags & FLAG_REVERSE) ? snd_lookup : rcv_lookup;
			if (lookup.exists(d.type)) {
					const table::set *s = lookup.get(d.type);
				if (d.len > 0) {
					switch (s->format) {
					case table::STRING:
						std::cout << std::dec << "+\t" << s->name << " = "
								<< &d.value[0] << std::dec << "\n";
						break;
					case table::HEX:
						std::cout << std::dec << "+\t" << s->name << " = "
								<< std::hex << d.value << std::dec << "\n";
						break;
					case table::DEC:
						std::cout << std::dec << "+\t" << s->name << " = "
								<< std::dec << d.value << std::dec << "\n";
						break;
					default:
						std::cout << std::dec << "+\t" << s->name << " = "
								<< std::hex << d.value << std::dec << "\n";
					}
				} else { //empty
					std::cout << std::dec << ">\t" << s->name << "\n";
				}
			} else {//unknown id
				if (d.len > 0) {
					std::cout << "##\t" << d.type << ":\n\t";
					std::cout << std::hex << d.value << std::dec << "\n";
				} else { //empty
					std::cout << "#>\t" << d.type << "\n";
				}
			}
		}
	}
	return 0;
}

int Program::list() {

	std::cout << "List:\n";
	Packet p = Packet(Packet::DISCOVERY);
	p.setHostMac(host.getMac());
	p.setPayload( { });
	bytes b = p.getBytes();
	p.encode(b);

	try {
		sock->setHostIp(host.getIp());
		sock->init(DST_PORT, SRC_PORT);
		sock->callback =
				[this](Packet a) {
					printHeader(a);
					if (options.flags & FLAG_HEX) {
						std::cout <<"Received Payload:\n"<<a.getBody()<<"\n";
					} else {
						datasets d =a.getPayload();
						Switch sw = Switch();
						sw.parse(d);
						File f;
						f.write(sw.toString());
						std::cout <<"Devices:\n\t"<<sw.settings.hostname<<" ("<< sw.device.type<<")\tMAC: "<<sw.device.mac<<"\tIP: "<<sw.settings.ip_addr<<"\n";
					}
					return 1;
				};
		sock->send(b);
		io_service->run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 1;
}

int Program::sniff() {
	printf("Listening:\n");
	try {
		boost::asio::io_service io_service;
		Socket s(io_service);
		s.setHostIp(host.getIp());
		s.init(DST_PORT, SRC_PORT);
		s.callback = [](Packet p) {
			std::cout << p.opCodeToString() << "\n";
			printHeader(p);
			printPacket(p);
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
	std::cout << "List:\n";
	Packet p = Packet(Packet::DISCOVERY);
	p.setHostMac(host.getMac());
	p.setPayload( { });
	bytes b = p.getBytes();
	p.encode(b);
	std::cout << "count-x:" << sock.use_count() << "\n";
	auto s = sock;
	try {
		sock->setHostIp(host.getIp());
		sock->init(DST_PORT, SRC_PORT);

		std::cout << "count-y:" << sock.use_count() << "\n";
		sock->callback =
				[this](Packet a) {
					auto s = sock;
					std::cout<<"count-z:"<<sock.use_count()<<"\n";
					datasets d =a.getPayload();
					Switch sw = Switch();
					sw.parse(d);
					std::cout <<"Devices:\n\t"<<sw.settings.hostname<<" ("<< sw.device.type<<")\tMAC: "<<sw.device.mac<<"\tIP: "<<sw.settings.ip_addr<<"\n";

					Packet p = Packet(Packet::GET);
					p.setSwitchMac(a.getSwitchMac());
					p.setHostMac(host.getMac());
					datasets t = { {2305, 0, {}}};
					p.setPayload(t);
					bytes c = p.getBytes();
					p.encode(c);
					sock->callback =
					[this](Packet a) {
						auto s = sock;
						datasets d =a.getPayload();
						Switch sw = Switch();
						sw.parse(d);
						Packet p = Packet(Packet::LOGIN);
						p.setSwitchMac(a.getSwitchMac());
						p.setHostMac(host.getMac());
						datasets t = { {snd_lookup["login_user"], 0, {}}};
						p.setPayload(t);
						bytes c = p.getBytes();
						p.encode(c);

						sock->callback =
						[this](Packet a) {
							std::cout << a.opCodeToString() << "\n";
							printHeader(a);
							printPacket(a);
							return 0;
						};
						sock->send(c);
						return 0;
					};

					std::cout<<"count-b:"<<sock.use_count()<<"\n";

					sock->send(c);

					std::cout<<"count-a:"<<sock.use_count()<<"\n";
					return 0;
				};
		sock->send(b);
		io_service->run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 1;
}

int Program::save() {
	Switch sw = Switch();
	sw.settings.hostname = "testname.lan";
	File f;
	f.write(sw.toString());
	return 1;
}

int Program::restore() {
	File f;
	Switch sw;
	sw.parse(f.read());
	std::cout << "Devices:\n\t" << sw.settings.hostname << " ("
			<< sw.device.type << ")\tMAC: " << sw.device.mac << "\tIP: "
			<< sw.settings.ip_addr << "\n";
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
