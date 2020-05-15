#include "include/httplib.h"
#include "util.cpp"
#include "extract.cpp"
#include "load.cpp"
#include "data.cpp"
#include "report.cpp"
#include "log.cpp"
#include "config.cpp"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <algorithm>


#define INFO std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [INFO] "
#define DEBUG std::cout << std::put_time(std::localtime(&time_now), "%d-%m-%y %OH:%OM:%OS") << " [DEBUG] "

static void help()
{
    std::cerr << "Usage: TorFisher -s seedFile.txt -l logFile.log -t torFile.log -p localhost:8118\n"
              << "Options:\n"
              << "\t-s,\tSeed, default file is SeedFile.txt. Seed file is mandatory\n"
              << "\t-l,\tLog, default file is TorFisher.log\n"
              << "\t-t,\tTor, default file is TorList.log\n"
              << "\t-p,\tProxy, default is localhost:8118\n"
              << "\t-h,\tHelp, this info\n"
              << std::endl;
}

int main( int argc, char* argv[] ) {

    int c ;
    while( ( c = getopt (argc, argv, "s:l:t:p:h") ) != -1 )
    {
        switch(c)
        {
            case 's':
                if(optarg && util::validateFileName(optarg)) {
                    config::seedFile = optarg;
                    }
                break;
            case 'l':
                if(optarg && util::validateFileName(optarg)) {
                    config::logFile = optarg;
                }
                break;
            case 't':
                if(optarg && util::validateFileName(optarg)) {
                    config::torFile = optarg;
                }
                break;
            case 'p':
                if(optarg && util::validateIP(optarg)) {
                    config::proxy = optarg;
                }
                break;
            case 'h':
                help();
                return 1;
            default:
                break;
        }
    }

    INFO << "TorFisher START " << std::endl;
    INFO << "|- Seed (-s): " << config::seedFile << std::endl;
    INFO << "|- Log (-l): " << config::logFile << std::endl;
    INFO << "|- Tor (-t): " << config::torFile << std::endl;
    INFO << "|- Proxy (-p): " << config::proxy << std::endl;

    data datastore;

    if(!util::readSeed(config::seedFile,datastore)){
        INFO <<"Initialization failed. Check the seed."<<std::endl;
        return 1;
    }

    if (datastore.totalSize() == 0){
        INFO <<"Initialization failed. Check the seed."<<std::endl;
        return  1;
    }

    //endless loop. scan never completed ...
    while(true){
        //Domains, scanned only if not previously successful
        for (unsigned long i = 0; i < datastore.totalSize(); i++) {
            if (datastore.toDomainSize(i) !=  0) {
                auto toDomain = datastore.toDomain(i);
                std::set<std::string>::iterator it = toDomain.begin();
                while (it != toDomain.end()) {
                    if (!datastore.isDomainScanned(*it)){
                        time_now = std::time(nullptr);
                        report::printTorFisherStatus(datastore);
                        DEBUG << "Working phase: Loading domain" << std::endl;
                        load::loadAndExtract(datastore, *it);
                    }
                    it++;
                }
            }
        }

        //Links, scans [linkLimit] random links per domain
        for (unsigned long i = 0; i < datastore.totalSize(); i++) {
            if (datastore.toLinkSize(i) !=  0){
                auto out = datastore.randomToLink(i);
                for (const auto j : out){
                    if (!datastore.isDomainScanned(j)) {
                        time_now = std::time(nullptr);
                        report::printTorFisherStatus(datastore);
                        DEBUG << "Working phase: Loading link" << std::endl;
                        load::loadAndExtract(datastore, j);
                    }
                }
            }
        }
    }
}

