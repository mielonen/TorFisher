#include "data.h"
#include <boost/algorithm/string.hpp>

void data::addOnionDomain(const struct onionDomain& onionDomain) {
    bool exists = false;
    for(unsigned long i=0; i < onionDomainVector.size(); i++) {
        if (onionDomainVector.at(i).domain == onionDomain.domain) {
            onionDomainVector.at(i).status = onionDomain.status;
            onionDomainVector.at(i).headers = onionDomain.headers;
            for (const std::string& domain : onionDomain.toDomain) {
                onionDomainVector.at(i).toDomain.insert(domain);
            }
            for (const std::string& link : onionDomain.toLink) {
                onionDomainVector.at(i).toLink.insert(link);
            }
            exists = true;
            break;
        }
    }

    if (!exists){
        onionDomainVector.push_back(onionDomain);
        log::saveOnionDomain(config::torFile, onionDomain);
    }
}

unsigned long data::totalSize() {
    return onionDomainVector.size();
}

unsigned long data::toDomainSize(unsigned long i) {
    if (validateIndex(i)){
        return onionDomainVector.at(i).toDomain.size();
    } else{
        return 0;
    }
}

unsigned long data::toLinkSize(unsigned long i) {
    if (validateIndex(i)){
        return onionDomainVector.at(i).toLink.size();
    } else{
        return 0;
    }
}

std::set<std::string> data::toLink(unsigned long i) {
    if (validateIndex(i)){
        return onionDomainVector.at(i).toLink;
    } else{
        return std::set<std::string> ();
    }
}

std::set<std::string> data::toDomain(unsigned long i) {
    if (validateIndex(i)){
        return onionDomainVector.at(i).toLink;
    } else{
        return std::set<std::string> ();
    }
}

std::string data::domain(unsigned long i) {
    if (validateIndex(i)){
        return onionDomainVector.at(i).domain;
    } else{
        return std::string();
    }
}

int data::domainStatus (unsigned long i){
    if (validateIndex(i)){
        return onionDomainVector.at(i).status;
    } else{
        return 0;
    }

}

bool my_cmp(const data::onionDomain & a, const data::onionDomain & b){
    return a.toDomain.size() > b.toDomain.size();
}

void data::sortDomain() {
    std::sort(onionDomainVector.begin(), onionDomainVector.end(), my_cmp);
}

std::string data::domainTitle(unsigned long i) {
    for (auto it = onionDomainVector.at(i).title.begin();
         it != onionDomainVector.at(i).title.end();) {
            return *it;
    }
    return "";
}

bool data::isDomainScanned(const std::string &onionDomain) {
    for (unsigned long i = 0; i < onionDomainVector.size(); i++) {
        if (boost::iequals(onionDomainVector.at(i).domain, onionDomain)) {
            if (onionDomainVector.at(i).status == 200) {
                return true;
            }
        }
    }
    return false;
}

bool data::validateIndex(unsigned long i) {
    return (i >= 0) && (i < onionDomainVector.size());
}

std::vector<std::string> data::randomToLink(unsigned long i) {
    if (validateIndex(i)){
        std::set<std::string> in = onionDomainVector.at(i).toLink;
        std::vector<std::string> out;
        std::sample(in.begin(), in.end(), std::back_inserter(out),
                    config::linkLimit, std::mt19937{std::random_device{}()});
        return out;
    } else{
        return std::vector<std::string>();
    }
}
