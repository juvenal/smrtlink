//============================================================================
// Name        : smrtlink.cpp
// Author      : jdi
// Version     :
// Copyright   : GPL v2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstring>
#include <getopt.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include "Program.h"

#define USAGE "Usage: smrtlink [-p n|--port n] [-h|--help] [-v|--version] name\n"

#define flag_version 1
#define flag_help 2

#define no_argument 0
#define required_argument 1
#define optional_argument 2

int main(int argc, char *argv[]) {
	int opt, index, option_flags;

	option_flags = 0;

	const struct option longopts[] = { { "version", no_argument, 0, 'v' }, {
			"help", no_argument, 0, 'h' },
			{ "port", required_argument, 0, 'p' }, { "srcport",
			required_argument, 0, 's' },
			{ "dstport", required_argument, 0, 'p' }, { 0, 0, 0, 0 }, };

	Program p = Program();

	while ((opt = getopt_long(argc, argv, "vhp:s:", longopts, &index)) != -1) {
		switch (opt) {

		case 'h':
			std::cout << "You hit help" << std::endl;
			option_flags |= flag_version;
			break;

		case 'v':
			std::cout << "You hit version" << std::endl;
			option_flags |= flag_help;
			break;

		case 'p':
			p.dst_port = atoi(optarg);
			option_flags |= 4;
			break;

		case 's':
			p.src_port = atoi(optarg);
			option_flags |= 4;
			break;

		default: /* '?' */
			fprintf(stderr, "Unknown option\n");
			fprintf(stderr, USAGE);
			exit(EXIT_FAILURE);
		}
	}

	if (optind >= argc && !option_flags) {
		//fprintf(stderr, "Expected argument\n");
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	}

	if (optind < argc) {
		if (strcmp(argv[optind], "list") == 0) {
			if (p.list())
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		} else {
			printf("Unknown Command: %s\n", argv[optind]);
			while (optind < argc) {
				printf("->%s\n", argv[optind]);
				optind++;
			}
			exit(EXIT_FAILURE);
		}
		optind++;
	}

}

