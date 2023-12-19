/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Components.hpp
*/

#ifndef R_TYPE_SERVER_COMPONENTS_HPP
#define R_TYPE_SERVER_COMPONENTS_HPP

#include <iostream>

namespace components {

    struct Position {
        float x;
        float y;
    };

    struct Velocity {
        float vx;
        float vy;
    };

    struct Size {
        float width;
        float height;
    };

    typedef int Id;

} // ecs

#endif //R_TYPE_SERVER_COMPONENTS_HPP
