/*
 * Options.h
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "Types.h"

#define VERSION "smrtlink (v1 Linux)\n"
#define USAGE "usage: %s [-bhrvx] [-i interface] [-u [password:]username]\n\
	[-p password] <command>\n\n"
#define HELP "\
	Option Summary:\n\
		-h --help	This help text\n\
		-v --version	Display version of this tool\n\
		-r		switch ports to emulate switch while sniffing\n\
		-b --header 	Show header\n\
		-x --hex 	Display Packets as Hex String\n\
		-i --interface	only use one Interface\n\
		-u --user 	Login with user\n\
		-p		Password\n\n\
	Command Summary:\n\
		help		This help text\n\
		list		list all connected switches\n\
		sniff		capture and display all incoming or outgoing packets\n\
				depending on the --reverse option\n\n"

#define FLAG_HEX 1
#define FLAG_REVERSE 2
#define FLAG_HEADER 4

extern Options options;

#endif /* OPTIONS_H_ */
