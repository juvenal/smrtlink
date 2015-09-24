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

int Program::run() {
	Device d = Device();
	printf(" %d\n", d.getName());

	bytes b = { 255, 255, 0, 0 };
	Host h = Host();
	Packet p = Packet(Packet::DISCOVERY);
	p.setBody(b);
	p.setHostMac(h.getMac());
	bytes a = p.getBytes();
	p.encode(a);

	try {
		asio::io_service io_service;
		Socket s(io_service);
		s.init(dst_port, src_port);
		s.send(a);
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 1;
}

int Program::discover() {
	return 0;
}
