//============================================================================
// Name        : smrtlink.cpp
// Author      : jdi
// Version     :
// Copyright   : GPL v2
// Description : SmrtLink in C++, Ansi-style
//============================================================================

#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

#include <getopt.h>
#include <unistd.h>

#include "Options.h"
#include "Host.h"
#include "Program.h"

#define no_argument 0
#define required_argument 1
#define optional_argument 2

Options options;

constexpr unsigned int caseArg(const char* str, int h = 0) {
	return !str[h] ? 5381 : (caseArg(str, h + 1) * 33) ^ str[h];
}

int main(int argc, char *argv[]) {
	int opt, index;

	const struct option longopts[] = { { "version", no_argument, 0, 'v' }, {
			"help", no_argument, 0, 'h' }, { "reverse", no_argument, 0, 'r' }, {
			"permanent", no_argument, 0, 's' }, { "password", required_argument,
			0, 'p' }, { "user",
	required_argument, 0, 'u' }, { "interface", required_argument, 0, 'i' }, {
			"header", required_argument, 0, 'b' }, { "hex", required_argument,
			0, 'x' }, { "file", required_argument, 0, 'f' }, { "timeout",
	required_argument, 0, 't' }, { "wait",
	required_argument, 0, 'w' }, { 0, 0, 0, 0 }, };

	Program p = Program();

	while ((opt = getopt_long(argc, argv, "bhrsvxp:u:i:f:t:", longopts, &index))
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

		case 's':
			options.flags |= FLAG_PERMANENT;
			break;

		case 'w':
			options.flags |= FLAG_WAIT;
			break;

		case 't':
			options.timeout = atoi(optarg);
			break;

		case 'f':
			options.file = std::string(optarg);
			break;

		case 'p':
			options.password = std::string(optarg);
			break;

		case 'u':
			options.user = std::string(optarg);
			break;

		case 'i':
			options.interface = std::string(optarg);
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
		std::string cmd = std::string(argv[optind++]);

		switch (caseArg(cmd.c_str())) {
		case caseArg("set"):
			if (p.setProperty())
				exit(EXIT_SUCCESS);
			fprintf(stderr, "Not yet implemented.\n");
			exit(EXIT_FAILURE);
			break;
		case caseArg("reboot"):
			if (p.reboot())
				exit(EXIT_SUCCESS);
			fprintf(stderr, "Not yet implemented.\n");
			exit(EXIT_FAILURE);
			break;
		case caseArg("reset"):
			if (p.reset())
				exit(EXIT_SUCCESS);
			fprintf(stderr, "Not yet implemented.\n");
			exit(EXIT_FAILURE);
			break;
		case caseArg("save"):
			if (p.save())
				exit(EXIT_SUCCESS);
			fprintf(stderr, "Not yet implemented.\n");
			exit(EXIT_FAILURE);
			break;
		case caseArg("restore"):
			if (p.restore())
				exit(EXIT_SUCCESS);
			fprintf(stderr, "Not yet implemented.\n");
			exit(EXIT_FAILURE);
			break;
		case caseArg("flash"):
			if (p.flash())
				exit(EXIT_SUCCESS);
			fprintf(stderr, "Not yet implemented.\n");
			exit(EXIT_FAILURE);
			break;

		case caseArg("get"):
			if (p.getProperty())
				exit(EXIT_SUCCESS);
			break;

		case caseArg("list"):
			if (p.list())
				exit(EXIT_SUCCESS);
			break;

		case caseArg("sniff"):
			if (p.sniff())
				exit(EXIT_SUCCESS);
			break;

		case caseArg("encode"):
			if (optind < argc) {
				std::string s(argv[optind]);
				optind++;
				if (p.encode(s))
					exit(EXIT_SUCCESS);
			} else {
				fprintf(stderr, "Argument expected after encode\n");
				exit(EXIT_FAILURE);
			}
			break;

		case caseArg("help"):
			fprintf(stderr, VERSION);
			fprintf(stderr, USAGE, argv[0]);
			fprintf(stderr, HELP);
			exit(EXIT_SUCCESS);
			break;

		default:
			printf("Unknown command: %s\n", cmd.c_str());
			while (optind < argc) {
				printf("->%s\n", argv[optind]);
				optind++;
			}
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_FAILURE);
}

