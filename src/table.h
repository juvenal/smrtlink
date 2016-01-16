/*
 * lookupTable.h
 *
 *  Created on: 11.10.2015
 *      Author: jdi
 */

#ifndef LOOKUPTABLE_H_
#define LOOKUPTABLE_H_

#include <map>
#include <vector>

class table {
public:
	enum F {STRING,HEX,DEC,ACTION,EMPTY};
	struct set {
		short type;
		F format;
		std::string name;
	};
	table(std::initializer_list<set> l);
	const short& operator[](std::string);
	const std::string& operator[](short);
	const set* get(std::string);
	const set* get(short);
	bool exists(std::string);
	bool exists(short);
private:
	std::vector<set> data;
	const std::map<short, set*> left;
	const std::map<std::string, set*> right;
};

#endif /* LOOKUPTABLE_H_ */
