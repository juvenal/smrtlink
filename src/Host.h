/*
 * Host.h
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#ifndef HOST_H_
#define HOST_H_

#include "Types.h"

class Host {
public:
	Host();
	byteArray<6> getMac();
	byteArray<4> getIp(std::string);
};

#endif /* HOST_H_ */
