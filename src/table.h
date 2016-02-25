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
        enum A {
            RW, RO, WO, NONE, UNKNOWN
        };
        enum F {
            STRING, HEX, DEC, ACTION, BOOL, EMPTY
        };
        struct set {
                short type;
                F format;
                A action;
                std::string name;
                std::string id;
        };
        table(std::initializer_list<set> l);
        const table::set operator[](std::string);
        const table::set operator[](short);
        bool exists(std::string);
        bool exists(short);
        short type(std::string);
        std::string id(short);
        std::string name(short);
    private:
        std::vector<set> data;
        std::map<short, set*> left;
        std::map<std::string, set*> right;
};

#endif /* LOOKUPTABLE_H_ */
