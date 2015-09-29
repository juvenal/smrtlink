/*
 * Types.h
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <functional>
#include <vector>
#include <array>
#include <map>

template<typename T>
std::vector<T> operator+(const std::vector<T> &A, const std::vector<T> &B) {
	std::vector<T> AB;
	AB.reserve(A.size() + B.size());                // preallocate memory
	AB.insert(AB.end(), A.begin(), A.end());        // add A;
	AB.insert(AB.end(), B.begin(), B.end());        // add B;
	return AB;
}

template<typename T>
std::vector<T> &operator+=(std::vector<T> &A, const std::vector<T> &B) {
	A.reserve(A.size() + B.size());
	A.insert(A.end(), B.begin(), B.end());
	return A;
}

template<size_t N>
using byteArray = std::array<unsigned char, N>;
typedef std::vector<unsigned char> bytes;
typedef unsigned char byte;

struct dataset {
	short type;
	short len;
	bytes value;
};

//typedef std::vector<dataset> datasets;
typedef std::map<short, dataset> datasets;

//std::function<int()>;
//typedef int receiveCallback;
struct Options {
	unsigned flags = 0x00;
	std::string user;
	std::string password;
	std::string interface;
	std::string file;
	long timeout;
};

#endif /* TYPES_H_ */
