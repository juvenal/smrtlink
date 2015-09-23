/*
 * Device.h
 *
 *  Created on: 01.09.2015
 *      Author: jdi
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <string>

class Device {
public:
	Device();
	virtual ~Device();

	int getName(void) {
		return 5;
	}
};

#endif /* DEVICE_H_ */
