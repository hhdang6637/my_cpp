#include <vector>
#include <string>
#include <iostream>

#include "network.h"
#include "nmap_scanner.h"

int main(int argc, char const *argv[])
{
    auto nmapResult = NmapScan("192.168.50.0/24");
    if (nmapResult.second == true)
    {
        std::cout << nmapResult.first;
    }

    return 0;
}
