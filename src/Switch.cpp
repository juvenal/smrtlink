/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include <string>
#include "Types.h"
#include "Switch.h"
#include "lookup.h"
#include "Constant.h"
#include "table.h"

int Switch::parse(datasets arr) {
    for (dataset a : arr) {
        parse(a);
    }
    return 0;
}

int Switch::print() {
    std::cout << "\t" << settings.hostname << " (" << device.type << ")\tMAC: "
            << device.mac << "\tIP: " << settings.ip_addr << "\n";
    return 0;
}

int Switch::parse(dataset d) {
    switch (d.type) {
    case TYPE:
        device.type = d.value;
        break;
    case MAC:
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
