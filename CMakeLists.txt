cmake_minimum_required(VERSION 3.16)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(rtype)

set(link_src "${CMAKE_CURRENT_SOURCE_DIR}/client/assets")
if(UNIX AND NOT APPLE)
    set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/assets")
else()
    set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets")
endif()
ADD_CUSTOM_TARGET(link_target ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink ${link_src} ${link_dst})

add_subdirectory(server)
add_subdirectory(client)