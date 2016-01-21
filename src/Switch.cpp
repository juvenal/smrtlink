/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include <string>
#include "Types.h"
#include "Switch.h"
<<<<<<< HEAD
#include "Lookup.h"
=======
#include "lookup.h"
>>>>>>> 3ef2da7b7a10c8b34f20c452acc0f8d0ffc17db5
#include "Constant.h"
#include "table.h"

int Switch::parse(datasets arr) {
    for (dataset a : arr) {
        parse(a);
    }
    return 0;
}

int Switch::parse(dataset d) {
<<<<<<< HEAD
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
=======
    switch (d.type) {
    case RCV_TYPE:
        device.type = d.value;
        break;
    case RCV_MAC:
        device.mac = d.value;
        break;
    case FIRMWARE_VERSION:
        device.firmware_version = d.value;
        break;
    case HARDWARE_VERSION:
        device.hardware_version = d.value;
        break;
    case PORTS:
        device.ports = d.value[0];
        break;
    case HOSTNAME:
        settings.hostname = d.value;
        break;
    case IP_ADDR:
        settings.ip_addr = d.value;
        break;
    case IP_MASK:
        settings.ip_mask = d.value;
        break;
    case GATEWAY:
        settings.gateway = d.value;
        break;
    case DHCP_ENABLED:
        settings.dhcp = d.value[0];
        break;
    case LOOP_PREVENTION:
        settings.loop_prevention = d.value[0];
        break;
    case QOS_BASIC_ENABLED:
        settings.qos_enabled = d.value[0];
        break;
    case VLAN_ENABLED:
        settings.vlan_enabled = d.value[0];
        break;
    }
    return 0;
}

>>>>>>> 3ef2da7b7a10c8b34f20c452acc0f8d0ffc17db5
