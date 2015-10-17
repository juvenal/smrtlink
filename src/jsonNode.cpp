/*
 * jsonNode.cpp
 *
 *  Created on: 17.10.2015
 *      Author: jdi
 */

#include "jsonNode.h"

jsonNode::jsonNode(const std::string &x, doc &root) {
	super(rapidjson::kStringType);
	char buffer[30];
	int len = sprintf(buffer, "%s", x.c_str());
	this->SetString(buffer, static_cast<size_t>(len), root.GetAllocator());
	memset(buffer, 0, sizeof(buffer));
}

jsonNode::jsonNode(const ipAddr &x, doc &root) {
	super(rapidjson::kStringType);
	char buffer[16];
	int len = sprintf(buffer, "%d.%d.%d.%d", x[0], x[1],
			x[2], x[3]);
	this->SetString(buffer, static_cast<size_t>(len), root.GetAllocator());
	memset(buffer, 0, sizeof(buffer));
}

jsonNode::jsonNode(const macAddr &x, doc &root) {
	super(rapidjson::kStringType);
	char buffer[18];
	int len = sprintf(buffer, "%02x:%02x:%02x:%02x:%02x:%02x", x[0], x[1],
			x[2], x[3], x[4], x[5]);
	this->SetString(buffer, static_cast<size_t>(len), root.GetAllocator());
	memset(buffer, 0, sizeof(buffer));
}

jsonNode::jsonNode(const vlan &x, doc &root) {
	super(rapidjson::kObjectType);
	AddMember("id", x.vlan_id, root.GetAllocator());
	AddMember("name", jsonNode(x.name, root), root.GetAllocator());
	AddMember("tagged-members", jsonNode(x.tagged_member, root),
			root.GetAllocator());
	AddMember("untagged-members", jsonNode(x.untagged_member, root),
			root.GetAllocator());
}

jsonNode::jsonNode(const port &x, doc &root) {
	super(rapidjson::kObjectType);
	AddMember("id", x.id, root.GetAllocator());
	AddMember("status", x.status, root.GetAllocator());
	AddMember("pvid", x.pvid, root.GetAllocator());
}
