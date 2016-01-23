#!/bin/sh
clear
echo SmrtLink Test

echo bin/smrtlink encode 00:11:22:33:44:55:66:77:88:99
bin/smrtlink encode 00:11:22:33:44:55:66:77:88:9

echo bin/smrtlink -i eth0 list
bin/smrtlink -i eth0 list

echo bin/smrtlink -i eth6 list
bin/smrtlink -i eth6 list

echo bin/smrtlink list
bin/smrtlink list

echo bin/smrtlink -i wlan0 list
bin/smrtlink -i wlan0 list
