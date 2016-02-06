/*
 * Program.cpp
 *
 *  Created on: 04.09.2015
 *      Author: jdi
 */
#include <iostream>
#include <algorithm>
#include <regex>
#include <string>
#include <cstring>

#include "Constant.h"
#include "Program.h"
#include "File.h"
#include "Host.h"
#include "Socket.h"
#include "Switch.h"
#include "Packet.h"
#include "Types.h"
#include "lookup.h"
#include "table.h"

using namespace smrtlink;
using namespace std;

int Program::run(vector<string> arg) {
    int optind = 0;
    std::vector<std::string> vect;
    std::map<std::string, std::string> ll;
    std::cmatch sm;
    std::string cmd = arg[optind++];
    switch (caseArg(cmd.c_str())) {
    case caseArg("reboot"):
        if (!reboot())
            return 0;
        fprintf(stderr, "Not yet implemented.\n");
        return 1;
        break;
    case caseArg("reset"):
        if (!reset())
            return 0;
        fprintf(stderr, "Not yet implemented.\n");
        return 1;
        break;
    case caseArg("save"):
        if (!save())
            return 0;
        fprintf(stderr, "Not yet implemented.\n");
        return 1;
        break;
    case caseArg("restore"):
        if (!restore())
            return 0;
        fprintf(stderr, "Not yet implemented.\n");
        return 1;
        break;
    case caseArg("flash"):
        if (!flash())
            return 0;
        fprintf(stderr, "Not yet implemented.\n");
        return 1;
        break;

    case caseArg("list"):
        if (!list())
            return 0;
        break;

    case caseArg("sniff"):
        if (!sniff())
            return 0;
        break;

    case caseArg("encode"):
        if (optind < arg.size()) {
            std::string s(arg[optind]);
            optind++;
            if (encode(s))
                return 0;
        } else {
            fprintf(stderr, "Argument expected after encode\n");
            return 1;
        }
        break;
    case caseArg("set"):
        while (optind < arg.size()) {
            if (regex_match(arg[optind].c_str(), sm,
                    std::regex("^([a-z]+)=(.*)$"))) {
                if (!snd_lookup.exists(sm[1]) && !rcv_lookup.exists(sm[1])) {
                    cerr << "Unknown argument " << arg[optind] << endl;
                    return 1;
                }
                ll.insert(std::pair<std::string, std::string>(sm[1], sm[2]));
            } else {
                cerr << "Invalid Syntax " << arg[optind] << endl;
                return 1;
            }
            optind++;
        }
        if (!setProperty(ll))
            return 0;
        fprintf(stderr, "Not yet implemented.\n");
        return 1;
        break;
    case caseArg("get"):
        while (optind < arg.size()) {
            if (regex_match(arg[optind].c_str(), sm,
                    std::regex("^([a-z]+)$"))) {
                if (!snd_lookup.exists(sm[1]) && !rcv_lookup.exists(sm[1])) {
                    cerr << "Unknown argument " << arg[optind] << endl;
                    return 1;
                }
                vect.push_back(sm[1]);
            } else {
                cerr << "Invalid argument " << arg[optind] << endl;
                return 1;
            }
            optind++;
        }
        if (!getProperty(vect))
            return 0;
        break;
    default:
        printf("Unknown command: %s\n", cmd.c_str());
        return 1;
    }

}

int printHeader(Packet p) {
    if (options.flags.HEADER) {
        if (options.flags.HEX) {
            cout << "Received Header:\n\t" << p.getHead() << "\n";
        } else {
            p.printHeader();
            printf("\n");
        }
    }
    return 0;
}

int printPacket(Packet p) {
    if (options.flags.HEX) {
        cout << "Received Payload:\n\t" << p.getBody() << "\n";
    } else {
        for (dataset d : p.getPayload()) {
            auto lookup = (options.flags.REVERSE) ? snd_lookup : rcv_lookup;
            if (lookup.exists(d.type)) {
                table::set s = lookup[d.type];
                if (d.len > 0) {
                    switch (s.format) {
                    case table::STRING:
                        cout << "+\t" << s.name << " = " << &d.value[0] << "\n";
                        break;
                    case table::BOOL:
                        cout << "+\t" << s.name << " = "
                                << (d.value[0] ? "YES" : "NO") << "\n";
                        break;
                    case table::HEX:
                        cout << "+\t" << s.name << " = " << d.value << "\n";
                        break;
                    case table::DEC:
                        cout << "+\t" << s.name << " = ";
                        if (d.value.size() > 0)
                            cout << dec << (unsigned) d.value[0];
                        for (unsigned i = 1; i < d.value.size(); i++)
                            cout << dec << "." << (unsigned) d.value[i];
                        cout << "\n";
                        break;
                    case table::ACTION:
                        cout << "Error:" << s.name
                                << " is marked as 'action' but carries payload."
                                << d.value << "\n";
                        break;
                    default:
                        cout << "+\t" << s.name << " = " << d.value << "\n";
                        break;
                    }
                } else { //empty
                    cout << dec << ">\t" << s.name << "\n";
                }
            } else { //unknown id
                if (d.len > 0) {
                    cout << "##\t" << d.type << ":\n\t";
                    cout << hex << d.value << dec << "\n";
                } else { //empty
                    cout << "#>\t" << d.type << "\n";
                }
            }
        }
    }
    return 0;
}

int Program::list() {
    try {
        cout << "List:\n";
        discover([this](Packet a) {
            printHeader(a);
            if (options.flags.HEX) {
                cout <<"Received Payload:\n"<<a.getBody()<<"\n";
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
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
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
            cout << p.opCodeToString() << "\n";
            printHeader(p);
            printPacket(p);
            return 0;
        };
        s.listen();
        io_service.run();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

int Program::encode(string s) {
    bytes d;
    d = d.readHex(s);
    Packet p = Packet(Packet::NONE);
    p.encode(d);
    cout << d << endl;
    return 0;
}

int Program::setProperty(map<string, string> prop) {
    try {
        datasets data = { };
        for (auto p : prop) {
            string s = p.second;
            dataset d;
            if (rcv_lookup.exists(p.first)) {
                d.type = rcv_lookup.type(p.first);
                if (rcv_lookup[p.first].format == table::STRING) {
                    d.len = s.size() + 1;
                    d.value = s;
                    data.push_back(d);
                }
            }
        }

        cout << "List:\n";
        discover([this,data](Packet a) {
            datasets d =a.getPayload();
            Switch sw = Switch();
            sw.parse(d);
            sw.print();

            datasets t = { {SND_PING, 0, {}}};
            get(a, t, [this,data](Packet a) {
                        datasets d =a.getPayload();
                        Switch sw = Switch();
                        sw.parse(d);
                        set(a,data,

                                [this](Packet a) {
                                    cout << a.opCodeToString() << "\n";
                                    printHeader(a);
                                    printPacket(a);
                                    return 0;
                                });
                        return 0;
                    });
            return 0;
        });

        io_service->run();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int Program::getProperty(vector<string> prop) {
    try {
        datasets data = { };
        for (string s : prop) {
            dataset d;
            d.type = snd_lookup.type(s);
            data.push_back(d);
        }
        cout << "List:\n";
        discover([this,data](Packet a) {
            datasets d =a.getPayload();
            Switch sw = Switch();
            sw.parse(d);
            sw.print();
            get(a, data, [this](Packet a) {
                        cout << a.opCodeToString() << "\n";
                        printHeader(a);
                        printPacket(a);
                        return 0;
                    });
            return 0;
        });

        io_service->run();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
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
        discover(
                [this](Packet a) {
                    datasets d =a.getPayload();
                    Switch sw = Switch();
                    sw.parse(d);
                    cout <<sw.settings.hostname<<"\t";
                    datasets t = { {SND_PING, 0, {}}};
                    get(a, t, [this](Packet a) {
                                datasets d =a.getPayload();
                                Switch sw = Switch();
                                sw.parse(d);
                                datasets t = { {REBOOT, 1, {options.flags.PERMANENT?(byte)1:(byte)0}}};
                                set(a,t,[this](Packet a) {
                                            if( a.getOpCode()==Packet::CONFIRM)
                                            cout<< "rebooting now.\n";
                                            return 0;
                                        });
                                return 0;
                            });
                    return 0;
                });
        io_service->run();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int Program::reset() {
    try {
        discover([this](Packet a) {
            datasets d =a.getPayload();
            Switch sw = Switch();
            sw.parse(d);
            cout <<sw.settings.hostname<<"\t";
            datasets t = { {SND_PING, 0, {}}};
            get(a, t, [this](Packet a) {
                        datasets d =a.getPayload();
                        Switch sw = Switch();
                        sw.parse(d);
                        datasets t = { {RESET, 0, {}}};
                        set(a,t,[this](Packet a) {
                                    if( a.getOpCode()==Packet::CONFIRM)
                                    cout<< "reseting config.\n";
                                    return 0;
                                });
                        return 0;
                    });
            return 0;
        });
        io_service->run();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

int Program::discover(function<int(Packet)> c) {
    Packet p = Packet(Packet::DISCOVERY);
    p.setHostMac(host.getMac());
    p.setPayload( { });
    sock->callback = c;
    sock->send(p);
    return 0;
}

int Program::get(Packet l, datasets t, function<int(Packet)> c) {
    Packet p = Packet(Packet::GET);
    p.setSwitchMac(l.getSwitchMac());
    p.setHostMac(host.getMac());
    p.setPayload(t);
    sock->callback = c;
    sock->send(p);
    return 0;
}

int Program::set(Packet l, datasets t, function<int(Packet)> c) {
    Packet p = Packet(Packet::SET);
    p.setSwitchMac(l.getSwitchMac());
    p.setTokenId(l.getTokenId());
    p.setHostMac(host.getMac());
    bytes n = options.user;
    bytes w = options.password;
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
