cmake_minimum_required(VERSION 3.16)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(r-type_server
        main.cpp)

target_compile_features(r-type_server PRIVATE cxx_std_17)
