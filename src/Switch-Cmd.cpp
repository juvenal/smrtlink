/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include <string>
#include "Types.h"
#include "Switch.h"
#include "Constant.h"
#include "table.h"

using namespace smrtlink;
using namespace std;

int Switch::set(pair<string, string> str) {

    return 0;
}

std::string Switch::get(std::string str) {
    std::string ret;
    switch (caseArg(str.c_str())) {
    case caseArg("ip"):
        ret = "0.0.0.0";
        break;
    }
    return ret;
}

