/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include <boost/bimap.hpp>

class lookupTable: public boost::bimap<short, std::string> {
	struct set{
		short n;
		std::string s;
	};
public:
	lookupTable(std::initializer_list<set> l) {
        for (set  s : l) {
        	this->left[s.n]=s.s;
        }
	}
	const short& operator[](std::string s){
		return this->right[s];
	}
	const std::string& operator[](short n){
		return this->left[n];
	}
};

static lookupTable rcv_lookup = { { 1, "type" }, //string
		{ 2, "hostname" }, //string
		{ 3, "mac" }, //byte[6]
		{ 4, "ip_addr" }, //byte[4]
		{ 5, "ip_mask" }, //byte[4]
		{ 6, "gateway" }, //byte[4]
		{ 7, "firmware_version" }, //string
		{ 8, "hardware_version" }, //string
		{ 9, "dhcp" }, //bool byte
		{ 8704, "802.1q vlan" }, //???
		//{0000," "},
		};

static lookupTable snd_lookup = {

// TODO find out if id is unique in response
		{ 10, "???" }, //after login
		{ 2, "???" }, //after login
		{ 512, "login_user" }, //string
		{ 513, "new_user" }, //string
		{ 514, "login_password" }, //string
		{ 515, "new_passwoord" }, //string
		{ 2200, "vlan" },
		{ 2305, "???" }, //sent before login and before change hostname
		{ 4608, "port_trunk" }, //byte[5] last byte bitmask??
		{ 8192, "mtu_vlan" }, //byte[2] first byte bool,	second byte port id
		{ 8449, "port_vlan" }, //???

		{ 8704, "802.1q vlan" }, //??? get vlan / set status
		{ 8705, "802.1q vlan" }, //???
		{ 8706, "802.1q vlan pvid" }, //????

		{ 12288, "QoS Basic" }, //bool = QoS Mod
		{ 16640, "port_mirror" }, //byte[10] second byte port id??
		{ 17152, "loop_prevention" }, //bool byte
		//{0000," "},
		};
