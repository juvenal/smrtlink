/*
 * Packet.h
 *
 *  Created on: 03.09.2015
 *      Author: jdi
 */

#ifndef PACKET_H_
#define PACKET_H_

#define HEADER_LEN 32
#define PACKET_END 0xFFFF0000

#include "Types/Types.h"

class Packet {
public:
	enum OpCode {
		DISCOVERY, GET, SET, READ4,RECEIVE, READ5
	};
	Packet(OpCode);
	void encode(bytes&);
	bytes getBytes();
	void parse(bytes);
	void printHeader();
	std::string opCodeToString();
	short getLength() const;
	int getCheckSum() const;
	short getSequenceId() const;
	macAddr getSwitchMac() const;
	const bytes& getBody() const;
	const bytes& getHead() const;
	const datasets& getPayload() const;
	void setBody(bytes);
	void setHostMac(macAddr);
	void setSwitchMac(macAddr);
	void setCheckSum(int);
	void setSequenceId(short);
	void setPayload(datasets payload);

private:
	bytes head = bytes(32);
	bytes body = bytes(0);
	datasets payload;

	byte version = 1;
	byte opCode;
	macAddr switchMac {{ 0, 0, 0, 0, 0, 0 }};
	macAddr hostMac {{ 0, 0, 0, 0, 0, 0 }};
	macAddr broadcastMac  {{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }};
	short sequenceId;
	short tokenId = 0;
	short fragmentOffset = 0;
	int errorCode = 0;
	int checkSum = 0;
	short flag = 0;

	void buildHead();
	void buildBody();

	void push(bytes&, int&, short);
	void push(bytes&, int&, int);
	void push(bytes&, int&, byte);
	void push(bytes&, int&, bytes);
	void push(bytes&, int&, ipAddr);
	void push(bytes&, int&, macAddr);
	void push(bytes&, int&, dataset);

	void pull(bytes&, int&, short&);
	void pull(bytes&, int&, int&);
	void pull(bytes&, int&, byte&);
	void pull(bytes&, int&, bytes&, unsigned);
	void pull(bytes&, int&, ipAddr&);
	void pull(bytes&, int&, macAddr&);
	void pull(bytes&, int&, dataset&);
};

#endif /* PACKET_H_ */
