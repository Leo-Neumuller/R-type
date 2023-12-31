/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** ClientComponents.hpp
*/

#ifndef R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP
#define R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP

#include <iostream>
#include "src/Loader.hpp"
#include <SFML/Graphics.hpp>
#include <queue>

namespace components {

    typedef sf::Sprite Drawable;
    typedef sf::Event Event;
    struct EventQueues {
        std::queue<sf::Event> keyboardEvents;
        std::queue<sf::Event> windowEvents;
    };
    typedef const std::map<std::string, sf::Texture> Textures;
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

} // ecs

#endif //R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP
