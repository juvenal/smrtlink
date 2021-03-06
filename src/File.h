/*
 * File.h
 *
 *  Created on: 17.10.2015
 *      Author: jdi
 */

#ifndef FILE_H_
#define FILE_H_

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
namespace fs = boost::filesystem;

#include <string>

#define DEFAULT_FILE "config.json"

class File {
public:
	File() {
		home = fs::path(getenv("HOME")) / ".smrtlink";
	}
	std::string read();
	int write(std::string);
private:
	fs::path home;
};

#endif /* FILE_H_ */
