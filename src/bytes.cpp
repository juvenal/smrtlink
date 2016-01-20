/*
 * Bytes.cpp
 *
 *  Created on: 02.10.2015
 *      Author: jdi
 */

#include "bytes.h"

bytes bytes::readHex(std::string s){
	vector ret;
	std::string delimiter = ":";
	std::string token;
	size_t pos = 0;
	int hex;
	byte b;
	ret.resize(0);
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		sscanf(token.c_str(), "%x", &hex);
		s.erase(0, pos + delimiter.length());
		b = hex & 0xFF;
		ret.push_back(b);
	}
	sscanf(s.c_str(), "%x", &hex);
	b = hex & 0xFF;
	ret.push_back(b);
	return ret;
}
