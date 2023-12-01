cmake_minimum_required(VERSION 3.16)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(r-type_server
        main.cpp
        network/Network.cpp
        network/Network.hpp
        Server.cpp
        Server.hpp
        network/NetworkHandler.cpp
        network/NetworkHandler.hpp
        utils/IdGenerator.cpp
        utils/IdGenerator.hpp
        Client.cpp
        Client.hpp
        network/PacketsRegistry.cpp
        network/PacketsRegistry.hpp
        network/packet/EPacket.hpp
        network/packet/IPacket.hpp
        network/packet/GenericPacket.hpp
        ../shared/Entity.cpp
        ../shared/Registry.hpp
        ../shared/SparseArray.hpp)


include_directories(../shared/)

target_compile_features(r-type_server PRIVATE cxx_std_17)

include_directories(network utils network/packet .)

include(FetchContent)

FetchContent_Declare(asio-cmake
        GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
        GIT_TAG        origin/master
)

set(ASIO_CMAKE_ASIO_TAG asio-1-11-0)
FetchContent_MakeAvailable(asio-cmake)

target_link_libraries(r-type_server
        PRIVATE asio
)
