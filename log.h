#ifndef TORFISHER_LOG_H
#define TORFISHER_LOG_H
#include "data.h"

class log {
public:
    static void saveOnionDomainData(const std::string& filepath, const data::onionDomain& onionDomain);
    static void saveOnionDomain(const std::string& filepath, const data::onionDomain& onionDomain);
};

#endif //TORFISHER_LOG_H
