#ifndef TORFISHER_LOAD_H
#define TORFISHER_LOAD_H

class load {
public:
    static std::shared_ptr<httplib::Response> loadHtmlResponse(const std::string& url);
    static void loadAndExtract(data& datastore , const std::string& url);
};

#endif //TORFISHER_LOAD_H
