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
		{ 7, table::STRING, "firmware_version" },
		{ 8, table::STRING, "hardware_version" },
		{ 9, table::DEC, "dhcp" }, //bool byte
		{ 19, table::DEC, "ports" }, //byte, maybe number of ports
		{ 4352, table::HEX, "igmp_snooping" }, //switching
		{ 4096, table::HEX, "port_settings" }, //switching
		{ 4608, table::HEX, "port_trunk" }, //byte[5] last byte bitmask??
		{ 8704, table::HEX, "802.1q vlan" }, //???

		{ 12288, table::HEX, "QoS Basic 1" }, //bool = QoS Mod
		{ 12289, table::HEX, "QoS Basic 2" }, //QoS
		{ 16640, table::HEX, "port_mirror" }, //byte[10] second byte port id??
		{ 16384, table::HEX, "port_statistics" }, //???
		{ 17152, table::HEX, "loop_prevention" }, //bool byte
		//{0000," "},
		};

static table snd_lookup = {

// TODO find out if id is unique in response
		{ 2, table::HEX, "system_info" }, //page sysinfo
		{ 9, table::HEX, "ip_config" }, //page sysinfo
		{ 10, table::HEX, "??? - 10" }, //after login
		{ 512, table::STRING, "login_user" }, //string
		{ 513, table::STRING, "new_user" }, //string
		{ 514, table::STRING, "login_password" }, //string
		{ 515, table::STRING, "new_passwoord" }, //string
		{ 2200, table::HEX, "vlan" }, //vlan

		{ 2305, table::HEX, "??? - 2305" }, //sent before login and before change hostname

		{ 4352, table::HEX, "igmp_snooping" }, //switching
		{ 4096, table::HEX, "port_settings" }, //switching
		{ 4608, table::HEX, "port_trunk" }, //byte[5] last byte bitmask??
		{ 8192, table::HEX, "mtu_vlan" }, //byte[2] first byte bool,	second byte port id
		{ 8449, table::HEX, "port_vlan1" }, //???
		{ 8448, table::HEX, "port_vlan2" }, //open page
		{ 8704, table::HEX, "802.1q vlan" }, //??? get vlan / set status
		{ 8705, table::HEX, "802.1q vlan" }, //???
		{ 8706, table::HEX, "802.1q vlan pvid" }, //????

		{ 12288, table::HEX, "QoS Basic 1" }, //bool = QoS Mod
		{ 12289, table::HEX, "QoS Basic 2" }, //QoS
		{ 16640, table::HEX, "port_mirror" }, //byte[10] second byte port id??
		{ 16384, table::HEX, "port_statistics" }, //???
		{ 17152, table::HEX, "loop_prevention" }, //bool byte
		//{0000," "},
		};
