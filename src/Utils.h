/*
 * Utils.h
 *
 *  Created on: 24.09.2015
 *      Author: jdi
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <cstring>
#include "Types.h"

namespace utils {

static void printHex(bytes d) {
	if (d.size() > 0)
		printf("%.2X", d[0]);
	for (unsigned i = 1; i < d.size(); i++) {
		printf(":%.2X", d[i]);
	}
}

static void printDec(bytes d) {
	if (d.size() > 0)
		printf("%.1d", d[0]);
	for (unsigned i = 1; i < d.size(); i++) {
		printf(".%.1d", d[i]);
	}
}

}
#endif /* UTILS_H_ */
