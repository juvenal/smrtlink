/*
 * Host.cpp
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#include "Host.h"

Host::Host() {
	// TODO Auto-generated constructor stub

}

bytes Host::getMac() {
	return {0x08,0x3e,0x8e,0x16,0x17,0x2c};
}

bytes Host::getIp() {
	return {0,0,0,0};
}

