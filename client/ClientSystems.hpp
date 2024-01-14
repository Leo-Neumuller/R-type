/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** ClientSystems.hpp
*/

#ifndef R_TYPE_CLIENT_CLIENTSYSTEMS_HPP
#define R_TYPE_CLIENT_CLIENTSYSTEMS_HPP

#include <iostream>
#include "Client.hpp"
#include "Registry.hpp"
#include "Components.hpp"
#include "SparseArray.hpp"
#include "ClientComponents.hpp"
#include "Entity.hpp"
#include "src/Loader.hpp"
#include "network/NetworkHandler.hpp"
#include "network/NetworkClient.hpp"
#include <SFML/Graphics.hpp>


namespace ecs {

    /**
     * ClientSystems
     * Class of the client systems
     */
    class ClientSystems {
        public:
            ClientSystems() = delete;
            ~ClientSystems() = delete;

            static void spawnEnemyMissile(Registry &ecs, int enemyIndex, float x, float y);
            static void spawnEnnemy(Registry &ecs, float x, float y);
            static void playerMissile(Registry &ecs, int index, float x, float y);
            static void drawSystem(Registry &ecs, float deltatime, SparseArray<components::Position> &pos, SparseArray<components::Drawable> &draw,
                               SparseArray<components::Size> &size, SparseArray<components::Enemy> &enemy, SparseArray<components::Velocity> &vel);
            static void eventPollingSystem(Registry &ecs, SparseArray<components::Event> &event, SparseArray<components::Window> &window,
                                           SparseArray<components::EventQueues> &event_queues);
            static void windowEventsSystem(Registry &ecs, SparseArray<components::Window> &window, SparseArray<components::EventQueues> &event_queues);
            static void playerMoveEvent(Registry &ecs, SparseArray<components::EventQueues> &event_queues, SparseArray<components::Velocity> &vel,
                                        SparseArray<components::EntityType> &type, SparseArray<components::Position> &pos);
            static void playerMoveNetwork(Registry &ecs, float &deltatime, SparseArray<components::Velocity> &vel, SparseArray<components::Position> &pos,
                                              SparseArray<components::EntityType> &type, SparseArray<components::NetworkHandler> &network_handler,
                                              SparseArray<components::LastVelocity> &last_vel);
            static void spriteAnimation(Registry &ecs, float deltatime, SparseArray<components::Drawable> &draw, SparseArray<components::Anim> &Anim);
        protected:



    protected:

        private:

    };

} // client

#endif //R_TYPE_CLIENT_CLIENTSYSTEMS_HPP
