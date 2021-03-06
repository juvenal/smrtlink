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

enum CntStatus {
	OPEN, SHORT
};

struct vlan {
	int vlan_id;
	std::string name;
	std::vector<byte> tagged_member;
	std::vector<byte> untagged_member;
};

struct trunk {
	int trunk_id;
	std::vector<byte> member;
};

struct port {
	byte id;
	byte status;
	int pvid;
	struct {
		//port_settings
	} settings;
	struct {
		//port_statistics
	} stats;
	struct {
		//bandwidth_control_ingress
		//bandwidth_control_egress
	} bw_control;
	struct {
		//storm_control
	} storm_control;
	struct {
		CntStatus status;
		int fault_distace;
	} test;
	//qos_basic

};

class Switch {
public:
	Switch() {
	}
	int parse(datasets);
	int parse(dataset);
	int parse(std::string);
	int set(std::pair<std::string,std::string>);

	std::string get(std::string);
	std::string toString();

	int print();

	struct {
		std::string type;
		std::string hardware_version;
		std::string firmware_version;
		macAddr mac { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
		int ports;
	} device;
	struct {
		std::string password = DEFAULT_PASS;
		std::string username = DEFAULT_USER;
		std::string hostname;
		ipAddr ip_addr { 0, 0, 0, 0, };
		ipAddr ip_mask;
		ipAddr gateway;
		bool dhcp;
		bool loop_prevention;
		bool qos_enabled;
		bool vlan_enabled;
		//mtu_vlan
	} settings;

private:
	rapidjson::Document json;
	std::vector<vlan> vlans;
	std::vector<port> ports;
};

#endif /* SWITCH_H_ */
