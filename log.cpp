#include "log.h"
#include "data.h"
#include <iostream>

#define LOG file << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [LOG] "

void log::saveOnionDomainData(const std::string& filepath, const data::onionDomain& onionDomain) {
    time_now = std::time(nullptr);
    std::ofstream file;
    file.open(filepath, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(std::strerror(errno));

    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    LOG <<"Domain: " << onionDomain.domain << std::endl;

    for (const std::string& title : onionDomain.title)
    {
        LOG <<"|- Title: " << title << std::endl;
    }

    LOG <<"|- Status: " << onionDomain.status << std::endl;

    std::multimap<std::string, std::string, httplib::detail::ci> ::const_iterator it;
    for (it = onionDomain.headers.begin(); it != onionDomain.headers.end(); ++it)
    {
        LOG <<"|- Header: " << it->first <<" "<< it->second << std::endl;
    }

    LOG <<"|- DomainCount: " << onionDomain.toDomain.size() << std::endl;

    LOG <<"|- LinkCount: " << onionDomain.toLink.size() << std::endl;

    file.close();
}

void log::saveOnionDomain(const std::string& filepath, const data::onionDomain& onionDomain) {
    time_now = std::time(nullptr);
    std::ofstream file;
    file.open(filepath, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(std::strerror(errno));

    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    for (const std::string& title : onionDomain.title) {
        file << onionDomain.domain << ";" << title << std::endl;
    }

    file.close();
}