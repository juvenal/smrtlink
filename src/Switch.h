/*
 * Switch.h
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include <string>
#include <map>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/prettywriter.h"
#include "Types.h"

#define DEFAULT_USER "admin"
#define DEFAULT_PASS "admin"

typedef rapidjson::Value jsonNode;

/*
template<typename T>
jsonNode to_json(const T &x) {
	// TODO Throw undefined
	return NULL;
}

template<> jsonNode to_json<vlan>(const vlan &x) {
	jsonNode ret;
	return ret;
}

template<typename T>
T from_json(const jsonNode &s) {
// TODO Throw not implemented
	return NULL;
}

template<> vlan from_json<vlan>(const jsonNode &s) {
	vlan ret;
	return ret;
}*/

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
	int parse(datasets);
	int parse(dataset);
	int parse(std::string);
	std::string toString();
	struct {
		std::string type;
		std::string hardware_version;
		std::string firmware_version;
		macAddr mac { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	} device;
	struct {
		std::string password = DEFAULT_PASS;
		std::string username = DEFAULT_USER;
		std::string hostname;
		ipAddr ip_addr { 0, 0, 0, 0, };
		ipAddr ip_mask;
		ipAddr gateway;
		bool dhcp;
	} settings;
private:
	rapidjson::Document json;
	std::vector<vlan> vlans;
	std::vector<port> ports;
};

#endif /* SWITCH_H_ */
