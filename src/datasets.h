/*
 * Datasets.h
 *
 *  Created on: 02.10.2015
 *      Author: jdi
 */

#ifndef DATASETS_H_
#define DATASETS_H_

#include <map>
#include "bytes.h"

struct dataset {
	short type;
	short len;
	bytes value;
};

class datasets : public std::vector<dataset> {
public:
	datasets(){};
	datasets(std::initializer_list<dataset> s)
	{
		for (dataset b : s) {
			//(*this)[b.type]=b;
			push_back(b);
		}
    }
};

#endif /* DATASETS_H_ */
