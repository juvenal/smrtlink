/*
 * Program.cpp
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */
#include <iostream>
#include <algorithm>

#include "Constant.h"
#include "Program.h"
#include "File.h"
#include "Host.h"
#include "Socket.h"
#include "Switch.h"
#include "Packet.h"
#include "lookup.h"
#include "table.h"

int printHeader(Packet p) {
    if (options.flags & FLAG_HEADER) {
        if (options.flags & FLAG_HEX) {
            std::cout << "Received Header:\n\t" << p.getHead() << "\n";
        } else {
            p.printHeader();
            printf("\n");
        }
    }
    return 0;
}

int printPacket(Packet p) {
<<<<<<< HEAD
	if (options.flags & FLAG_HEX) {
		std::cout << "Received Payload:\n\t" << p.getBody() << "\n";
	} else {
		for (dataset d : p.getPayload()) {
			auto lookup =
					(options.flags & FLAG_REVERSE) ? snd_lookup : rcv_lookup;
			if (lookup.exists(d.type)) {
				const table::set *s = lookup.get(d.type);
				if (d.len > 0) {
					switch (s->format) {
					case table::STRING:
						std::cout << "+\t" << s->name << " = " << &d.value[0]
								<< "\n";
						break;
					case table::BOOL:
						std::cout << "+\t" << s->name << " = " << (d.value[0]?"YES":"NO")
								<< "\n";
						break;
					case table::HEX:
						std::cout << "+\t" << s->name << " = " << d.value
								<< "\n";
						break;
					case table::DEC:
						std::cout << "+\t" << s->name << " = ";
						if (d.value.size() > 0)
							std::cout << std::dec << (unsigned) d.value[0];
						for (unsigned i = 1; i < d.value.size(); i++)
							std::cout <<  std::dec << "." << (unsigned) d.value[i];
						std::cout << "\n";
						break;
					case table::ACTION:
						std::cout << "Error:" << s->name
								<< " is marked as 'action' but carries payload."
								<< d.value << "\n";
						break;
					default:
						std::cout << "+\t" << s->name << " = " << d.value
								<< "\n";
						break;
					}
				} else { //empty
					std::cout << std::dec << ">\t" << s->name << "\n";
				}
			} else { //unknown id
				if (d.len > 0) {
					std::cout << "##\t" << d.type << ":\n\t";
					std::cout << std::hex << d.value << std::dec << "\n";
				} else { //empty
					std::cout << "#>\t" << d.type << "\n";
				}
			}
		}
	}
	return 0;
=======
    if (options.flags & FLAG_HEX) {
        std::cout << "Received Payload:\n\t" << p.getBody() << "\n";
    } else {
        for (dataset d : p.getPayload()) {
            auto lookup =
                    (options.flags & FLAG_REVERSE) ? snd_lookup : rcv_lookup;
            if (lookup.exists(d.type)) {
                table::set s = lookup[d.type];
                if (d.len > 0) {
                    switch (s.format) {
                    case table::STRING:
                        std::cout << "+\t" << s.name << " = " << &d.value[0]
                                << "\n";
                        break;
                    case table::BOOL:
                        std::cout << "+\t" << s.name << " = "
                                << (d.value[0] ? "YES" : "NO") << "\n";
                        break;
                    case table::HEX:
                        std::cout << "+\t" << s.name << " = " << d.value
                                << "\n";
                        break;
                    case table::DEC:
                        std::cout << "+\t" << s.name << " = ";
                        if (d.value.size() > 0)
                            std::cout << std::dec << (unsigned) d.value[0];
                        for (unsigned i = 1; i < d.value.size(); i++)
                            std::cout << std::dec << "."
                                    << (unsigned) d.value[i];
                        std::cout << "\n";
                        break;
                    case table::ACTION:
                        std::cout << "Error:" << s.name
                                << " is marked as 'action' but carries payload."
                                << d.value << "\n";
                        break;
                    default:
                        std::cout << "+\t" << s.name << " = " << d.value
                                << "\n";
                        break;
                    }
                } else { //empty
                    std::cout << std::dec << ">\t" << s.name << "\n";
                }
            } else { //unknown id
                if (d.len > 0) {
                    std::cout << "##\t" << d.type << ":\n\t";
                    std::cout << std::hex << d.value << std::dec << "\n";
                } else { //empty
                    std::cout << "#>\t" << d.type << "\n";
                }
            }
        }
    }
    return 0;
>>>>>>> 3ef2da7b7a10c8b34f20c452acc0f8d0ffc17db5
}

int Program::list() {

    std::cout << "List:\n";
    Packet p = Packet(Packet::DISCOVERY);
    p.setHostMac(host.getMac());
    p.setPayload( { });
    bytes b = p.getBytes();
    p.encode(b);

    try {
        sock->setHostIp(host.getIp());
        sock->init(DST_PORT, SRC_PORT);
        sock->callback =
                [this](Packet a) {
                    printHeader(a);
                    if (options.flags & FLAG_HEX) {
                        std::cout <<"Received Payload:\n"<<a.getBody()<<"\n";
                    } else {
                        datasets d =a.getPayload();
                        Switch sw = Switch();
                        sw.parse(d);
                        File f;
                        f.write(sw.toString());
                        std::cout <<"\t"<<sw.settings.hostname<<" ("<< sw.device.type<<")\tMAC: "<<sw.device.mac<<"\tIP: "<<sw.settings.ip_addr<<"\n";
                    }
                    return 1;
                };
        sock->send(b);
        io_service->run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 1;
}

int Program::sniff() {
    printf("Listening:\n");
    try {
        boost::asio::io_service io_service;
        Socket s(io_service);
        s.setHostIp(host.getIp());
        s.init(DST_PORT, SRC_PORT);
        s.callback = [](Packet p) {
            std::cout << p.opCodeToString() << "\n";
            printHeader(p);
            printPacket(p);
            return 0;
        };
        s.listen();
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 1;
}

int Program::encode(std::string s) {
    bytes d(s);
    Packet p = Packet(Packet::DISCOVERY);
    p.encode(d);
    std::cout << d << std::endl;
    return 0;
}

int Program::setProperty() {
    return 0;
}

int Program::getProperty() {
<<<<<<< HEAD
	std::cout << "List:\n";
	Packet p = Packet(Packet::DISCOVERY);
	p.setHostMac(host.getMac());
	p.setPayload( { });
	bytes b = p.getBytes();
	p.encode(b);
	auto s = sock;
	try {
		sock->setHostIp(host.getIp());
		sock->init(DST_PORT, SRC_PORT);
		sock->callback =
				[this](Packet a) {
					auto s = sock;
					datasets d =a.getPayload();
					Switch sw = Switch();
					sw.parse(d);
					std::cout <<"Devices:\n\t"<<sw.settings.hostname<<" ("<< sw.device.type<<")\tMAC: "<<sw.device.mac<<"\tIP: "<<sw.settings.ip_addr<<"\n";

					Packet p = Packet(Packet::GET);
					p.setSwitchMac(a.getSwitchMac());
					p.setHostMac(host.getMac());
					datasets t = { {snd_lookup["ping"], 0, {}}};
					p.setPayload(t);
					bytes c = p.getBytes();
					p.encode(c);
					sock->callback =
					[this](Packet a) {
						auto s = sock;
						datasets d =a.getPayload();
						Switch sw = Switch();
						sw.parse(d);
						Packet p = Packet(Packet::SET);
						p.setSwitchMac(a.getSwitchMac());
						p.setHostMac(host.getMac());
						datasets t = {
								{snd_lookup["login_user"], (short)(options.user.length()), options.user},
								{snd_lookup["login_password"], (short)(options.password.length()), options.password}
						};
						std::cout<<options.user<<std::endl<<options.password<<std::endl;
						p.setPayload(t);
						bytes c = p.getBytes();
						p.encode(c);

						sock->callback =
						[this](Packet a) {
							std::cout << a.opCodeToString() << "\n";
							printHeader(a);
							printPacket(a);
							return 0;
						};
						sock->send(c);
						return 0;
					};

					sock->send(c);
					return 0;
				};
		sock->send(b);
		io_service->run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 1;
=======
    std::cout << "List:\n";
    Packet p = Packet(Packet::DISCOVERY);
    p.setHostMac(host.getMac());
    p.setPayload( { });
    bytes b = p.getBytes();
    p.encode(b);
    auto s = sock;
    try {
        sock->setHostIp(host.getIp());
        sock->init(DST_PORT, SRC_PORT);
        sock->callback =
                [this](Packet a) {
                    auto s = sock;
                    datasets d =a.getPayload();
                    Switch sw = Switch();
                    sw.parse(d);
                    std::cout <<"\t"<<sw.settings.hostname<<" ("<< sw.device.type<<")\tMAC: "<<sw.device.mac<<"\tIP: "<<sw.settings.ip_addr<<"\n";

                    Packet p = Packet(Packet::GET);
                    p.setSwitchMac(a.getSwitchMac());
                    p.setHostMac(host.getMac());
                    datasets t = { {SND_PING, 0, {}}};
                    p.setPayload(t);
                    bytes c = p.getBytes();
                    p.encode(c);

                    sock->callback =
                    [this](Packet a) {
                        auto s = sock;
                        datasets d =a.getPayload();
                        Switch sw = Switch();
                        sw.parse(d);
                        Packet p = Packet(Packet::SET);
                        p.setSwitchMac(a.getSwitchMac());
                        p.setTokenId(a.getTokenId());
                        p.setHostMac(host.getMac());
                        bytes n = options.user;
                        bytes w = options.password;
                        n.push_back('\0');
                        w.push_back('\0');
                        datasets t = {
                            {   LOGIN_USER, (short)(n.size()), n},
                            {   LOGIN_PASSWORD, (short)(w.size()), w},
                            {   REBOOT, 1, {0}}
                        };
                        p.setPayload(t);
                        bytes c = p.getBytes();
                        p.encode(c);

                        sock->callback =
                        [this](Packet a) {
                            std::cout << a.opCodeToString() << "\n";
                            printHeader(a);
                            printPacket(a);
                            return 0;
                        };
                        sock->send(c);
                        return 0;
                    };

                    sock->send(c);
                    return 0;
                };
        sock->send(b);
        io_service->run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 1;
>>>>>>> 3ef2da7b7a10c8b34f20c452acc0f8d0ffc17db5
}

int Program::save() {
    Switch sw = Switch();
    sw.settings.hostname = "testname.lan";
    File f;
    f.write(sw.toString());
    return 1;
}

int Program::restore() {
    File f;
    Switch sw;
    sw.parse(f.read());
    std::cout << "Devices:\n\t" << sw.settings.hostname << " ("
            << sw.device.type << ")\tMAC: " << sw.device.mac << "\tIP: "
            << sw.settings.ip_addr << "\n";
    return 1;
}

int Program::flash() {

    return 0;
}

int Program::reboot() {

    return 0;
}

int Program::reset() {

    return 0;
}

int Program::ping(std::function<int(Packet)>) {

    return 0;
}

int Program::ping(std::function<int(Packet)>){

	return 0;
}

void Program::init() {
    if (options.interface.compare("") == 0)
        options.interface = host.getIface();
}
