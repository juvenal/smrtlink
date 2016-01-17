/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include "table.h"

static table rcv_lookup = { //
		{ 1, table::STRING, "type" }, //+string
		{ 2, table::STRING, "hostname" }, //+string
		{ 3, table::HEX, "mac" }, //+byte[6]
		{ 4, table::DEC, "ip_addr" }, //+byte[4]
		{ 5, table::DEC, "ip_mask" }, //+byte[4]
		{ 6, table::DEC, "gateway" }, //+byte[4]
		{ 7, table::STRING, "firmware_version" },//+
		{ 8, table::STRING, "hardware_version" },//+
		{ 9, table::DEC, "dhcp" }, //+bool byte
		{ 10, table::DEC, "ports" }, //+byte, maybe number of ports

		{ 4352, table::HEX, "igmp_snooping" }, //???
		{ 4096, table::HEX, "port_settings" }, //+per port
		{ 4608, table::HEX, "port_trunk" }, //byte[5] last byte bitmask??

		{ 8192, table::HEX, "mtu_vlan" }, //byte[2] first byte bool,second byte port id
		{ 8448, table::HEX, "port_vlan_1" }, //???
		{ 8450, table::HEX, "port_vlan_2" }, //???
		{ 8704, table::HEX, "vlan_enabled" }, //+bool byte
		{ 8705, table::HEX, "vlan" }, //+one set per vlan
		{ 8706, table::HEX, "vlan_pvid" }, //+per port
		{ 8707, table::HEX, "vlan ?????" }, //????

		{ 12288, table::HEX, "qos_basic_enabled" }, //+bool = QoS Mod
		{ 12289, table::HEX, "qos_basic" }, //+per port ???
		{ 12544, table::HEX, "bandwidth_control_1" }, //+per port ???
		{ 12545, table::HEX, "bandwidth_control_2" }, //+per port ???
		{ 12800, table::HEX, "storm_control" }, //+per port ???
		{ 16640, table::HEX, "port_mirror" }, //byte[10] second byte port id???
		{ 16384, table::HEX, "port_statistics" }, //+per port ???
		{ 16896, table::HEX, "cable_test" }, //+per port ???
		{ 17152, table::HEX, "loop_prevention" }, //+bool byte

		//{0000," "},
		};

static table snd_lookup = {

		// TODO find out if id is unique in response
		{ 2, table::HEX, "system_info" }, //page sysinfo
		{ 9, table::HEX, "ip_config" }, //page sysinfo
		{ 10, table::HEX, "ports" }, //after login
		{ 512, table::STRING, "login_user" }, //string
		{ 513, table::STRING, "new_user" }, //string
		{ 514, table::STRING, "login_password" }, //string
		{ 515, table::STRING, "new_passwoord" }, //string
		{ 773, table::HEX, "reboot" }, //bool byte = save config

		{ 1280, table::ACTION, "reset" }, //
		{ 1536, table::ACTION, "flash" }, //update firmware

		{ 2200, table::HEX, "vlan" }, //vlan
		{ 2304, table::ACTION, "save" }, //save
		{ 2305, table::ACTION, "ping" }, //sent before SET ???

		{ 4352, table::HEX, "igmp_snooping" }, //switching
		{ 4096, table::HEX, "port_settings" }, //switching
		{ 4608, table::HEX, "port_trunk" }, //byte[5] last byte bitmask??

		{ 8192, table::HEX, "mtu_vlan" }, //byte[2] first byte bool,	second byte port id
		{ 8449, table::HEX, "port_vlan ???" }, //???
		{ 8448, table::HEX, "port_vlan" }, //open page
		{ 8704, table::HEX, "vlan_enabled" }, //??? get vlan / set status
		{ 8705, table::HEX, "vlan" }, // per vlan
		{ 8706, table::HEX, "vlan_pvid" }, //per port

		{ 12288, table::HEX, "qos_basic_enabled" }, //bool = QoS Mod
		{ 12289, table::HEX, "qos_basic" }, //per port
		{ 12544, table::HEX, "bandwidth_control_1" }, //per port
		{ 12545, table::HEX, "bandwidth_control_2" }, //per port
		{ 12800, table::HEX, "storm_control" }, //???
		{ 16640, table::HEX, "port_mirror" }, //byte[10] second byte port id??
		{ 16384, table::HEX, "port_statistics" }, //???
		{ 17152, table::HEX, "loop_prevention" }, //bool byte

		//{0000," "},
		};
