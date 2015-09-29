/*
 * Switch.h
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include <string>
#include "Types.h"

#define DEFAULT_USER "admin"
#define DEFAULT_PASS "admin"

struct vlan {
	int vlan_id;
	std::string name;
};

struct port {
	int id;
	struct {
		std::vector<vlan*> tagged;
		std::vector<vlan*> untagged;
		int pvid;
	} vlan;
};

class Switch {
public:
	Switch();
	void parse(datasets);
private:
	struct {
		std::string type;
		std::string hardware_version;
		std::string firmware_version;
		byteArray<6> mac;
	} device;
	struct {
		std::string password = DEFAULT_PASS;
		std::string username = DEFAULT_USER;
		struct {
			std::string hostname;
			byteArray<4> ip_addr;
			byteArray<4> ip_mask;
			byteArray<4> gateway;
			byte dhcp;
		} network;
	} settings;
	std::vector<vlan> vlans;
	std::vector<port> ports;
};

#endif /* SWITCH_H_ */
