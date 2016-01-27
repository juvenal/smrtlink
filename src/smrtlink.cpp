//============================================================================
// Name        : smrtlink.cpp
// Author      : jdi
// Version     :
// Copyright   : GPL v2
// Description : SmrtLink in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <regex>

#include <cstring>
#include <sstream>
#include <cstdlib>

#include <getopt.h>
#include <unistd.h>

#include "Constant.h"
#include "Interactive.h"
#include "Host.h"
#include "Program.h"
#include "Switch.h"
#include "lookup.h"

#define no_argument 0
#define required_argument 1
#define optional_argument 2

using namespace std;

Options options;

constexpr unsigned int caseArg(const char* str, int h = 0) {
    return !str[h] ? 5381 : (caseArg(str, h + 1) * 33) ^ str[h];
}

int main(int argc, char *argv[]) {
    int index,opt;

    options.user = DEFAULT_USER;
    options.password = DEFAULT_PASS;

    const struct option longopts[] = { { "version", no_argument, 0, 'V' }, {
            "verbose", no_argument, 0, 'v' }, { "help", no_argument, 0, 'h' }, {
            "reverse", no_argument, 0, 'r' },
            { "permanent", no_argument, 0, 's' }, { "debug", optional_argument,
                    0, 'd' }, { "password", required_argument, 0, 'p' }, {
                    "user", required_argument, 0, 'u' }, { "interface",
                    required_argument, 0, 'i' }, { "header", required_argument,
                    0, 'b' }, { "hex", required_argument, 0, 'x' }, { "file",
                    required_argument, 0, 'f' }, { "timeout", required_argument,
                    0, 't' }, { "wait", required_argument, 0, 'w' }, { 0, 0, 0,
                    0 }, };



    while ((opt = getopt_long(argc, argv, "bhrvXIswxP:U:i:f:t:d::", longopts,
            &index)) != -1) {
        switch (opt) {

        case 'h':
            fprintf(stderr, VERSION);
            fprintf(stderr, USAGE, argv[0]);
            fprintf(stderr, HELP);
            exit(EXIT_SUCCESS);
            break;

        case 'V':
            fprintf(stderr, VERSION);
            exit(EXIT_SUCCESS);
            break;

        case 'r':
            options.flags.REVERSE = true;
            break;

        case 'b':
            options.flags.HEADER = true;
            break;

        case 'x':
            options.flags.HEX = true;
            break;

        case 's':
            options.flags.PERMANENT = true;
            break;

        case 'w':
            options.flags.WAIT = true;
            break;

        case 'X':
            options.flags.INTERACTIVE = true;
            break;

        case 'v':
            if (optarg != NULL)
                options.verbosity = atoi(optarg);
            else
                options.verbosity++;
            break;

        case 'd':
            if (optarg != NULL)
                options.debug_level = atoi(optarg);
            else
                options.debug_level++;
            break;

        case 't':
            options.timeout = atol(optarg);
            break;

        case 'f':
            options.file = std::string(optarg);
            break;

        case 'P':
            options.password = std::string(optarg);
            break;

        case 'U':
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

    /*//TODO stdin
     std::ostringstream bucket;
     bucket << std::cin.rdbuf();
     p.input = bucket.str();
     */

    if (optind >= argc && !options.flags.INTERACTIVE) {
        cerr << "Command expected\n";
        cerr << USAGE;
        exit(EXIT_FAILURE);
    }

    if (options.flags.INTERACTIVE) {
        if (optind < argc) {
        cerr << "Command is ignored in interactive mode\n";
    }
        Interactive p = Interactive();
        if (!p.run())
            exit(EXIT_SUCCESS);
        fprintf(stderr, "Not yet implemented.\n");
        exit(EXIT_FAILURE);
    }
    else if (optind < argc) {
        Program p = Program();
    p.init();
    std::vector<std::string> vect;
    std::map<std::string, std::string> list;
    std::cmatch sm;
        std::string cmd = std::string(argv[optind++]);
        switch (caseArg(cmd.c_str())) {
        case caseArg("reboot"):
            if (!p.reboot())
                exit(EXIT_SUCCESS);
            fprintf(stderr, "Not yet implemented.\n");
            exit(EXIT_FAILURE);
            break;
        case caseArg("reset"):
            if (!p.reset())
                exit(EXIT_SUCCESS);
            fprintf(stderr, "Not yet implemented.\n");
            exit(EXIT_FAILURE);
            break;
        case caseArg("save"):
            if (!p.save())
                exit(EXIT_SUCCESS);
            fprintf(stderr, "Not yet implemented.\n");
            exit(EXIT_FAILURE);
            break;
        case caseArg("restore"):
            if (!p.restore())
                exit(EXIT_SUCCESS);
            fprintf(stderr, "Not yet implemented.\n");
            exit(EXIT_FAILURE);
            break;
        case caseArg("flash"):
            if (!p.flash())
                exit(EXIT_SUCCESS);
            fprintf(stderr, "Not yet implemented.\n");
            exit(EXIT_FAILURE);
            break;

        case caseArg("list"):
            if (!p.list())
                exit(EXIT_SUCCESS);
            break;

        case caseArg("sniff"):
            if (!p.sniff())
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
        case caseArg("set"):
            while (optind < argc) {
                if (regex_match(argv[optind], sm,
                        std::regex("^([a-z]+)=(.*)$"))) {
                    if (!snd_lookup.exists(sm[1])&&!rcv_lookup.exists(sm[1])) {
                        cerr << "Unknown argument " << argv[optind] << endl;
                        exit(EXIT_FAILURE);
                    }
                    list.insert(
                            std::pair<std::string, std::string>(sm[1], sm[2]));
                } else {
                    cerr << "Invalid Syntax " << argv[optind] << endl;
                    exit(EXIT_FAILURE);
                }
                optind++;
            }
            if (!p.setProperty(list))
                exit(EXIT_SUCCESS);
            fprintf(stderr, "Not yet implemented.\n");
            exit(EXIT_FAILURE);
            break;
        case caseArg("get"):
            while (optind < argc) {
                if (regex_match(argv[optind], sm, std::regex("^([a-z]+)$"))) {
                    if (!snd_lookup.exists(sm[1])&&!rcv_lookup.exists(sm[1])) {
                        cerr << "Unknown argument " << argv[optind] << endl;
                        exit(EXIT_FAILURE);
                    }
                    vect.push_back(sm[1]);
                } else {
                    cerr << "Invalid argument " << argv[optind] << endl;
                    exit(EXIT_FAILURE);
                }
                optind++;
            }
            if (!p.getProperty(vect))
                exit(EXIT_SUCCESS);
            break;
        default:
            printf("Unknown command: %s\n", cmd.c_str());
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_FAILURE);
}

