/*
 * Program.cpp
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */
#include <stdio.h>

#include "Program.h"
#include "Device.h"
#include "Host.h"
#include "Socket.h"
#include "Packet.h"

Program::Program() {
	// TODO Auto-generated constructor stub
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

int Program::run() {
	Device d = Device();
	printf(" %d", d.getName());

	bytes b = { 255, 255, 0, 0};

	Host h = Host();
	Packet p = Packet(Packet::DISCOVERY);
	p.setBody(b);
	p.setHostMac(h.getMac());
	bytes a = p.getBytes();
	printf("\na =");
	for (unsigned i = 0; i < sizeof(a); i++)
		printf(" %d", a[i]);
	p.encode(a);
	printf("\nb =");
	for (unsigned i = 0; i < sizeof(a); i++)
		printf(" %d", a[i]);
	printf("\n");

	try {
		asio::io_service io_service;
		Socket s(io_service, dst_port, src_port);
		//s.listen();
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
