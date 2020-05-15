cmake_minimum_required(VERSION 3.15)
project(TorFisher)

set(CMAKE_CXX_STANDARD 17)

add_executable(TorFisher main.cpp include/httplib.h)
add_executable(TorFisherTests include/httplib.h tests/tests.cpp)

find_package(OpenSSL REQUIRED)
target_link_libraries(TorFisher OpenSSL::SSL)
target_link_libraries(TorFisherTests OpenSSL::SSL)
