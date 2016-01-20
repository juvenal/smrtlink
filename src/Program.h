/*
 * Program.h
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <memory>

#include "Types.h"
#include "Host.h"
#include "Socket.h"

class Program {
private:
	std::shared_ptr<boost::asio::io_service> io_service;
	std::shared_ptr<Socket> sock;
	Host host = Host();
	int ping(std::function<int(Packet)>);
public:
	Program() {
		io_service = std::make_shared<boost::asio::io_service>();
		sock = std::make_shared<Socket>(*io_service);
	}
	void init();
	int list();
	int sniff();
	int encode(std::string);
	int setProperty();
	int getProperty();
	int save();
	int restore();
	int flash();
	int reboot();
	int reset();
	std::string input;
};

#endif /* PROGRAM_H_ */
