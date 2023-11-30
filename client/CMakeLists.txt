cmake_minimum_required(VERSION 3.16)
project(r-type_client)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_STANDARD 17)

add_executable(r-type_client
        main.cpp)

target_compile_features(r-type_client PRIVATE cxx_std_17)


if (UNIX OR APPLE)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(r-type_client PRIVATE sfml-graphics)

    install(TARGETS r-type_client DESTINATION bin)
endif (UNIX OR APPLE)
