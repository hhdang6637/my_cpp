
#include <sys/types.h>
#include <arpa/inet.h>

#include <string>
#include <array>
#include <fstream>

#include "network.h"

std::vector<std::string> GetAllNetworkInf()
{
    auto removeHyphenChar = [](std::array<char, 64> &infName) {
        for (auto &c : infName)
        {
            if (c == ':')
            {
                c = '\0';
                break;
            }
        }
    };

    std::vector<std::string> intfs;
    std::ifstream netDevFile("/proc/net/dev");
    if (netDevFile.is_open())
    {
        std::array<char, 256> line;
        std::array<char, 64> intfName;
        int lineCount = 0;
        while (netDevFile.getline(line.data(), line.size()))
        {
            if (++lineCount <= 2)
            {
                continue;
            }
            // printf("->%s\n", line.data());
            if (sscanf(line.data(), "%64s\t", intfName.data()) == 1)
            {
                removeHyphenChar(intfName);
                intfs.emplace_back(intfName.data());
            }
        }
        netDevFile.close();
    }

    return intfs;
}

std::pair<std::pair<struct sockaddr, struct sockaddr>, bool> GetV4SubnetAddrIntf(const std::string &intf)
{
    struct sockaddr ifa_addr
    {
    };
    struct sockaddr ifa_netmask
    {
    };

    bool found = false;

    struct ifaddrs *ifAddrsPtr = nullptr;
    getifaddrs(&ifAddrsPtr);

    for (struct ifaddrs *ifAddrPtr = ifAddrsPtr; ifAddrPtr != nullptr; ifAddrPtr = ifAddrPtr->ifa_next)
    {
        if (ifAddrPtr->ifa_addr == nullptr)
        {
            continue;
        }

        if (ifAddrPtr->ifa_addr->sa_family == AF_INET && intf.compare(ifAddrPtr->ifa_name) == 0)
        {
            ifa_addr = *ifAddrPtr->ifa_addr;
            ifa_netmask = *ifAddrPtr->ifa_netmask;
            found = true;
#if 0
            printf("%s : %s/%s\n", intf.c_str(), V4sockaddr2Str(ifa_addr).c_str(), V4sockaddr2Str(ifa_netmask).c_str());
#endif
        }
    }
    if (ifAddrsPtr != nullptr)
    {
        freeifaddrs(ifAddrsPtr);
    }

    return std::make_pair(std::make_pair(ifa_addr, ifa_netmask), found);
}

std::string V4sockaddr2Str(struct sockaddr &ifa_addr)
{
    std::array<char, 64> str;
    inet_ntop(AF_INET, &((struct sockaddr_in *)&ifa_addr)->sin_addr, str.data(), str.size());
    return std::string(str.data());
}

int V4SubnetMaskToCIDR(struct sockaddr &ifa_netmask)
{
    if (ifa_netmask.sa_family != AF_INET)
    {
        return 0;
    }

    uint32_t mask = (uint32_t)(((struct sockaddr_in *)&ifa_netmask)->sin_addr.s_addr);

    int cidr = 0;
    while (mask > 0)
    {
        if (mask % 2 == 1)
        {
            cidr++;
        }
        else
        {
            break;
        }

        mask = mask / 2;
    }

    return cidr;
}

#if 0

#include <iostream>

int main(int argc, char const *argv[])
{
    std::vector<std::string> intfs = GetAllNetworkInf();

    for (const auto &intf : intfs)
    {
        // std::cout << intf << std::endl;
        auto subnetInfo = GetV4SubnetAddrIntf(intf);
        if (subnetInfo.second == true)
        {
            std::cout << intf << std::endl;
            std::cout << V4sockaddr2Str(subnetInfo.first.first) << "/" << V4sockaddr2Str(subnetInfo.first.second) << std::endl;
        }
    }

    return 0;
}
#endif