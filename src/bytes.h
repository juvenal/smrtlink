/*
 * Bytes.h
 *
 *  Created on: 02.10.2015
 *      Author: jdi
 */

#ifndef BYTES_H_
#define BYTES_H_

#include <initializer_list>
#include <functional>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

typedef unsigned char byte;

class bytes: public std::vector<unsigned char> {
        typedef std::vector<unsigned char> vector;
    public:
        using vector::operator[];
        bytes() {
        }
        bytes(int n) :
                vector(n) {
        }

        bytes(std::string d) :
                vector(d.begin(), d.end()) {
            this->push_back('\0');
        }

        bytes(std::initializer_list<uint8_t> s) {
            for (uint8_t b : s) {
                this->push_back(b);
            }
        }

        bytes(const vector &B) {
            this->reserve(B.size());
            this->insert(this->begin(), B.begin(), B.end());
        }

        bytes readHex(std::string);

        bytes operator=(const vector &B) {
            this->reserve(B.size());
            this->insert(this->begin(), B.begin(), B.end());
            return *this;
        }

        bytes &operator+=(const bytes &B) {
            this->reserve(this->size() + B.size());
            this->insert(this->end(), B.begin(), B.end());
            return *this;
        }

        bytes operator+(const bytes &B) {
            bytes AB;
            AB.reserve(this->size() + B.size());
            AB.insert(AB.end(), this->begin(), this->end());
            AB.insert(AB.end(), B.begin(), B.end());
            return AB;
        }

        friend std::ostream& operator<<(std::ostream& out, const bytes& arr) {
            if (arr.size() > 0) {
                out << std::hex << std::setw(2) << std::setfill('0')
                        << (unsigned) arr[0];
            }
            for (unsigned i = 1; i < arr.size(); i++) {
                out << ":" << std::setw(2) << std::setfill('0')
                        << (unsigned) arr[i];
            }
            return out;
        }

        operator std::string() {
            std::string s(this->begin(), this->end());
            return s;
        }
};

#endif /* BYTES_H_ */
