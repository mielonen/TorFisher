#ifndef TORFISHER_UTIL_H
#define TORFISHER_UTIL_H
#include "data.h"

class util {
public:
    static std::vector<std::string> split(const std::string& strToSplit, char delimiter);
    static bool readSeed(const std::string& fileName, data &datastore );
    static bool validateFileName(const std::string& s);
    static bool validateIP(const std::string& s);
};

#endif //TORFISHER_UTIL_H
