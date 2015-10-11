/*
 * Bytes.cpp
 *
 *  Created on: 02.10.2015
 *      Author: jdi
 */

#include "bytes.h"

bytes::bytes(std::string d) {
	vector();
	std::string delimiter = ":";
	std::string token;
	size_t pos = 0;
	int hex;
	byte b;
	resize(0);
	while ((pos = d.find(delimiter)) != std::string::npos) {
		token = d.substr(0, pos);
		sscanf(token.c_str(), "%x", &hex);
		d.erase(0, pos + delimiter.length());
		b = hex & 0xFF;
		push_back(b);
	}
	sscanf(d.c_str(), "%x", &hex);
	b = hex & 0xFF;
	push_back(b);
}
