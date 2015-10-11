/*
 * Options.h
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "Types/Types.h"

#define VERSION "smrtlink (v1 Linux)\n"
#define USAGE "usage: %s [-bhrvx] [-i interface] [-u [password:]username]\n\
	[-p password] <command>\n\n"
#define HELP "\
	### for questions please contact <smrtlink@jdi.li> ###\n\
	Option Summary:\n\
		-h --help	This help text\n\
		-v --version	Display version of this tool\n\
		-r		switch ports to emulate switch while sniffing\n\
		-b --header 	Show header\n\
		-x --hex 	Display Packets as Hex String\n\
		-i --interface	only use one Interface\n\
		-u --user 	Login with user\n\
		-p		Password\n\
		-f --file	Not yet implemented:.choose a settings file\n\
		-t --timeout	Not yet implemented\n\
		-w --wait	Not yet implemented: blocking until operation is completed\n\
		-s --permanent	Not yet implemented: make changes immediately permanent\n\n\
	Command Summary:\n\
		help		This help text\n\
		list		list all connected switches\n\
		sniff		capture and display all incoming or outgoing packets\n\
				depending on the --reverse option\n\
		encode		use encoding algorithm on hex data separated by colon\n\
		get		Not yet implemented\n\
		set		Not yet implemented\n\
		save		Not yet implemented: save config to file\n\
		restore		Not yet implemented: restore onfig from file\n\
		flash		Not yet implemented: replace firmware\n\
		reboot		Not yet implemented\n\
		reset		Not yet implemented\n\n"

#define FLAG_HEX 1
#define FLAG_REVERSE 2
#define FLAG_HEADER 4
#define FLAG_PERMANENT 8
#define FLAG_WAIT 16

extern Options options;

#endif /* OPTIONS_H_ */
