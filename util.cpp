#include "util.h"
#include "load.h"
#include "report.h"
#include <iostream>

#define INFO std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [INFO] "
#define DEBUG std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [DEBUG] "

std::vector<std::string> util::split(const std::string& strToSplit, char delimiter) {
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimiter))
    {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}

bool util::readSeed(const std::string &fileName, data &datastore) {
    auto time_now = std::time(nullptr);
    INFO << "Reading "<< fileName << " START" << std::endl;
    std::ifstream in(fileName.c_str());
    if(!in)
    {
        INFO << "Reading : "<<fileName<< " failed" << std::endl;
        return false;
    }

    std::string str;
    std::regex urlRe("(([a-zA-Z2-7]{16})|([a-zA-Z2-7]{56}))\\.(onion|ONION)");
    while (std::getline(in, str))
    {
        if(!str.empty()){
            DEBUG << "Working phase: Reading seed" << std::endl;
            if (std::regex_match(str, urlRe)){
                load::loadAndExtract(datastore, str);
                report::printTorFisherStatus(datastore);
            } else{
                DEBUG << "Error in seed" << std::endl;
            }
        }
    }
    in.close();
    INFO << "Reading "<< fileName << " OK" << std::endl;
    return true;
}

bool util::validateIP(const std::string &s) {
    std::regex e ("^(((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\."
                  "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9]))|localhost):[0-9]+$");
    return std::regex_match (s,e);
}

bool util::validateFileName(const std::string &s) {
    std::regex e (R"((^[\/]?([A-z0-9-_+]+\/)*([A-z0-9]+\.(log|csv|txt))))");
    return std::regex_match (s,e);
}
