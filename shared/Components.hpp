/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Components.hpp
*/

#ifndef R_TYPE_SERVER_COMPONENTS_HPP
#define R_TYPE_SERVER_COMPONENTS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

namespace components
{

    struct Position
    {
        float x;
        float y;
    };

    struct Velocity
    {
        float vx;
        float vy;
    };

    struct Size
    {
        float width;
        float height;
    };

    struct Anim
    {
        int nbFrame;
        int actualFrame;
        float animationInterval;
        float animationTimer;
        std::map<int, sf::IntRect> spriteFrames;
    };

    struct MissileStruct
    {
        float lifeTimer;
        bool active;
    };

    struct Enemy
    {
        int life;
        int attack;
        float missileTimer;
    };

    typedef int Id;

} // ecs

#endif // R_TYPE_SERVER_COMPONENTS_HPP
