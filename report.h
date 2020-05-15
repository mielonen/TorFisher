#ifndef TORFISHER_REPORT_H
#define TORFISHER_REPORT_H
#include "data.h"

class report {
public:
    static void printTop100OnionDomainStatus(data datastore);
    static void printOnionDomainData(const data::onionDomain& onionDomain);
    static void printTorFisherStatus(data datastore);
};

#endif //TORFISHER_REPORT_H
