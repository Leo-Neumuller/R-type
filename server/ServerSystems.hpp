/*
** EPITECH PROJECT, 2024
** r-type_server
** File description:
** ServerSystems.hpp
*/

#ifndef R_TYPE_SERVER_SERVERSYSTEMS_HPP
#define R_TYPE_SERVER_SERVERSYSTEMS_HPP

#include <iostream>
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "ServerComponents.hpp"
#include "Components.hpp"


namespace ecs {

    class ServerSystems {
        public:
            static void spawnEnemy(Registry &ecs, float &deltatime, SparseArray<components::EnemySpawnData> &EnemySpawnData);
            static void moveEnemy(Registry &ecs, float &deltatime, SparseArray<components::Position> &pos,
                                  SparseArray<components::Velocity> &vel, SparseArray<components::Enemy> &enemy);

        protected:

        private:

    };

} // server

#endif //R_TYPE_SERVER_SERVERSYSTEMS_HPP
