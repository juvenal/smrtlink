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
    std::cout<<"\nParsing to document succeeded.\n";
























    ////////////////////////////////////////////////////////////////////////////
        // 2. Access values in document.

        printf("\nAccess values in document:\n");
        assert(json.IsObject());    // Document is a JSON value represents the root of DOM. Root can be either an object or array.

        assert(json.HasMember("hello"));
        assert(json["hello"].IsString());
        printf("hello = %s\n", json["hello"].GetString());

        // Since version 0.2, you can use single lookup to check the existing of member and its value:
        rapidjson::Value::MemberIterator hello = json.FindMember("hello");
        assert(hello != json.MemberEnd());
        assert(hello->value.IsString());
        assert(strcmp("world", hello->value.GetString()) == 0);
        (void)hello;

        assert(json["t"].IsBool());     // JSON true/false are bool. Can also uses more specific function IsTrue().
        printf("t = %s\n", json["t"].GetBool() ? "true" : "false");

        assert(json["f"].IsBool());
        printf("f = %s\n", json["f"].GetBool() ? "true" : "false");

        printf("n = %s\n", json["n"].IsNull() ? "null" : "?");

        assert(json["i"].IsNumber());   // Number is a JSON type, but C++ needs more specific type.
        assert(json["i"].IsInt());      // In this case, IsUint()/IsInt64()/IsUInt64() also return true.
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
            (void)y;

            // Iterating array with iterators
            printf("a = ");
            for (rapidjson::Value::ConstValueIterator itr = a.Begin(); itr != a.End(); ++itr)
                printf("%d ", itr->GetInt());
            printf("\n");
        }

        // Iterating object members
        static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
        for (rapidjson::Value::ConstMemberIterator itr = json.MemberBegin(); itr != json.MemberEnd(); ++itr)
            printf("Type of member %s is %s\n", itr->name.GetString(), kTypeNames[itr->value.GetType()]);



	return 0;
}

std::string Switch::toString() {
	////////////////////////////////////////////////////////////////////////////
	    // 3. Modify values in document.

	    // Change i to a bigger number
	    {
	        uint64_t f20 = 1;   // compute factorial of 20
	        for (uint64_t j = 1; j <= 20; j++)
	            f20 *= j;
	        json["i"] = f20;    // Alternate form: document["i"].SetUint64(f20)
	        assert(!json["i"].IsInt()); // No longer can be cast as int or uint.
	    }

	    // Adding values to array.
	    {
	    	rapidjson::Value& a = json["a"];   // This time we uses non-const reference.
	        rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
	        for (int i = 5; i <= 10; i++)
	            a.PushBack(i, allocator);   // May look a bit strange, allocator is needed for potentially realloc. We normally uses the document's.

	        // Fluent API
	        a.PushBack("Lua", allocator).PushBack("Mio", allocator);
	    }

	    // Making string values.

	    // This version of SetString() just store the pointer to the string.
	    // So it is for literal and string that exists within value's life-cycle.
	    {
	        json["hello"] = "hostname"; //settings.hostname;    // This will invoke strlen()
	        // Faster version:
	        // document["hello"].SetString("rapidjson", 9);
	    }

	    // This version of SetString() needs an allocator, which means it will allocate a new buffer and copy the the string into the buffer.
	    rapidjson::Value author;
	    {
	        char buffer[10];
	        int len = sprintf(buffer, "%s %s", "Milo", "Yip");  // synthetic example of dynamically created string.

	        author.SetString(buffer, static_cast<size_t>(len), json.GetAllocator());
	        // Shorter but slower version:
	        // document["hello"].SetString(buffer, document.GetAllocator());

	        // Constructor version:
	        // Value author(buffer, len, document.GetAllocator());
	        // Value author(buffer, document.GetAllocator());
	        memset(buffer, 0, sizeof(buffer)); // For demonstration purpose.
	    }
	    // Variable 'buffer' is unusable now but 'author' has already made a copy.
	    json.AddMember("author", author, json.GetAllocator());

	    assert(author.IsNull());        // Move semantic for assignment. After this variable is assigned as a member, the variable becomes null.















    std::cout<<"\nModified JSON with reformatting:\n";
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    json.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    return sb.GetString();
}


