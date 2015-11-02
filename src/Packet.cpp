/*
 * Packet.cpp
 *
 *  Created on: 03.09.2015
 *      Author: jdi
 */

#include <cstring>
#include <cstdlib>
#include <ctime>
#include "Packet.h"
#include "Types.h"

Packet::Packet(OpCode c) {
	srand(time(NULL));
	sequenceId = rand() % 1000;
	opCode = c;
}

void Packet::printHeader() {
	std::cout << "Header:\n";
	std::cout << "\tID:\t\t" << sequenceId << "\n";
	std::cout << "\tVersion:\t" << (int) version << "\n";
	std::cout << "\tError:\t\t" << errorCode << "\n";
	std::cout << "\tSwitch MAC:\t" << switchMac << "\n";
	std::cout << "\tHost MAC: \t" << hostMac << "\n";
	std::cout << "\tLength:   \t" << std::dec << this->getLength() << "\n";
	std::cout << "\tOffset:   \t" << fragmentOffset << "\n";
	std::cout << "\tFlags:    \t" << std::hex << flag << "\n";
	std::cout << "\tChecksum: \t" << std::dec << checkSum << "\n";
}

bytes Packet::getBytes() {
	int i = 0;
	for (auto d : payload)
		push(body, i, d);
	push(body, i, (int) PACKET_END);
	i = 0;
	push(head, i, version);
	push(head, i, opCode);
	push(head, i, switchMac);
	push(head, i, hostMac);
	push(head, i, sequenceId);
	push(head, i, errorCode);
	push(head, i, this->getLength());
	push(head, i, fragmentOffset);
	push(head, i, flag);
	push(head, i, tokenId);
	push(head, i, checkSum);
	bytes data = head + body;
	return data;
}

void Packet::parse(bytes data) {
	memcpy(&head[0], &data[0], HEADER_LEN);
	body.resize(data.size() - HEADER_LEN);
	memcpy(&body[0], &data[HEADER_LEN], data.size() - HEADER_LEN);
	int i = 0;
	short checkLen = 0x0;
	pull(head, i, version);
	pull(head, i, opCode);
	pull(head, i, switchMac);
	pull(head, i, hostMac);
	pull(head, i, sequenceId);
	pull(head, i, errorCode);
	pull(head, i, checkLen);
	pull(head, i, fragmentOffset);
	pull(head, i, flag);
	pull(head, i, tokenId);
	pull(head, i, checkSum);
	if (this->getLength() != checkLen) {
		printf("Packet Length doesn't match: %lu != %hd\n", data.size(),
				checkLen);
	}
	i = 0;
	dataset d;
	payload = {};
	while (i < (int) body.size() - 4) {
		pull(body, i, d.type);
		pull(body, i, d.len);
		pull(body, i, d.value, d.len);
		payload.push_back(d);
	}
}

const bytes& Packet::getBody() const {
	return body;
}

const bytes& Packet::getHead() const {
	return head;
}

void Packet::setBody(bytes data) {
	this->body = data;
}

void Packet::setHostMac(macAddr mac) {
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

macAddr Packet::getSwitchMac() const {
	return switchMac;
}

void Packet::setSwitchMac(macAddr switchMac) {
	this->switchMac = switchMac;
}

const datasets& Packet::getPayload() const {
	return payload;
}

void Packet::setPayload(datasets payload) {
	this->payload = payload;
}

std::string Packet::opCodeToString() {
	switch (opCode) {
	case DISCOVERY:
		return "DISCOVERY";
	case GET:
		return "GET";
	case SET:
		return "SET";
	case LOGIN:
		return "LOGIN";
	case RETURN:
		return "RETURN";
	case READ5:
		return "READ5";
	default:
		return "NONE";
	}
	return "NONE";
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
	int i, j = 0;
	for (int k = 0; k < len; k++) {
		i = (k + 1) % 256;
		j = (j + s[i]) % 256;
		std::swap(s[i], s[j]);
		data[k] = data[k] ^ s[(s[i] + s[j]) % 256];
	}
}

void Packet::push(bytes &arr, int &index, byte data) {
	if (arr.size() > (unsigned) index) {
		arr[index++] = data;
	} else {
		arr.push_back(data);
		index++;
	}
}

void Packet::push(bytes &arr, int &index, bytes data) {
	for (unsigned j = 0; j < data.size(); j++)
		push(arr, index, data[j]);
}

void Packet::push(bytes &arr, int &index, ipAddr data) {
	for (unsigned j = 0; j < 4; j++)
		push(arr, index, (byte) data[j]);
}

void Packet::push(bytes &arr, int &index, macAddr data) {
	for (unsigned j = 0; j < 6; j++)
		push(arr, index, (byte) data[j]);
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

void Packet::pull(bytes &arr, int &index, byte &ret) {
	ret = arr[index++];
}

void Packet::pull(bytes &arr, int &index, bytes &ret, unsigned len) {
	ret.resize(len);
	memcpy(&ret[0], &arr[index], len);
	index += len;
}

void Packet::pull(bytes &arr, int &index, macAddr &ret) {
	memcpy(&ret[0], &arr[index], 6);
	index += 6;
}

void Packet::pull(bytes &arr, int &index, ipAddr &ret) {
	memcpy(&ret[0], &arr[index], 4);
	index += 4;
}

void Packet::pull(bytes &arr, int &index, short &ret) {
	ret = (arr[index++] << 8);
	ret |= arr[index++] & 0xFF;
	ret &= 0xFFFF;
}

void Packet::pull(bytes &arr, int &index, int &ret) {
	ret = arr[index++] << 24;
	ret |= (arr[index++] & 0xFF) << 16;
	ret |= (arr[index++] & 0xFF) << 8;
	ret |= arr[index++] & 0xFF;
}

void Packet::pull(bytes &arr, int &index, dataset &ret) {
	pull(arr, index, ret.type);
	pull(arr, index, ret.len);
	pull(arr, index, ret.value, (unsigned) ret.len);
}
