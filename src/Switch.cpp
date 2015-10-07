/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include <string>
#include "Types/bytes.h"
#include "Switch.h"

void Switch::parse(datasets arr) {
	device.type = arr[1].value;
	settings.hostname = arr[2].value;
	device.mac = arr[3].value;
	settings.ip_addr = arr[4].value;
	settings.ip_mask = arr[5].value;
	settings.gateway = arr[6].value;
	device.firmware_version = arr[7].value;
	device.hardware_version = arr[8].value;
	settings.dhcp=arr[9].value[0];
}

