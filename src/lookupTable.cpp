/*
 * lookupTable.h
 *
 *  Created on: 11.10.2015
 *      Author: jdi
 */

#include "lookupTable.h"

lookupTable::lookupTable(std::initializer_list<set> l) {
	int i = 0;
	this->data.resize(l.size());
	for (set s : l) {
		this->data[i] = s;
		this->left[s.type] = &this->data[i];
		this->right[s.name] = &this->data[i];
		i++;
	}
}
const short& lookupTable::operator[](std::string s) {
	return this->right[s]->type;
}
const std::string& lookupTable::operator[](short n) {
	return this->left[n]->name;
}
bool lookupTable::exists(std::string s) {
	return !(right.find(s) == right.end());
}
bool lookupTable::exists(short n) {
	return !(left.find(n) == left.end());
}
