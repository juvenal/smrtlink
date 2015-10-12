/*
 * lookupTable.h
 *
 *  Created on: 11.10.2015
 *      Author: jdi
 */

#ifndef LOOKUPTABLE_H_
#define LOOKUPTABLE_H_

#include <map>

class lookupTable {
	struct set {
		short n;
		std::string s;
	};
public:
	lookupTable(std::initializer_list<set> l) {
		for (set s : l) {
			this->left[s.n] = s.s;
			this->right[s.s] = s.n;
		}
	}
	const short& operator[](std::string s) {
		return this->right[s];
	}
	const std::string& operator[](short n) {
		return this->left[n];
	}
	bool exists(std::string s) {
		return !(right.find(s) == right.end());
	}
	bool exists(short n) {
		return !(left.find(n) == left.end());
	}
private:
	std::map<short, std::string> left;
	std::map<std::string, short> right;
};

#endif /* LOOKUPTABLE_H_ */
