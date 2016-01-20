/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include <string>
#include "Types.h"
#include "Switch.h"
#include "Lookup.h"
#include "Constant.h"
#include "table.h"

int Switch::parse(datasets arr) {
	for (dataset a : arr) {
		parse(a);
	}
	return 0;
}

int Switch::parse(dataset d) {
	auto lookup = (options.flags & FLAG_REVERSE) ? snd_lookup : rcv_lookup;
	std::string id = lookup.exists(d.type)?lookup[d.type]:"unknown";
	if (d.type == lookup["type"]) {
		device.type = d.value;
	}
	else if (id == "mac") {
		device.mac = d.value;
	}
	else if (d.type == lookup["firmware_version"]) {
		device.firmware_version = d.value;
	}
	else if (id == "hardware_version") {
		device.hardware_version = d.value;
	}
	else if (id == "ports") {
		device.ports = d.value[0];
	}
	else if (id == "hostname") {
		settings.hostname = d.value;
	}
	else if (id == "ip_addr") {
		settings.ip_addr = d.value;
	}
	else if (id == "ip_mask") {
		settings.ip_mask = d.value;
	}
	else if (id == "gateway") {
		settings.gateway = d.value;
	}
	else if (id == "dhcp_enabled") {
		settings.dhcp = d.value[0];
	}
	else if (id == "loop_prevention") {
		settings.loop_prevention = d.value[0];
	}
	else if (id == "qos_basic_enabled") {
		settings.qos_enabled = d.value[0];
	}
	else if (id == "vlan_enabled") {
		settings.vlan_enabled = d.value[0];
	}
	return 0;
}
