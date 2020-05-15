#include "extract.h"
#include "report.h"
#include "util.h"
#include "log.h"
#include "config.h"
#include <iostream>

#define INFO std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [INFO] "
#define DEBUG std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [DEBUG] "

std::set<std::string> extract::extractOnionDomain(const std::string& text) {
    static const std::regex hl_regex( "(?:http:\\/\\/)((([a-zA-Z2-7]{16})|([a-zA-Z2-7]{56}))\\.(onion|ONION))", std::regex_constants::icase  ) ;

    return { std::sregex_token_iterator( text.begin(), text.end(), hl_regex, 1 ),
             std::sregex_token_iterator{} } ;
}

std::set<std::string> extract::extractOnionLinks(const std::string& text) {
    static const std::regex hl_regex( "(?:\"http:\\/\\/)((([a-zA-Z2-7]{16})|([a-zA-Z2-7]{56}))\\.(onion|ONION)\\/[\\w\\/\\.]+)(?:\")", std::regex_constants::icase  ) ;

    return { std::sregex_token_iterator( text.begin(), text.end(), hl_regex, 1 ),
             std::sregex_token_iterator{} } ;
}

std::set<std::string> extract::extractRelativeOnionLinks(const std::string& text) {
    static const std::regex hl_regex( "(?:href=\"[\\/]?)(([\\w]+)([\\/\\w\\.]*))(?:\")", std::regex_constants::icase  ) ;

    return { std::sregex_token_iterator( text.begin(), text.end(), hl_regex, 1 ),
             std::sregex_token_iterator{} } ;
}

std::set<std::string> extract::extractTitle(const std::string& text) {
    static const std::regex hl_regex( "<title>(.*?)<\\/title>", std::regex_constants::icase  ) ;

    return { std::sregex_token_iterator( text.begin(), text.end(), hl_regex, 1 ),
             std::sregex_token_iterator{} } ;
}

data::onionDomain extract::extractALL(const std::string& url, const std::shared_ptr<httplib::Response>& Response) {
    data::onionDomain oDomain;
    auto time_now = std::time(nullptr);

    std::regex urlRe("((([a-zA-Z2-7]{16})|([a-zA-Z2-7]{56}))\\.(onion|ONION))(.*)");
    oDomain.domain = std::regex_replace(url, urlRe, "$1");
    oDomain.title = extractTitle(Response->body);
    oDomain.status = Response->status;
    oDomain.headers = Response->headers;

    for (const std::string& domain : extract::extractOnionDomain(Response->body)) {
        oDomain.toDomain.insert(domain);
        DEBUG <<"Domain found: "<< domain << std::endl;
    }

    for (const std::string& link : extract::extractOnionLinks(Response->body)) {
        oDomain.toLink.insert(link);
        DEBUG <<"Link found: "<< link << std::endl;
    }

    for (const std::string& link : extract::extractRelativeOnionLinks((Response->body))) {
        oDomain.toLink.insert(oDomain.domain + '/' + link);
        DEBUG <<"Relative link found: "<< link << std::endl;
    }

    report::printOnionDomainData(oDomain);
    log::saveOnionDomainData(config::logFile,oDomain);
    return oDomain;
}




