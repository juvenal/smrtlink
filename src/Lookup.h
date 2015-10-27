/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include "table.h"

static table rcv_lookup = { { 1, table::STRING, "type" }, //string
		{ 2, table::STRING, "hostname" }, //string
		{ 3, table::HEX, "mac" }, //byte[6]
		{ 4, table::DEC, "ip_addr" }, //byte[4]
		{ 5, table::DEC, "ip_mask" }, //byte[4]
		{ 6, table::DEC, "gateway" }, //byte[4]
		{ 7, table::STRING, "firmware_version" }, //string
		{ 8, table::STRING, "hardware_version" }, //string
		{ 9, table::DEC, "dhcp" }, //bool byte
		{ 8704, table::HEX, "802.1q vlan" }, //???
		//{0000," "},
		};

static table snd_lookup = {

// TODO find out if id is unique in response
		{ 10, table::HEX, "???" }, //after login
		{ 2, table::HEX, "???" }, //after login
		{ 512, table::STRING, "login_user" }, //string
		{ 513, table::STRING, "new_user" }, //string
		{ 514, table::STRING, "login_password" }, //string
		{ 515, table::STRING, "new_passwoord" }, //string
		{ 2200, table::HEX, "vlan" }, { 2305, table::HEX, "???" }, //sent before login and before change hostname
		{ 4608, table::HEX, "port_trunk" }, //byte[5] last byte bitmask??
		{ 8192, table::HEX, "mtu_vlan" }, //byte[2] first byte bool,	second byte port id
		{ 8449, table::HEX, "port_vlan" }, //???

		{ 8704, table::HEX, "802.1q vlan" }, //??? get vlan / set status
		{ 8705, table::HEX, "802.1q vlan" }, //???
		{ 8706, table::HEX, "802.1q vlan pvid" }, //????

		{ 12288, table::HEX, "QoS Basic" }, //bool = QoS Mod
		{ 16640, table::HEX, "port_mirror" }, //byte[10] second byte port id??
		{ 17152, table::HEX, "loop_prevention" }, //bool byte
		//{0000," "},
		};
