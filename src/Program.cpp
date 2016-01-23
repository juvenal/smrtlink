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
    if (options.flags.HEADER) {
        if (options.flags.HEX) {
            std::cout << "Received Header:\n\t" << p.getHead() << "\n";
        } else {
            p.printHeader();
            printf("\n");
        }
    }
    return 0;
}

int printPacket(Packet p) {
    if (options.flags.HEX) {
        std::cout << "Received Payload:\n\t" << p.getBody() << "\n";
    } else {
        for (dataset d : p.getPayload()) {
            auto lookup =
                    (options.flags.REVERSE) ? snd_lookup : rcv_lookup;
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
}

int Program::list() {
    try {
        std::cout << "List:\n";
        discover([this](Packet a) {
            printHeader(a);
            if (options.flags.HEX) {
                std::cout <<"Received Payload:\n"<<a.getBody()<<"\n";
            } else {
                datasets d =a.getPayload();
                Switch sw = Switch();
                sw.parse(d);
                File f;
                f.write(sw.toString());
                sw.print();
            }
            return 0;
        });
        io_service->run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
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

    return 0;
}

int Program::encode(std::string s) {
    bytes d(s);
    Packet p = Packet(Packet::NONE);
    p.encode(d);
    std::cout << d << std::endl;
    return 0;
}

int Program::setProperty(std::map<std::string,std::string> prop) {
    try {

        std::cout << "List:\n";
        discover(
                [this](Packet a) {
                    datasets d =a.getPayload();
                    Switch sw = Switch();
                    sw.parse(d);
                    sw.print();

                    datasets t = { {SND_PING, 0, {}}};
                    get(a, t, [this](Packet a) {
                                datasets d =a.getPayload();
                                Switch sw = Switch();
                                sw.parse(d);

                                datasets t = { {LOOP_PREVENTION, 1, {0}}};
                                set(a,t,

                                        [this](Packet a) {
                                            std::cout << a.opCodeToString() << "\n";
                                            printHeader(a);
                                            printPacket(a);
                                            return 0;
                                        });
                                return 0;
                            });
                    return 0;
                });

        io_service->run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int Program::getProperty(std::vector<std::string> prop) {
    try {
        std::cout << "List:\n";
        discover([this](Packet a) {

            datasets d =a.getPayload();
            Switch sw = Switch();
            sw.parse(d);
            sw.print();

            datasets t = { {SYSTEM_INFO, 0, {}}};
            get(a, t, [this](Packet a) {
                        std::cout << a.opCodeToString() << "\n";
                        printHeader(a);
                        printPacket(a);
                        return 0;
                    });
            return 0;
        });

        io_service->run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int Program::save() {
    Switch sw = Switch();
    sw.settings.hostname = "testname.lan";
    File f;
    f.write(sw.toString());
    return 0;
}

int Program::restore() {
    File f;
    Switch sw;
    sw.parse(f.read());
    sw.print();
    return 0;
}

int Program::flash() {

    return 1;
}

int Program::reboot() {
    try {
        discover([this](Packet a) {
            datasets d =a.getPayload();
            Switch sw = Switch();
            sw.parse(d);
            std::cout <<sw.settings.hostname<<"\t";
            datasets t = { {SND_PING, 0, {}}};
            get(a, t, [this](Packet a) {
                        datasets d =a.getPayload();
                        Switch sw = Switch();
                        sw.parse(d);
                        datasets t = { {REBOOT, 1, {0}}};
                        set(a,t,[this](Packet a) {
                                    if( a.getOpCode()==Packet::CONFIRM)
                                    std::cout<< "rebooting now.\n";
                                    return 0;
                                });
                        return 0;
                    });
            return 0;
        });
        io_service->run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int Program::reset() {

    return 1;
}

int Program::discover(std::function<int(Packet)> c) {
    Packet p = Packet(Packet::DISCOVERY);
    p.setHostMac(host.getMac());
    p.setPayload( { });
    sock->callback = c;
    sock->send(p);
    return 0;
}

int Program::get(Packet l, datasets t, std::function<int(Packet)> c) {
    Packet p = Packet(Packet::GET);
    p.setSwitchMac(l.getSwitchMac());
    p.setHostMac(host.getMac());
    p.setPayload(t);
    sock->callback = c;
    sock->send(p);
    return 0;
}

int Program::set(Packet l, datasets t, std::function<int(Packet)> c) {
    Packet p = Packet(Packet::SET);
    p.setSwitchMac(l.getSwitchMac());
    p.setTokenId(l.getTokenId());
    p.setHostMac(host.getMac());
    bytes n = options.user;
    bytes w = options.password;
    n.push_back('\0');
    w.push_back('\0');
    datasets ld = { { LOGIN_USER, (short) (n.size()), n }, { LOGIN_PASSWORD,
            (short) (w.size()), w } };
    p.setPayload(ld + t);
    sock->callback = c;
    sock->send(p);
    return 0;
}

void Program::init() {
    if (options.interface.compare("") == 0)
        options.interface = host.getIface();

    sock->setHostIp(host.getIp());
    sock->init(DST_PORT, SRC_PORT);
}
