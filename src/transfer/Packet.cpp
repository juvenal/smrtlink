/*
 * Packet.cpp
 *
 *  Created on: 03.09.2015
 *      Author: jdi
 */

#include <string.h>
#include <cstdlib>
#include <time.h>
#include "Packet.h"
#include "../Types.h"

Packet::Packet(OpCode c) {
	srand(time(NULL));
	sequenceId = rand() % 1000;
	opCode = c;
}

Packet::~Packet() {
	// TODO Auto-generated destructor stub
}

bytes Packet::getBytes() {
	int i = 0;
	push(body, i, payload);
	push(body, i, (int) PACKET_END);
	i = 0;
	push(head, i, version);
	push(head, i, opCode);
	push(head, i, switchMac);
	push(head, i, hostMac);
	push(head, i, sequenceId);
	push(head, i, err);
	push(head, i, this->getLength());
	push(head, i, fragmentOffset);
	push(head, i, flag);
	push(head, i, tokenId);
	push(head, i, checkSum);
	bytes data = head + body;
	return data;
}

void Packet::setBody(bytes data) {
	this->body = data;
}

void Packet::setHostMac(bytes mac) {
	this->hostMac = mac;
}

short Packet::getLength() const {
	return HEADER_LEN + body.size();
}

int Packet::getCheckSum() const {
	return checkSum;
}

void Packet::setCheckSum(int checkSum) {
	this->checkSum = checkSum;
}

short Packet::getSequenceId() const {
	return sequenceId;
}

void Packet::setSequenceId(short sequenceId) {
	this->sequenceId = sequenceId;
}

const bytes& Packet::getSwitchMac() const {
	return switchMac;
}

void Packet::setSwitchMac(bytes switchMac) {
	this->switchMac = switchMac;
}

const datasets& Packet::getPayload() const {
	return payload;
}

void Packet::setPayload(const datasets& payload) {
	this->payload = payload;
}

void Packet::encode(bytes &data) {
	int len = data.size();
	bytes key = { 191, 155, 227, 202, 99, 162, 79, 104, 49, 18, 190, 164, 30,
			76, 189, 131, 23, 52, 86, 106, 207, 125, 126, 169, 196, 28, 172, 58,
			188, 132, 160, 3, 36, 120, 144, 168, 12, 231, 116, 44, 41, 97, 108,
			213, 42, 198, 32, 148, 218, 107, 247, 112, 204, 14, 66, 68, 91, 224,
			206, 235, 33, 130, 203, 178, 1, 134, 199, 78, 249, 123, 7, 145, 73,
			208, 209, 100, 74, 115, 72, 118, 8, 22, 243, 147, 64, 96, 5, 87, 60,
			113, 233, 152, 31, 219, 143, 174, 232, 153, 245, 158, 254, 70, 170,
			75, 77, 215, 211, 59, 71, 133, 214, 157, 151, 6, 46, 81, 94, 136,
			166, 210, 4, 43, 241, 29, 223, 176, 67, 63, 186, 137, 129, 40, 248,
			255, 55, 15, 62, 183, 222, 105, 236, 197, 127, 54, 179, 194, 229,
			185, 37, 90, 237, 184, 25, 156, 173, 26, 187, 220, 2, 225, 0, 240,
			50, 251, 212, 253, 167, 17, 193, 205, 177, 21, 181, 246, 82, 226,
			38, 101, 163, 182, 242, 92, 20, 11, 95, 13, 230, 16, 121, 124, 109,
			195, 117, 39, 98, 239, 84, 56, 139, 161, 47, 201, 51, 135, 250, 10,
			19, 150, 45, 111, 27, 24, 142, 80, 85, 83, 234, 138, 216, 57, 93,
			65, 154, 141, 122, 34, 140, 128, 238, 88, 89, 9, 146, 171, 149, 53,
			102, 61, 114, 69, 217, 175, 103, 228, 35, 180, 252, 200, 192, 165,
			159, 221, 244, 110, 119, 48 };
	bytes s = key;
	int i, t, j = 0;
	for (int k = 0; k < len; k++) {
		i = (k + 1) % 256;
		j = (j + s[i]) % 256;
		t = s[i];
		s[i] = s[j];
		s[j] = t;
		data[k] = ((data[k] ^ s[(s[i] + s[j]) % 256]));
	}
}

void Packet::push(bytes &arr, int &index, byte data) {
	arr[index] = data;
	index++;
}

void Packet::push(bytes &arr, int &index, bytes data) {
	for (unsigned j = 0; j < data.size(); j++)
		push(arr, index, data[j]);
}

void Packet::push(bytes &arr, int &index, short data) {
	byte a = (data >> 8) & 0xFF;
	push(arr, index, a);
	a = data & 0xFF;
	push(arr, index, a);
}

void Packet::push(bytes &arr, int &index, int data) {
	byte a = (data >> 24) & 0xFF;
	push(arr, index, a);
	a = (data >> 16) & 0xFF;
	push(arr, index, a);
	a = (data >> 8) & 0xFF;
	push(arr, index, a);
	a = data & 0xFF;
	push(arr, index, a);
}

void Packet::push(bytes &arr, int &index, dataset data) {
	push(arr, index, data.type);
	push(arr, index, data.len);
	push(arr, index, data.value);
}

void Packet::push(bytes &arr, int &index, datasets data) {
	for (unsigned j = 0; j < data.size(); j++)
		push(arr, index, data[j]);
}
