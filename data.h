#ifndef TORFISHER_DATA_H
#define TORFISHER_DATA_H
#include <set>
#include "include/httplib.h"

class data {
public:
    struct onionDomain
    {
        std::string domain;
        std::set<std::string> title;
        int status;
        httplib::Headers headers;
        std::set <std::string> toDomain;
        std::set <std::string> toLink;
    };

    bool isDomainScanned(const std::string &onionDomain);
    void addOnionDomain(const onionDomain& onionDomain);

    unsigned long totalSize();
    unsigned long toDomainSize(unsigned long i);
    unsigned long toLinkSize(unsigned long i);

    std::set<std::string> toDomain(unsigned long i);
    std::set<std::string> toLink(unsigned long i);
    std::vector<std::string> randomToLink(unsigned long i);

    std::string domain (unsigned long i);
    std::string domainTitle (unsigned long i);
    int domainStatus (unsigned long i);
    
    void sortDomain();
    bool validateIndex(unsigned long i);

private:
    std::vector<struct onionDomain> onionDomainVector;
};

#endif //TORFISHER_DATA_H
