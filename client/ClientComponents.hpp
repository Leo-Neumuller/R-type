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
#include "network/NetworkHandler.hpp"

namespace components {

    /*
     * Drawable
     * Component of the drawable
     * @sprite: sprite of the drawable
     */
    typedef sf::Sprite Drawable;

    /*
     * Event
     * Component of the event
     * @event: event
     */
    typedef sf::Event Event;

    /*
     * EventQueues
     * Component of the event queues
     * @keyboardEvents: queue of keyboard events
     * @windowEvents: queue of window events
     */
    struct EventQueues {
        std::queue<sf::Event> keyboardEvents;
        std::queue<sf::Event> windowEvents;
    };

    /*
     * Textures
     * Component of the textures
     * @textures: map of textures
     */
    typedef const std::map<std::string, sf::Texture> Textures;

    /*
     * Window
     * Component of the window
     * @window: pointer to the window
     */
    typedef sf::RenderWindow *Window;

    /*
     * EntityType
     * Enum of the entity types
     * @CURRENT_PLAYER: current player
     * @PLAYER: player
     * @ENEMY: enemy
     * @BACKGROUND: background
     * @BULLET: bullet
     * @OBSTACLE: obstacle
     * @UI: UI
     * @BUTTON: button
     * @TEXT: text
     * @CURSOR: cursor
     * @SOUND: sound
     * @MUSIC: music
     * @ANIMATION: animation
     * @PARTICLE: particle
     * @UNKNOWN: unknown
     */
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

    /*
     * NetworkHandler
     * Component of the network handler
     * @networkHandler: pointer to the network handler
     */
    typedef network::NetworkHandler<EPacketServer> *NetworkHandler;

    /*
     * LastVelocity
     * Component of the last velocity
     * @vx: last x velocity
     * @vy: last y velocity
     */
    struct LastVelocity {
        float vx;
        float vy;
    };

} // ecs

#endif //R_TYPE_CLIENT_CLIENTCOMPONENTS_HPP
