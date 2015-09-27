/*
 * Program.h
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Types.h"

#define SRC_PORT 29809
#define DST_PORT 29808

class Program {
public:
	Program();
	virtual ~Program() {
	}
	int list();
	int sniff();
	int encode(std::string);
};

#endif /* PROGRAM_H_ */
