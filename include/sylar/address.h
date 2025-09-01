#ifndef __SYLAR_ADDRESS_H__
#define __SYLAR_ADDRESS_H__

#include <memory>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <vector>
#include <map>

namespace sylar {

class Address {
public:
    typedef std::shared_ptr<Address> ptr;
    virtual ~Address() {}
    // Placeholders for Address class methods
};

class IPAddress : public Address {
public:
    typedef std::shared_ptr<IPAddress> ptr;
    // Placeholders for IPAddress class
};

class IPv4Address : public IPAddress {
public:
    typedef std::shared_ptr<IPv4Address> ptr;
    // Placeholders for IPv4Address class
};

class IPv6Address : public IPAddress {
public:
    typedef std::shared_ptr<IPv6Address> ptr;
    // Placeholders for IPv6Address class
};

class UnixAddress : public Address {
public:
    typedef std::shared_ptr<UnixAddress> ptr;
    // Placeholders for UnixAddress class
};

}

#endif
