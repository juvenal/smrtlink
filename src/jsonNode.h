/*
 * jsonNode.h
 *
 *  Created on: 17.10.2015
 *      Author: jdi
 */

#ifndef JSONNODE_H_
#define JSONNODE_H_

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/prettywriter.h"
#include "Switch.h"

class jsonNode: public rapidjson::Value {
        typedef rapidjson::Value super;
        typedef rapidjson::Document doc;
    public:
        jsonNode(const std::string&, doc&);
        jsonNode(const macAddr&, doc&);
        jsonNode(const ipAddr&, doc&);
        jsonNode(const vlan&, doc&);
        jsonNode(const port&, doc&);

        template<class T>
        jsonNode(const T &templ_arg, doc &root) {
            std::cerr << "Not serializable Type: " << typeid(T).name() << "\n";
        }

        template<class T>
        jsonNode(const std::vector<T> &x, doc &root) {
            super(rapidjson::kArrayType);
            for (T y : x)
                PushBack(jsonNode(y, root), root.GetAllocator());
        }
};

#endif /* JSONNODE_H_ */
