/*
 * Switch.h
 *
 *  Created on: 29.09.2015
 *      Author: jdi
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include <string>
#include <map>
#include "Types.h"
#include "Types/bytes.h"
#include "Types/datasets.h"

#define DEFAULT_USER "admin"
#define DEFAULT_PASS "admin"

static std::map<int,std::string> rcv_lookup= {
	{	1, "type"},//string
	{	2, "hostname"},//string
	{	3, "mac"},//byte[6]
	{	4, "ip_addr"},//byte[4]
	{	5, "ip_mask"},//byte[4]
	{	6, "gateway"},//byte[4]
	{	7, "firmware_version"},//string
	{	8, "hardware_version"},//string
	{	9, "dhcp"}};//bool byte

static std::map<int,std::string> snd_lookup= {
		{10,"???"},//after login
		{2,"???"},//after login
		{512,"login_user"},//string
		{513,"new_user"},//string
		{514,"login_password"},//string
		{515,"new_passwoord"},//string
		{2200,"vlan"},
		{2305,"???"},//sent before login and before change hostname
		{4608,"port_trunk"},//byte[5] last byte bitmask??
		{8192,"mtu_vlan"},//byte[2] first byte bool,	second byte port id
		{8449,"port_vlan"},//???
		{8705,"802.1q vlan"},//???
		{8706,"802.1q vlan pvid"},//????
		{12288,"QoS Basic"},//bool = QoS Mod
		{16640,"port_mirror"},//byte[10] second byte port id??
		{17152,"loop_prevention"},//bool byte
		//{0000," "},
};


struct vlan {
	int vlan_id;
	std::string name;
};

struct port {
	byte id;
	byte status;
	struct {
		std::vector<vlan*> tagged;
		std::vector<vlan*> untagged;
		int pvid;
	} vlan;
};

class Switch {
public:
	Switch() {
	}
	void parse(datasets);
	struct {
		std::string type;
		std::string hardware_version;
		std::string firmware_version;
		macAddr mac { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	} device;
	struct {
		std::string password = DEFAULT_PASS;
		std::string username = DEFAULT_USER;
		std::string hostname;
		ipAddr ip_addr { 0, 0, 0, 0, };
		ipAddr ip_mask;
		ipAddr gateway;
		bool dhcp;
	} settings;
private:
	std::vector<vlan> vlans;
	std::vector<port> ports;
};

#endif /* SWITCH_H_ */
