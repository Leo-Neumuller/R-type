cmake_minimum_required(VERSION 3.16)
project(r-type_client)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_STANDARD 17)

add_executable(r-type_client
        main.cpp
        ../shared/Entity.cpp
        ../shared/Registry.hpp
        ../shared/SparseArray.hpp
        ../shared/network/PacketsRegistry.hpp
        ../shared/network/packet/EPacket.hpp
        ../shared/network/packet/IPacket.hpp
        ../shared/network/packet/GenericPacket.hpp
        ../shared/network/NetworkHandler.hpp
        ../shared/network/NetworkClient.cpp
        ../shared/network/NetworkClient.hpp
        ../shared/network/utils/IdGenerator.cpp
        ../shared/network/utils/IdGenerator.hpp
        network/Network.cpp
        network/Network.hpp
        Client.cpp
        Client.hpp
        network/PacketCallbacks.cpp
        network/PacketCallbacks.hpp)

target_compile_features(r-type_client PRIVATE cxx_std_17)

include_directories(../shared/ network ../shared/network/utils ../shared/network/packet .)

include(FetchContent)

FetchContent_Declare(asio-cmake
        GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
        GIT_TAG        origin/master
)

set(ASIO_CMAKE_ASIO_TAG asio-1-11-0)
FetchContent_MakeAvailable(asio-cmake)

target_link_libraries(r-type_client
        PRIVATE asio
)

if (UNIX OR APPLE)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(r-type_client PRIVATE sfml-graphics)

    install(TARGETS r-type_client DESTINATION bin)
endif (UNIX OR APPLE)
