/*
 * Interactive.h
 *
 *  Created on: 27.01.2016
 *      Author: jedi
 */

#ifndef INTERACTIVE_H_
#define INTERACTIVE_H_

class Interactive {
    public:
        Interactive() {
        }
        virtual ~Interactive() {
        }
        int loop();
        int single(std::vector<std::string> v);
};

#endif /* INTERACTIVE_H_ */
