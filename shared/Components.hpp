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


namespace components {

    /**
     * Position
     * Structure of the position
     */
    struct Position {
        float x;
        float y;
    };

    /**
     * Velocity
     * Structure of the velocity
     */
    struct Velocity {
        float vx;
        float vy;
    };

    /**
     * Size
     * Structure of the size
     */
    struct Size {
        float width;
        float height;
    };

    /**
     * MissileStruct
     * Structure of the missile
     */
    struct MissileStruct {
        float lifeTimer;
        bool active;
    };

    struct Enemy
    {
        int life;
        int attack;
        float missileCouldown;
    };

    struct EnemySpawnData
    {
        int nbEnemy;
        float spawnCouldown;
    };

    struct playerData {
        float fireCouldown;
        float actualCD;
        int life;
        int nbKills;
    };

    typedef int Id;

    /**
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
        ENEMYBULLET,
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

#endif //R_TYPE_SERVER_COMPONENTS_HPP
