/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Systems.hpp
*/

#ifndef R_TYPE_SERVER_SYSTEMS_HPP
#define R_TYPE_SERVER_SYSTEMS_HPP

#include <iostream>
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "Components.hpp"
#include "../client/ClientComponents.hpp"


namespace ecs {

    /*
     * Systems
     * Class of the systems
     */
    class Systems {
        public:
            Systems() = delete;
            ~Systems() = delete;

            static void moveSystem(Registry &r, float &deltaTime, SparseArray<components::Position> &pos,
                                   SparseArray<components::Velocity> &vel);
            static void manageMissiles(Registry &ecs, float deltatime, SparseArray<components::MissileStruct> &Missiles);

            static void manageHitBox(Registry &ecs, float &deltatime, SparseArray<components::EntityType> &entityType,
                                              SparseArray<components::Position> &pos, SparseArray<components::Size> &size,
                                              SparseArray<components::playerData> &plyData, SparseArray<components::Enemy> &enemy);
            static void spawnEnemy(Registry &ecs, float &deltatime, SparseArray<components::EnemySpawnData> &EnemySpawnData);
            static void enemyDeath(Registry &ecs, float deltatime, SparseArray<components::Enemy> &enemy, SparseArray<components::EnemySpawnData> &EnemySpawnData);
            static void playerDeath(Registry &ecs, float deltatime, SparseArray<components::playerData> &plyData);

    protected:

        private:

    };

} // ecs

#endif //R_TYPE_SERVER_SYSTEMS_HPP
