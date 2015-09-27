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

#include "Options.h"
#include "Host.h"
#include "Program.h"

#define no_argument 0
#define required_argument 1
#define optional_argument 2

Options options;

int main(int argc, char *argv[]) {
	int opt, index;

	const struct option longopts[] = { { "version", no_argument, 0, 'v' }, {
			"help", no_argument, 0, 'h' }, { "reverse", no_argument, 0, 'r' }, {
			"password", required_argument, 0, 'p' }, { "user",
	required_argument, 0, 'u' }, { "interface", required_argument, 0, 'i' }, {
			"header", required_argument, 0, 'b' }, { "hex", required_argument,
			0, 'x' }, { 0, 0, 0, 0 }, };

	Program p = Program();

	while ((opt = getopt_long(argc, argv, "bhrvxp:u:i:", longopts, &index))
			!= -1) {
		switch (opt) {

		case 'h':
			fprintf(stderr, VERSION);
			fprintf(stderr, USAGE, argv[0]);
			fprintf(stderr, HELP);
			exit(EXIT_SUCCESS);
			break;

		case 'v':
			fprintf(stderr, VERSION);
			exit(EXIT_SUCCESS);
			break;

		case 'r':
			options.flags |= FLAG_REVERSE;
			break;

		case 'b':
			options.flags |= FLAG_HEADER;
			break;

		case 'x':
			options.flags |= FLAG_HEX;
			break;

		case 'p':
			options.password= std::string(optarg);
			break;

		case 'u':
			options.user= std::string(optarg);
			break;

		case 'i':
			options.interface= std::string(optarg);
			break;

		default: /* '?' */
			fprintf(stderr, "Unknown option\n");
			fprintf(stderr, USAGE, argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "Command expected\n");
		fprintf(stderr, USAGE, argv[0]);
		exit(EXIT_FAILURE);
	}

	if (optind < argc) {
		if (strcmp(argv[optind], "help") == 0) {
			fprintf(stderr, VERSION);
			fprintf(stderr, USAGE, argv[0]);
			fprintf(stderr, HELP);
			exit(EXIT_SUCCESS);
		} else if (strcmp(argv[optind], "list") == 0) {
			optind++;
			if (p.list())
				exit(EXIT_SUCCESS);
		} else if (strcmp(argv[optind], "sniff") == 0) {
			optind++;
			if (p.sniff())
				exit(EXIT_SUCCESS);
		} else if (strcmp(argv[optind], "encode") == 0) {
			optind++;
			if (optind < argc) {
				std::string s(argv[optind]);
				optind++;
				if (p.encode(s))
					exit(EXIT_SUCCESS);
			} else {
				fprintf(stderr, "Argument expected after encode\n");
				exit(EXIT_FAILURE);
			}
		} else {
			printf("Unknown command: %s\n", argv[optind]);
			optind++;
			while (optind < argc) {
				printf("->%s\n", argv[optind]);
				optind++;
			}
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_FAILURE);

}

