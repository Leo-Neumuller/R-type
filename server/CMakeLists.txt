cmake_minimum_required(VERSION 3.16)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(r-type_server
        main.cpp
        network/Network.cpp
        network/Network.hpp
        Server.cpp
        Server.hpp
        ../shared/network/NetworkHandler.hpp
        ../shared/network/utils/IdGenerator.cpp
        ../shared/network/utils/IdGenerator.hpp
        ../shared/network/NetworkClient.cpp
        ../shared/network/NetworkClient.hpp
        ../shared/network/PacketsRegistry.hpp
        ../shared/network/packet/EPacket.hpp
        ../shared/network/packet/IPacket.hpp
        ../shared/network/packet/GenericPacket.hpp
        ../shared/Entity.cpp
        ../shared/Registry.hpp
        ../shared/SparseArray.hpp
        network/PacketCallbacks.cpp
        network/PacketCallbacks.hpp
        ../shared/Components.hpp
        ../shared/Systems.cpp
        ../shared/Systems.hpp
        ../client/src/Loader.cpp
        TimedEvents.cpp
        TimedEvents.hpp
        ServerSystems.cpp
        ServerSystems.hpp
        ServerComponents.hpp)


include_directories(../shared/ network ../shared/network/utils ../shared/network/packet .)

target_compile_features(r-type_server PRIVATE cxx_std_17)

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

if (UNIX)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(r-type_server PRIVATE sfml-graphics)

    install(TARGETS r-type_server DESTINATION bin)
endif (UNIX)

if (APPLE)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(r-type_server PRIVATE sfml-graphics)

    install(TARGETS r-type_client DESTINATION bin)
endif (APPLE)
