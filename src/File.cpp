/*
 * File.cpp
 *
 *  Created on: 17.10.2015
 *      Author: jdi
 */

#include <iostream>
#include "File.h"
#include "Options.h"

std::string File::read() {
	if (!fs::exists(home)) {
		fs::create_directory(home);
	}

	fs::ifstream in(((options.file=="")?home / DEFAULT_FILE:options.file), std::ios::in | std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	return "";
}

int File::write(std::string content) {
	if (!fs::exists(home)) {
		fs::create_directory(home);
	}
	fs::path p = (options.file=="")?home / DEFAULT_FILE:options.file;
	fs::ofstream file(p);
	file << content<<"\n";
	file.close();
	return 0;
}

