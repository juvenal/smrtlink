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
#define USAGE "usage: %s [-bdhjrvVstwx] [-i interface] [-U [password:]username]\n\
	[-P password] <command>\n\n"
#define HELP "\
    Option Summary:\n\
        -h --help               This help text\n\
        -V --version            Display version of this tool\n\
        -d --debug [n]          Show debugging messages\n\
        -v --verbose [n]        Show debugging messages\n\
\
        -r --reverse            switch ports to emulate switch while sniffing\n\
        -i --interface <iface>  only use one Interface\n\
        -t --timeout <n>        Timeout in milliseconds. Default: 180\n\
        -w --wait               Not yet implemented: blocking until operation is completed\n\
        -s --permanent          make changes immediately permanent\n\
\
        -b --header             Show header\n\
        -t --text               Display Packets as readable Text (default)\n\
        -x --hex                Display Packets as Hex String\n\
        -j --json               Display Packets as JSON\n\n\
\
        -U --user <[password:]username>\n\
        -P --password <password>\n\
                                Login with Username and Password\n\
        -f --file <path>        choose a settings file\n\
        -I --stdin              Not yet implemented\n\
        -O --stdout             Not yet implemented\n\
        -X --interactive        gives in interactive Shell. Ignores all commands\n\n\
    Command Summary:\n\
        list            list all connected switches\n\
        sniff [type:<type>] [<filter>]\n\
                        capture and display all incoming or outgoing packets\n\
                        depending on the --reverse option\n\
        encode          use encoding algorithm on hex data separated by colon\n\
        get <property1> [<property1> [...]]\n\
                        Not yet implemented\n\
        set <property1>=<value> [<property2>=<value> [...]]\n\
                        Not yet implemented\n\
        save            Not yet implemented: save config to file\n\
        restore         Not yet implemented: restore onfig from file\n\
        flash           Not yet implemented: replace firmware\n\
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
