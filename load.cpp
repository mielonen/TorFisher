#include "load.h"
#include "config.h"

#define INFO std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [INFO] "
#define DEBUG std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [DEBUG] "
static std::time_t time_now = std::time(nullptr);

std::shared_ptr<httplib::Response> load::loadHtmlResponse(const std::string &url) {
    try {
        DEBUG << "Loading: " << url;
        std::shared_ptr<httplib::Response> res;
        std::string domain = url.substr(0, url.find('/'));
        std::string path;
        if (url.find('/') != std::string::npos){
            path = url.substr(url.find('/'));
        }
        else {
            path = "/";
        }

        httplib::Client cli(domain);

        std::string proxy = std::string(config::proxy).substr(0, std::string(config::proxy).find(':'));
        std::string port = std::string(config::proxy).substr(std::string(config::proxy).find(':')+1);
        cli.set_proxy(proxy.c_str(), std::stoi(port));

        cli.set_timeout_sec(config::timeout);

        res = cli.Get(path.c_str());

        if (res && res->status == 200){
            std::cout << " ...status: "<< res->status << std::endl;
            return res;
        } else if (res && res->status == 301){
            cli.set_follow_location(true);
            res = cli.Get(path.c_str());
            if (res != nullptr){
                std::cout << " ...status: "<< res->status << std::endl;
                return res;
            } else{
                std::cout << " ...status: failed" << std::endl;
                return nullptr;
            }
        }
        else{
            std::cout << " ...status: failed" << std::endl;
            return nullptr;
        }
        }catch (...){
            INFO << "...crawler crashed" << std::endl;
            return nullptr;
    }
}

void load::loadAndExtract(data& datastore , const std::string& url){
    std::shared_ptr<httplib::Response> res;

    try {
        res = load::loadHtmlResponse(url);
    }catch (...){
        INFO << "Link read failed" << std::endl;
    }

    if (res){
        datastore.addOnionDomain(extract::extractALL(url, res));
    }
}