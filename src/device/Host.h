/*
 * Host.h
 *
 *  Created on: 11.09.2015
 *      Author: jdi
 */

#ifndef HOST_H_
#define HOST_H_

#include "../Types.h"

class Host {
public:
	Host();
	virtual ~Host() {}
	bytes getMac();
	bytes getIp();
};

#endif /* HOST_H_ */
