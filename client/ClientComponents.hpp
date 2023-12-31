/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** ClientComponents.hpp
*/

#ifndef R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP
#define R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include "network/NetworkHandler.hpp"

namespace components {

    typedef sf::RectangleShape Drawable;
    typedef sf::Event Event;
    struct EventQueues {
        std::queue<sf::Event> keyboardEvents;
        std::queue<sf::Event> windowEvents;
    };
    typedef sf::RenderWindow *Window;
    enum class EntityType {
        CURRENT_PLAYER,
        PLAYER,
        ENEMY,
        BACKGROUND,
        BULLET,
        OBSTACLE,
        UI,
        BUTTON,
        TEXT,
        CURSOR,
        SOUND,
        MUSIC,
        ANIMATION,
        PARTICLE,
        UNKNOWN
    };
    typedef network::NetworkHandler<EPacketServer> *NetworkHandler;
    struct LastVelocity {
        float vx;
        float vy;
    };

} // ecs

#endif //R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP
