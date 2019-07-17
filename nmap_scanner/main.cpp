#include <vector>
#include <string>
#include <iostream>

#include "network.h"

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
