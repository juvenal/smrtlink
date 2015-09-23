/*
 * encode.cpp
 *
 *  Created on: 15.09.2015
 *      Author: jdi
 */

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#include "Packet.h"

int encode(int argc, char *argv[]) {
	std::string s(argv[1]);
	std::string delimiter = ":";
	std::string token;
	size_t pos = 0;
	bytes arr = { };
	int hex;
	byte b;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		sscanf(token.c_str(), "%x", &hex);
		s.erase(0, pos + delimiter.length());
		b = hex & 0xFF;
		arr.push_back(b);
	}
	sscanf(s.c_str(), "%x", &hex);
	b = hex & 0xFF;
	arr.push_back(b);

	Packet p = Packet(Packet::DISCOVERY);
	p.encode(arr);
	printf("%x", arr[0]);
	for (unsigned i = 1; i < arr.size(); i++) {
		printf(":%x", arr[i]);
	}
	printf("\n");

}
