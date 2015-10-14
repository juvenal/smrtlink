/*
 * Program.h
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Types/Types.h"
#include "Host.h"

class Program {
public:
	Program(){}
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
private:
	Host host = Host();
};

#endif /* PROGRAM_H_ */
