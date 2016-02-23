/*
 * Filter.cpp
 *
 *  Created on: 23.02.2016
 *      Author: jedi
 */

#include "Filter.h"

Filter::Filter() {
}
Filter::Filter(macAddr a) {
    switchMac = a;
}
Filter::Filter(Packet::OpCode o) {
    oc = o;
}

Filter Filter::opcode(Packet::OpCode o) {
    oc = o;
    return *this;
}
Filter Filter::mac(macAddr a) {
    switchMac = a;
    return *this;
}
Filter Filter::tokenid(short i) {
    tokenId = i;
    return *this;
}

bool Filter::pass(const Packet p) const {
    macAddr none { 0, 0, 0, 0, 0, 0 };
    if (this->oc != Packet::NONE && this->oc != p.getOpCode())
        return false;
    if (this->switchMac != none && this->switchMac != p.getSwitchMac())
        return false;
    if (this->tokenId != -1 && this->tokenId != p.getTokenId())
        return false;
    /*    if (fragmentOffset != p.getF && fragmentOffset != -1)
     return false;*/
    return true;
}

bool Filter::operator<(const Filter f) const {
    if (this->oc != f.oc)
    return this->oc < f.oc;
    if (this->switchMac != f.switchMac)
        return this->switchMac < f.switchMac;
    if (this->tokenId < f.tokenId)
        return this->tokenId < f.tokenId;
    return false;
}
