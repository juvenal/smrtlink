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

class lookupTable {
public:
	struct set {
		short type;
		std::string name;
	};
	lookupTable(std::initializer_list<set> l);
	const short& operator[](std::string s);
	const std::string& operator[](short n);
	bool exists(std::string s);
	bool exists(short n);
private:
	std::vector<set> data;
	std::map<short, set*> left;
	std::map<std::string, set*> right;
};

#endif /* LOOKUPTABLE_H_ */
