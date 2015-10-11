/*
 * Types.h
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>

#include "bytes.h"
#include "datasets.h"

class macAddr: public std::array<byte, 6> {
public:
	friend std::ostream& operator<<(std::ostream& out, const macAddr& arr) {
		out << std::hex << std::setw(2) << std::setfill('0')
				<< (unsigned) arr[0];
		for (unsigned i = 1; i < 6; i++) {
			out << ":" << std::setw(2) << std::setfill('0')
					<< (unsigned) arr[i];
		}
		return out;
	}

	macAddr() {
		*this= {0,0,0,0,0,0};
	}

	macAddr(std::initializer_list<byte> s) {
		int i = 0;
        for (byte b : s) {
        	if(i<6) (*this)[i++]=b;
        	else break;
        }
	}

	macAddr(bytes bts) {
		int i = 0;
        for (byte b : bts) {
        	if(i<6) (*this)[i++]=b;
        	else break;
        }
	}
};

class ipAddr: public std::array<byte, 4> {
public:

	ipAddr() {
		*this= {0,0,0,0,0,0};
	}

	ipAddr(std::initializer_list<byte> s) {
		int i = 0;
        for (byte  b : s) {
        	if(i<4) (*this)[i++]=b;
        	else break;
        }
	}

	ipAddr(bytes bts) {
		int i = 0;
        for (byte b : bts) {
        	if(i<4) (*this)[i++]=b;
        	else break;
        }
	}

	friend std::ostream& operator<<(std::ostream& out, ipAddr& arr) {
		out << std::dec << (unsigned) arr[0];
		for (unsigned i = 1; i < 4; i++) {
			out << "." << (unsigned) arr[i];
		}
		return out;
	}
};

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

struct Options {
	unsigned flags = 0x00;
	std::string user;
	std::string password;
	std::string interface;
	std::string file;
	long timeout;
};

#endif /* TYPES_H_ */
