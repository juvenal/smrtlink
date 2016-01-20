/*
 * Options.h
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "Types.h"

#define VERSION "smrtlink (v1.1 Linux)\n"
#define USAGE "usage: %s [-bdhjrvswx] [-i interface] [-u [password:]username]\n\
	[-p password] <command>\n\n"
#define HELP "\
	Option Summary:\n\
		-h --help		This help text\n\
		-v --version		Display version of this tool\n\
		-d --debug [n]		Show debugging messages\n\
		-r			switch ports to emulate switch while sniffing\n\
		-b --header 		Show header\n\
		-x --hex 		Display Packets as Hex String\n\
		-j --json 		Display Packets as JSON\n\
		-i --interface <iface>	only use one Interface\n\
		-u --user <[password:]username>\n\
		-p --password <password>\n\
					Login with Username and Password\n\
		-f --file <path>	choose a settings file\n\n\
		-t --timeout <n>	Timeout in milliseconds. Default: 180\n\
		-I --interactive	Not yet implemented\n\
		-O --stdout		Not yet implemented\n\
		-w --wait		Not yet implemented: blocking until operation is completed\n\
		-s --permanent		Not yet implemented: make changes immediately permanent\n\n\
	Command Summary:\n\
		help			This help text\n\
		list			list all connected switches\n\
		sniff [type:<type>] [<filter>]\n\
					capture and display all incoming or outgoing packets\n\
					depending on the --reverse option\n\
		encode			use encoding algorithm on hex data separated by colon\n\
		get			Not yet implemented\n\
		set			Not yet implemented\n\
		get|save		Not yet implemented: save config to file\n\
		set|restore		Not yet implemented: restore onfig from file\n\
		flash			Not yet implemented: replace firmware\n\
		reboot			Not yet implemented\n\
		reset			Not yet implemented\n\n\
	### for questions please contact <smrtlink@jdi.li> ###\n\n"
//TODO
/*
 * Stdin
 * socketmode
 *
 */

#define FLAG_HEX 1
#define FLAG_REVERSE 2
#define FLAG_HEADER 4
#define FLAG_PERMANENT 8
#define FLAG_WAIT 16
#define FLAG_DEBUG 32

extern Options options;

#endif /* OPTIONS_H_ */
