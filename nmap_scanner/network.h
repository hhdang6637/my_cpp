#if !defined(_NETWORK_)
#define _NETWORK_

#include <ifaddrs.h>
#include <vector>
#include <string>

std::vector<std::string> GetAllNetworkInf(void);

std::pair<std::pair<struct sockaddr, struct sockaddr>, bool> GetV4SubnetAddrIntf(const std::string &);

std::string V4sockaddr2Str(struct sockaddr &);

#endif // _NETWORK_
