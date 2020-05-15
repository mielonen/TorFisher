#include "report.h"
#include "data.h"

#define INFO std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [INFO] "
#define DEBUG std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [DEBUG] "

void report::printOnionDomainData(const data::onionDomain& onionDomain) {
    INFO <<"Domain: " << onionDomain.domain << std::endl;

    for (const std::string& title : onionDomain.title)
    {
        INFO <<"|- Title: " << title << std::endl;
    }

    INFO <<"|- Status: " << onionDomain.status << std::endl;

    std::multimap<std::string, std::string, httplib::detail::ci> ::const_iterator it;
    for (it = onionDomain.headers.begin(); it != onionDomain.headers.end(); ++it)
    {
        INFO <<"|- Header: ";
        std::cout << it->first <<" ";
        std::cout << it->second << std::endl;
    }

    INFO <<"|- DomainCount: " << onionDomain.toDomain.size() << std::endl;

    INFO <<"|- LinkCount: " << onionDomain.toLink.size() << std::endl;
}

void report::printTop100OnionDomainStatus(data datastore) {
    INFO << "TOP 10 DOMAIN" << std::endl;

    datastore.sortDomain();

    for(unsigned long i=0; (i < datastore.totalSize() && i < 100); i++) {
        INFO << "|-"<< datastore.domain(i) <<" Domain: "
             << datastore.toDomainSize(i) << " Link: "
             << datastore.toLinkSize(i) << std::endl;
        INFO << "|-- Title: " << datastore.domainTitle(i) << std::endl;
          }
    }

void report::printTorFisherStatus(data datastore) {
    unsigned long totalDomainScanned = datastore.totalSize();
    unsigned long totalDomain = 0;
    unsigned long totalLink = 0;
    unsigned long successfulDomain = 0;

    for(unsigned long i=0; i < datastore.totalSize(); i++) {
        totalDomain += datastore.toDomainSize(i);
        totalLink += datastore.toLinkSize(i);
        if (datastore.domainStatus(i) != 0){
               successfulDomain += datastore.toDomainSize(i);
        }
    }

    INFO << "TorFisher database status (sites/links): " << totalDomain << " / " <<  totalLink << " "
         << "Scanned successfully (online): "<< totalDomainScanned <<  std::endl;
}

