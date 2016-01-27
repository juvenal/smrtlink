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
#define USAGE "usage: %s [-bhrVstx] [-i interface] [-U [password:]username]\n\
	[-P password] <command>\n\n"
#define HELP "\
    Option Summary:\n\
        -h --help               This help text\n\
        -V --version            Display version of this tool\n\
\
        -r --reverse            switch ports to emulate switch while sniffing\n\
        -i --interface <iface>  only use one Interface\n\
        -t --timeout <n>        Timeout in milliseconds. Default: 180\n\
        -s --permanent          make changes immediately permanent\n\
\
        -b --header             Show header\n\
        -x --hex                Display Packets as Hex String\n\
\
        -U --user <[password:]username>\n\
        -P --password <password>\n\
                                Login with Username and Password\n\n\
    Command Summary:\n\
        list            list all connected switches\n\
        sniff           capture and display all incoming or outgoing packets\n\
                        depending on the --reverse option\n\
        encode          use encoding algorithm on hex data separated by colon\n\
        reboot          Not yet implemented\n\
        reset           Not yet implemented\n\n\
	### for questions please contact <smrtlink@jdi.li> ###\n\n"
//TODO
/*
 * Stdin
 * socketmode
 *
 */

extern Options options;

#endif /* OPTIONS_H_ */
