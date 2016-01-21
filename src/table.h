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
	enum F {STRING,HEX,DEC,ACTION,BOOL,EMPTY};
	struct set {
		short type;
		F format;
		std::string name;
	};
	table(std::initializer_list<set> l);
	set operator[](short);
	bool exists(short);
	std::string name(short);
private:
	std::map<short, set> left;
};

#endif /* LOOKUPTABLE_H_ */
