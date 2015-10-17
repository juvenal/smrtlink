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
	for (auto a : arr) {
		parse(a.second);
	}
	return 0;
}

int Switch::parse(dataset d) {
	auto lookup = (options.flags & FLAG_REVERSE) ? snd_lookup : rcv_lookup;
	if (d.type == lookup["type"]) {
		device.type = d.value;
	}
	if (d.type == lookup["mac"]) {
		device.mac = d.value;
	}
	if (d.type == lookup["firmware_version"]) {
		device.firmware_version = d.value;
	}
	if (d.type == lookup["hardware_version"]) {
		device.hardware_version = d.value;
	}
	if (d.type == lookup["hostname"]) {
		settings.hostname = d.value;
	}
	if (d.type == lookup["ip_addr"]) {
		settings.ip_addr = d.value;
	}
	if (d.type == lookup["ip_mask"]) {
		settings.ip_mask = d.value;
	}
	if (d.type == lookup["gateway"]) {
		settings.gateway = d.value;
	}
	if (d.type == lookup["dhcp"]) {
		settings.dhcp = d.value[0];
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

	}
	/*
	 json.AddMember("ports", jsonNode(ports, json), allocator);
	 json.AddMember("vlans", jsonNode(vlans, json), allocator);
	 */


	// Since version 0.2, you can use single lookup to check the existing of member and its value:
	/*
	rapidjson::Value::MemberIterator hello = json.FindMember("hello");
	assert(hello != json.MemberEnd());
	assert(hello->value.IsString());
	assert(strcmp("world", hello->value.GetString()) == 0);
	(void) hello;

	assert(json["t"].IsBool()); // JSON true/false are bool. Can also uses more specific function IsTrue().
	printf("t = %s\n", json["t"].GetBool() ? "true" : "false");

	assert(json["f"].IsBool());
	printf("f = %s\n", json["f"].GetBool() ? "true" : "false");

	printf("n = %s\n", json["n"].IsNull() ? "null" : "?");

	assert(json["i"].IsNumber()); // Number is a JSON type, but C++ needs more specific type.
	assert(json["i"].IsInt()); // In this case, IsUint()/IsInt64()/IsUInt64() also return true.
	printf("i = %d\n", json["i"].GetInt()); // Alternative (int)document["i"]

	assert(json["pi"].IsNumber());
	assert(json["pi"].IsDouble());
	printf("pi = %g\n", json["pi"].GetDouble());

	{
		const rapidjson::Value& a = json["a"]; // Using a reference for consecutive access is handy and faster.
		assert(a.IsArray());
		for (rapidjson::SizeType i = 0; i < a.Size(); i++) // rapidjson uses SizeType instead of size_t.
			printf("a[%d] = %d\n", i, a[i].GetInt());

		int y = a[0].GetInt();
		(void) y;

		// Iterating array with iterators
		printf("a = ");
		for (rapidjson::Value::ConstValueIterator itr = a.Begin();
				itr != a.End(); ++itr)
			printf("%d ", itr->GetInt());
		printf("\n");
	}

	// Iterating object members
	static const char* kTypeNames[] = { "Null", "False", "True", "Object",
			"Array", "String", "Number" };
	for (rapidjson::Value::ConstMemberIterator itr = json.MemberBegin();
			itr != json.MemberEnd(); ++itr)
		printf("Type of member %s is %s\n", itr->name.GetString(),
				kTypeNames[itr->value.GetType()]);
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

