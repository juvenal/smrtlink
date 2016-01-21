/*
 * lookupTable.h
 *
 *  Created on: 11.10.2015
 *      Author: jdi
 */

#include <string>
#include "table.h"

table::table(std::initializer_list<set> l) {
	int i = 0;
	for (set s : l) {
		this->left[s.type] = s;
	}
}
table::set table::operator[](short n){
	return this->left[n];
}
bool table::exists(short n){
	return !(left.find(n) == left.end());
}
std::string table::name(short n){
	return this->left[n].name;
}
