#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../util.cpp"
#include "../extract.cpp"
#include "../load.cpp"
#include "../data.cpp"
#include "../report.cpp"
#include "../log.cpp"
#include "../config.cpp"
#include <ctime>
#include <iomanip>
#include <iterator>

TEST_CASE( "extractOnionDomain / length 16 characters", "[extract::extractOnionDomain]" ) {
    std::string link = "http://abcdefghijklmnop.onion";
    std::string shortLink = "http://abcdefghijklmno.onion";
    std::string longLink = "http://abcdefghijklmnopq.onion";

    std::string extractedDomain = "abcdefghijklmnop.onion";

    REQUIRE(extract::extractOnionDomain(link).begin()->c_str() != link);
    REQUIRE(extract::extractOnionDomain(link).begin()->c_str() == extractedDomain);
    REQUIRE(extract::extractOnionDomain(link).begin()->length() ==  22);
    REQUIRE(extract::extractOnionDomain(shortLink).empty());
    REQUIRE(extract::extractOnionDomain(longLink).empty());
}

TEST_CASE( "extractOnionDomain / length 56 characters", "[extract::extractOnionDomain]" ) {
    std::string link = "http://abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWYZ234567.onion";
    std::string shortLink = "http://abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWYZ23456.onion";
    std::string longLink = "http://abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWYZ2345678.onion";
    std::string base32_check_1 = "http://abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWYZ234567.onion";
    std::string base32_check_2 = "http://abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWYZ234589.onion";
    std::string base32_check_3 = "http://abcdefghijklmnopqrstuvwyzABCDEFGH1JKLMN0PQRSTUVWYZ234567.onion";

    std::string extractedDomain = "abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWYZ234567.onion";

    REQUIRE(extract::extractOnionDomain(link).begin()->c_str() != link);
    REQUIRE(extract::extractOnionDomain(link).begin()->c_str() == extractedDomain);
    REQUIRE(extract::extractOnionDomain(link).begin()->length() ==  62);
    REQUIRE(extract::extractOnionDomain(shortLink).empty());
    REQUIRE(extract::extractOnionDomain(longLink).empty());
    REQUIRE(extract::extractOnionDomain(base32_check_1).begin()->c_str() == extractedDomain);
    REQUIRE(extract::extractOnionDomain(base32_check_2).empty());
    REQUIRE(extract::extractOnionDomain(base32_check_3).empty());
}

TEST_CASE( "extractOnionDomain / extracting", "[extract::extractOnionDomain]" ) {
    std::string link16_1 = "http://abcdefghijklmnop.onion/";
    std::string link16_2 = "http://abcdefghijklmnop.onion/index.html";
    std::string link16_3 = "abcdefghijklmnop.onion.onion";
    std::string link16_4 = "http:/abcdefghijklmnop.onion.onion/";
    std::string link16_5 = "http://../abcdefghijklmnop.onion.onion/";
    std::string link16_6 = "http://abc%efghijklmnop.onion.onion/";
    std::string link16_7 = "http://abcdefghijk1mnop.onion.onion/";
    std::string link16_8 = "http://abcdefghijklmnop.com/";
    std::string extractedDomain16 = "abcdefghijklmnop.onion";

    REQUIRE(extract::extractOnionDomain(link16_1).begin()->c_str() != link16_1);
    REQUIRE(extract::extractOnionDomain(link16_1).begin()->c_str() == extractedDomain16);
    REQUIRE(extract::extractOnionDomain(link16_2).begin()->c_str() == extractedDomain16);
    REQUIRE(extract::extractOnionDomain(link16_3).empty());
    REQUIRE(extract::extractOnionDomain(link16_4).empty());
    REQUIRE(extract::extractOnionDomain(link16_5).empty());
    REQUIRE(extract::extractOnionDomain(link16_6).empty());
    REQUIRE(extract::extractOnionDomain(link16_7).empty());
    REQUIRE(extract::extractOnionDomain(link16_8).empty());
}

TEST_CASE( "extractOnionLinks / extracting", "[extract::extractOnionLinks]" ) {
    std::string link16_1 = "\"http://abcdefghijklmnop.onion/index.html\"";
    std::string link16_2 = "\"http://abcdefghijklmnop.onion/index.htm\"";
    std::string link16_3 = "\"http://abcdefghijklmnop.onion/path/\"";
    std::string link16_4 = "\"http://abcdefghijklmnop.onion/path/path/\"";

    std::string extractedDomain16_1 = "abcdefghijklmnop.onion/index.html";
    std::string extractedDomain16_2 = "abcdefghijklmnop.onion/index.htm";
    std::string extractedDomain16_3 = "abcdefghijklmnop.onion/path/";
    std::string extractedDomain16_4 = "abcdefghijklmnop.onion/path/path/";


    REQUIRE(extract::extractOnionLinks(link16_1).begin()->c_str() != link16_1);
    REQUIRE(extract::extractOnionLinks(link16_2).begin()->c_str() == extractedDomain16_2);
    REQUIRE(extract::extractOnionLinks(link16_3).begin()->c_str() == extractedDomain16_3);
    REQUIRE(extract::extractOnionLinks(link16_4).begin()->c_str() == extractedDomain16_4);
}

TEST_CASE( "extractRelativeOnionLinks / extracting", "[extract::extractRelativeOnionLinks]" ) {
    std::string link16_1 = "href://abcdefghijklmnop.onion/index.html\"";
    std::string link16_2 = "href=\"/index.html\"";
    std::string link16_3 = "href=\"/path/\"";
    std::string link16_4 = "href=\"/path/path/\"";

    std::string extractedDomain16_2 = "index.html";
    std::string extractedDomain16_3 = "path/";
    std::string extractedDomain16_4 = "path/path/";


    REQUIRE(extract::extractRelativeOnionLinks(link16_1).begin()->c_str() != link16_1);
    REQUIRE(extract::extractRelativeOnionLinks(link16_2).begin()->c_str() == extractedDomain16_2);
    REQUIRE(extract::extractRelativeOnionLinks(link16_3).begin()->c_str() == extractedDomain16_3);
    REQUIRE(extract::extractRelativeOnionLinks(link16_4).begin()->c_str() == extractedDomain16_4);
}

TEST_CASE( "validateFileName", "[util::validateFileName]" ) {
    REQUIRE(util::validateFileName("SeedFile.txt") == true);
    REQUIRE(util::validateFileName("TorFisher.log") == true);
    REQUIRE(util::validateFileName("TorList.log") == true);
    REQUIRE(util::validateFileName("/SeedFile.txt") == true);
    REQUIRE(util::validateFileName("/SeedFile.txt.csv") == false);
    REQUIRE(util::validateFileName("/temp/SeedFile.txt") == true);
    REQUIRE(util::validateFileName("/../SeedFile.txt") == false);
    REQUIRE(util::validateFileName("../SeedFile.txt") == false);
    REQUIRE(util::validateFileName("../SeedFile%3.txt") == false);
}

TEST_CASE( "validateIP", "[util::validateIP]" ) {
    REQUIRE(util::validateIP("192.168.1.1:8118") == true);
    REQUIRE(util::validateIP("localhost:8118") == true);
    REQUIRE(util::validateIP("0.0.0.0:8118") == true);
    REQUIRE(util::validateIP("1.1.1.1:8118") == true);
    REQUIRE(util::validateIP("255.255.255.255:8118") == true);
    REQUIRE(util::validateIP("256.256.256.256:8118") == false);
    REQUIRE(util::validateIP("something:8118") == false);
}

TEST_CASE( "readSeed", "[util::readSeed]" ) {
    std::ofstream seed;
    seed.open ("seed.txt");
    seed << "3g2upl4pq6kufc4m.onion\n";
    seed << "3g2upl4pq6kufc4.onion\n";
    seed << "3g2upl4pq6kufc4mm.onion\n";
    seed << "facebook.com\n";
    seed << "%3%4\n";
    seed.close();

    data datastore;

    REQUIRE(util::readSeed("seed.txt",datastore));
    REQUIRE(datastore.totalSize() == 1);
}
