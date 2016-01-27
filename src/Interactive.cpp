/*
 * Interactive.cpp
 *
 *  Created on: 27.01.2016
 *      Author: jedi
 */

#include <iostream>
#include <string>

#include "Interactive.h"

using namespace std;

Interactive::Interactive() {
    // TODO Auto-generated constructor stub

}

Interactive::~Interactive() {
    // TODO Auto-generated destructor stub
}

int Interactive::run() {
    string cmd;
    while(cmd.compare("quit")){
        cout<< "smrtlink>" << flush;
        cin >> cmd;
        cout << cmd <<endl;;
    }
    return 0;
}

