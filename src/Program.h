/*
 * Program.h
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Types/Types.h"

#define SRC_PORT 29809
#define DST_PORT 29808

class Program {
public:
	Program(){}
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
};

#endif /* PROGRAM_H_ */
