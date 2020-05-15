#ifndef TORFISHER_EXTRACT_H
#define TORFISHER_EXTRACT_H
#include <set>
#include "data.h"

class extract {
public:
    static std::set<std::string> extractOnionDomain(const std::string& text );
    static std::set<std::string> extractOnionLinks( const std::string& text );
    static std::set<std::string> extractRelativeOnionLinks( const std::string& text );
    static std::set<std::string> extractTitle( const std::string& text );
    static data::onionDomain extractALL (const std::string& url, const std::shared_ptr<httplib::Response>& Response);
};

#endif //TORFISHER_EXTRACT_H
