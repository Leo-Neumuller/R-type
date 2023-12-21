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

namespace components {

    typedef sf::RectangleShape Drawable;
    typedef sf::Event Event;
    typedef std::queue<sf::Event> KeyboardEvents;
    typedef std::queue<sf::Event> WindowEvents;
    typedef sf::RenderWindow *Window;

} // ecs

#endif //R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP
