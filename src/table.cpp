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
	this->data.resize(l.size());
	for (set s : l) {
		this->data[i] = s;
		this->left[s.type] = &this->data[i];
		this->right[s.name] = &this->data[i];
		i++;
	}
}
short table::operator[](std::string s){
	return this->right[s]->type;
}
std::string table::operator[](short n){
	return this->left[n]->name;
}
bool table::exists(std::string s){
	return !(right.find(s) == right.end());
}
bool table::exists(short n){
	return !(left.find(n) == left.end());
}
const table::set* table::get(std::string s){
	return this->right[s];
}
const table::set* table::get(short n){
	return this->left[n];
}
