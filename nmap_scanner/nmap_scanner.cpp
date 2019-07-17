#include <array>
#include <sstream>

#include "nmap_scanner.h"

static std::pair<std::string, bool> internalNmapScan(const std::string &cmd)
{
    std::string xmlData;
    FILE *p = popen(cmd.c_str(), "re");
    if (p != nullptr)
    {
        std::array<char, 256> line;
        while (fgets(line.data(), line.size(), p) != nullptr)
        {
            xmlData.append(line.data());
        }
        pclose(p);
    }
    else
    {
        return std::make_pair("", false);
    }
    return std::make_pair(xmlData, true);
}

std::pair<std::string, bool> NmapScan(const std::string &target)
{
    std::array<char, 256> cmd;
    snprintf(cmd.data(), cmd.size(), "nmap -n -p T:22 -oX - %s", target.c_str());
    return internalNmapScan(std::string(cmd.data()));
}

std::vector<NmapScannerHost> XMLParser(const std::string &xml)
{
    std::vector<NmapScannerHost> hosts;
    return hosts;
}
