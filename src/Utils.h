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

static bytes readHex(std::string d) {
	std::string delimiter = ":";
	std::string token;
	size_t pos = 0;
	bytes arr = { };
	int hex;
	byte b;
	while ((pos = d.find(delimiter)) != std::string::npos) {
		token = d.substr(0, pos);
		sscanf(token.c_str(), "%x", &hex);
		d.erase(0, pos + delimiter.length());
		b = hex & 0xFF;
		arr.push_back(b);
	}
	sscanf(d.c_str(), "%x", &hex);
	b = hex & 0xFF;
	arr.push_back(b);
	return arr;
}

static void printHex(bytes d) {
	if (d.size() > 0)
		printf("%.2X", d[0]);
	for (unsigned i = 1; i < d.size(); i++) {
		printf(":%.2X", d[i]);
	}
}

static void print(macAddr d) {
	printf("%.2X", d[0]);
	for (unsigned i = 1; i < 6; i++) {
		printf(":%.2X", d[i]);
	}
}

static void print(inetAddr d) {
	printf("%.1d", d[0]);
	for (unsigned i = 1; i < 4; i++) {
		printf(".%.1d", d[i]);
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
