#if !defined(_NMAP_SCANNER_)
#define _NMAP_SCANNER_

#include <string>
#include <vector>

struct NmapScannerHost
{
    bool Status;
    std::string IPv4Address[64];
    std::vector<std::pair<std::string, int>> OpenedPorts;
};

std::pair<std::string, bool> NmapScan(const std::string &subnet);
std::vector<NmapScannerHost> XMLParser(const std::string &xml);

#endif // _NMAP_SCANNER_
