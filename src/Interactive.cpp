/*
 * Interactive.cpp
 *
 *  Created on: 27.01.2016
 *      Author: jedi
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include<boost/program_options/parsers.hpp>
#include<readline/readline.h>
#include<readline/history.h>

#include "Program.h"
#include "Interactive.h"

using namespace std;

int Interactive::loop() {
    string cmd;
    vector<string> v;
    Program p = Program();
    p.init();
    while (1) {
        cmd = readline("smrtlink> ");
        if (!cmd.compare("quit") || !cmd.compare("q"))
            return 0;
        if (!cmd.empty()) {
            add_history(cmd.c_str());
            v = boost::program_options::split_unix(cmd);
            p.run(v);
        }
    }
    return 0;
}

int Interactive::single(vector<string> v) {
    Program p = Program();
    p.init();
    p.run(v);
    return 0;
}

