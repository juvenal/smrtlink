/*
 * Filter.h
 *
 *  Created on: 23.02.2016
 *      Author: jedi
 */

#ifndef FILTER_H_
#define FILTER_H_

#include "Packet.h"

class Filter {
public:
    Filter();
    Filter(Packet::OpCode);
    Filter(macAddr);
    Filter opcode(Packet::OpCode);
    Filter mac(macAddr);
    Filter tokenid(short);
    bool pass(const Packet) const;
    bool operator<(const Filter) const;
private:
    Packet::OpCode oc = Packet::NONE;
    macAddr switchMac = { 0, 0, 0, 0, 0, 0 };
    short tokenId = -1;
    short fragmentOffset = -1;
};

#endif /* FILTER_H_ */
