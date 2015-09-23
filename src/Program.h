/*
 * Program.h
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

class Program {
public:
	Program();
	virtual ~Program();
	int run();
	void setPort(int);
	void setPort();
	int src_port = 29809;
	int dst_port = 29808;
private:
	int discover();
};

#endif /* PROGRAM_H_ */
