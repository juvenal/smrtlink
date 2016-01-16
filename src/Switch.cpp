/*
 * Switch.cpp
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#include <string>
#include "Types.h"
#include "Switch.h"
#include "Lookup.h"
#include "jsonNode.h"
#include "Options.h"

int Switch::parse(datasets arr) {
	for (dataset a : arr) {
		parse(a);
	}
	return 0;
}

int Switch::parse(dataset d) {
	auto lookup = (options.flags & FLAG_REVERSE) ? snd_lookup : rcv_lookup;
	switch (d.type) {
	case lookup["type"]:
		device.type = d.value;
		return 0;
	case lookup["mac"]:
		device.mac = d.value;
		return 0;
	case lookup["ip_addr"]:
		device.firmware_version = d.value;
		return 0;
	case lookup["ip_mask"]:
		device.firmware_version = d.value;
		return 0;
	case lookup["gateway"]:
		device.firmware_version = d.value;
		return 0;
	case lookup["firmware_version"]:
		device.firmware_version = d.value;
		return 0;
	case lookup["hardware_version"]:
		device.hardware_version = d.value;
		return 0;
	case lookup["ports"]:
		device.ports = d.value[0];
		return 0;
	case lookup["hostname"]:
		settings.hostname = d.value;
		return 0;
	case lookup["ip_addr"]:
		settings.ip_addr = d.value;
		return 0;
	case lookup["ip_mask"]:
		settings.ip_mask = d.value;
		return 0;
	case lookup["gateway"]:
		settings.gateway = d.value;
		return 0;
	case lookup["dhcp"]:
		settings.dhcp = d.value[0];
		return 0;
	case lookup["loop_prevention"]:
		settings.loop_prevention = d.value[0];
		return 0;
	case lookup["qos_basic_enabled"]:
		settings.qos_enabled = d.value[0];
		return 0;
	case lookup["vlan_enabled"]:
		settings.vlan_enabled = d.value[0];
		return 0;
	}
	return 0;
}

int Switch::parse(std::string str) {

	if (json.Parse(str.c_str()).HasParseError())
		return 1;
	if (options.flags & FLAG_DEBUG)
		std::cout << "\nParsing to document succeeded.\n";

	if (json.IsObject()) {
		if (json.HasMember("hostname"))
			settings.hostname = json["hostname"].GetString();
		if (json.HasMember("type"))
			device.type = json["type"].GetString();
		if (json.HasMember("hardware_version"))
			device.hardware_version = json["hardware_version"].GetString();
		if (json.HasMember("firmware_version"))
			device.hardware_version = json["firmware_version"].GetString();
		if (json.HasMember("ports") && json["ports"].IsArray()) {
			const rapidjson::Value& a = json["ports"];
			for (rapidjson::SizeType i = 0; i < a.Size(); i++)
				if (a[i].IsObject()) {
					port p;
					if (a[i].HasMember("id") && a[i]["id"].IsInt()) {
						p.id = a[i]["id"].GetInt();
						std::cout << a[i]["id"].GetInt() << "\n";
					}
					ports.push_back(p);
				}
		}
		if (json.HasMember("vlans") && json["vlans"].IsArray()) {
			const rapidjson::Value& a = json["vlans"];
			for (rapidjson::SizeType i = 0; i < a.Size(); i++)
				if (a[i].IsObject()) {
					vlan v;
					if (a[i].HasMember("name") && a[i]["name"].IsString()) {
						v.name = a[i]["name"].GetString();
						std::cout << a[i]["name"].GetString() << "\n";
					}
					vlans.push_back(v);
				}
		}

	}

	/*


	 {
	 const rapidjson::Value& a = json["a"];
	 assert(a.IsArray());
	 for (rapidjson::SizeType i = 0; i < a.Size(); i++)
	 printf("a[%d] = %d\n", i, a[i].GetInt());

	 int y = a[0].GetInt();
	 (void) y;

	 */
	return 0;
}

std::string Switch::toString() {

	if (!json.IsObject()) {
		json.SetObject();
	}
	rapidjson::Document::AllocatorType& allocator = json.GetAllocator();

	json.AddMember("hostname", jsonNode(settings.hostname, json), allocator);
	json.AddMember("ip", jsonNode(settings.ip_addr, json), allocator);
	json.AddMember("netmask", jsonNode(settings.ip_mask, json), allocator);
	json.AddMember("gateway", jsonNode(settings.gateway, json), allocator);
	json.AddMember("type", jsonNode(device.type, json), allocator);
	json.AddMember("hardware_version", jsonNode(device.hardware_version, json),
			allocator);
	json.AddMember("firmware_version", jsonNode(device.firmware_version, json),
			allocator);
	json.AddMember("ports", jsonNode(ports, json), allocator);
	json.AddMember("vlans", jsonNode(vlans, json), allocator);

	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
	json.Accept(writer);
	return sb.GetString();
}

