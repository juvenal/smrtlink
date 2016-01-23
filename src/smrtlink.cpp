//============================================================================
// Name        : smrtlink.cpp
// Author      : jdi
// Version     : 1.1
// Copyright   : GPL v2
// Description : SmrtLink in C++, Ansi-style
//============================================================================

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>

#include <boost/program_options.hpp>
#include <unistd.h>

#include "Constant.h"
#include "Host.h"
#include "Program.h"
#include "Switch.h"

#define no_argument 0
#define required_argument 1
#define optional_argument 2

using namespace std;
namespace po = boost::program_options;

Options options;

constexpr unsigned int caseArg(const char* str, int h = 0) {
    return !str[h] ? 5381 : (caseArg(str, h + 1) * 33) ^ str[h];
}

int main3(int argc, char *argv[]) {
    int opt, index;

    options.user = DEFAULT_USER;
    options.password = DEFAULT_PASS;

    // Declare the supported options.
    po::options_description desc("Option Summary");
    desc.add_options()("help,h", "Display this help text")("version,V",
            "Display version of this tool")("reverse,r",
            po::bool_switch(&options.flags.REVERSE)->default_value(false),
            "switch ports to emulate switch while sniffing")("permanent,s",
            po::bool_switch(&options.flags.PERMANENT)->default_value(false),
            "Not yet implemented: make changes immediately permanent")("hex,x",
            po::bool_switch(&options.flags.HEX)->default_value(false),
            "Display Packets as Hex String")("json,j",
            po::bool_switch(&options.flags.JSON)->default_value(false),
            "Display Packets as JSON")("header,b",
            po::bool_switch(&options.flags.HEADER)->default_value(false),
            "Show header")("wait,w",
            po::bool_switch(&options.flags.WAIT)->default_value(false),
            "Not yet implemented: blocking until operation is completed")(
            "debug,d",
            po::value<int>()->implicit_value(1)->default_value(0)->value_name(
                    "n"), "Show debugging messages")("password,p",
            po::value<string>(&options.password)->value_name("password"), "")(
            "user,u", po::value<string>()->value_name("username"), "")(
            "interface,i",
            po::value<string>(&options.interface)->value_name("iface"),
            "only use one Interface")("file,f",
            po::value<string>(&options.file)->value_name("path"),
            "choose a settings file")("timeout,t",
            po::value<long>(&options.timeout)->default_value(180L)->value_name(
                    "n"), "Timeout in milliseconds")("verbose,v",
            po::value<int>()->implicit_value(1)->default_value(0)->value_name(
                    "n"), "verbosity level");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cerr << VERSION;
        cerr << USAGE;
        cerr << desc << "\n";
        cerr << HELP;
        exit(EXIT_SUCCESS);
        return 1;
    }

    if (vm.count("version")) {
        cerr << VERSION;
        exit(EXIT_SUCCESS);
        return 1;
    }

    Program p = Program();

    /*//TODO stdin
     std::ostringstream bucket;
     bucket << std::cin.rdbuf();
     p.input = bucket.str();
     */

    if (optind >= argc) {
        fprintf(stderr, "Command expected\n");
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    p.init();

    if (optind < argc) {
        std::string cmd = std::string(argv[optind++]);

        switch (caseArg(cmd.c_str())) {
        case caseArg("set"):
            while (optind < argc) {
                printf("+%s\n", argv[optind]);
                optind++;
            }
            if (!p.setProperty({}))
                exit(EXIT_SUCCESS);
            fprintf(stderr, "Not yet implemented.\n");
            exit(EXIT_FAILURE);
            break;
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

        case caseArg("get"):
            if (!p.getProperty({}))
                exit(EXIT_SUCCESS);
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

        default:
            printf("Unknown command: %s\n", cmd.c_str());
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_FAILURE);
}

