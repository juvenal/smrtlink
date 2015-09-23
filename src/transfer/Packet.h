/*
 * Packet.h
 *
 *  Created on: 03.09.2015
 *      Author: jdi
 */

#ifndef PACKET_H_
#define PACKET_H_

#define HEADER_LEN 32
#define PACKET_END -65536

#include "../Types.h"

class Packet {
public:
	enum OpCode {
		DISCOVERY, GET, SET
	};
	Packet(OpCode);
	virtual ~Packet();
	void encode(bytes&);
	bytes getBytes();
	short getLength() const ;
	int getCheckSum() const;
	short getSequenceId() const;
	const bytes& getSwitchMac() const;
	const datasets& getPayload() const;
	void setBody(bytes);
	void setHostMac(bytes);
	void setCheckSum(int);
	void setSequenceId(short);
	void setSwitchMac(bytes);
	void setPayload(const datasets& payload);

private:
	bytes head = bytes(32);
	bytes body;
	datasets payload;

	byte version = 1;
	byte opCode;
	bytes switchMac = { 0, 0, 0, 0, 0, 0 };
	bytes hostMac = { 0, 0, 0, 0, 0, 0 };// TODO set Mac
	bytes broadcastMac = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	short sequenceId;
	short tokenId = 0;
	short fragmentOffset = 0;
	int err = 0;
	int checkSum = 0;
	short flag = 0;

	void buildHead();
	void buildBody();

	void push(bytes&, int&, short);
	void push(bytes&, int&, int);
	void push(bytes&, int&, byte);
	void push(bytes&, int&, bytes);
	void push(bytes&, int&, dataset);
	void push(bytes&, int&, datasets);
};

#endif /* PACKET_H_ */
