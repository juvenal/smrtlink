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
#include "Types/bytes.h"
#include "Types/datasets.h"

#define DEFAULT_USER "admin"
#define DEFAULT_PASS "admin"

struct vlan {
	int vlan_id;
	std::string name;
};

struct port {
	byte id;
	byte status;
	struct {
		std::vector<vlan*> tagged;
		std::vector<vlan*> untagged;
		int pvid;
	} vlan;
};

class Switch {
public:
	Switch() {
	}
	void parse(datasets);
	struct {
		std::string type;
		std::string hardware_version;
		std::string firmware_version;
		macAddr mac {0x0,0x0,0x0,0x0,0x0,0x0};
	} device;
	struct {
		std::string password = DEFAULT_PASS;
		std::string username = DEFAULT_USER;
		std::string hostname;
		ipAddr ip_addr {0,0,0,0,};
		ipAddr ip_mask;
		ipAddr gateway;
		byte dhcp;
	} settings;
private:
	std::vector<vlan> vlans;
	std::vector<port> ports;
};

#endif /* SWITCH_H_ */
