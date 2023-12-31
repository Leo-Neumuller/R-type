/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** ClientSystems.hpp
*/

#ifndef R_TYPE_CLIENT_CLIENTSYSTEMS_HPP
#define R_TYPE_CLIENT_CLIENTSYSTEMS_HPP

#include <iostream>
#include "Registry.hpp"
#include "Components.hpp"
#include "SparseArray.hpp"
#include "ClientComponents.hpp"
#include "Entity.hpp"
#include "src/Loader.hpp"

namespace ecs {

    class ClientSystems {
        public:
            ClientSystems() = delete;
            ~ClientSystems() = delete;

            static void playerMissile(Registry &ecs, int index, float x, float y);



            static void drawSystem(Registry &ecs, SparseArray<components::Position> &pos, SparseArray<components::Drawable> &draw,
                                   SparseArray<components::Size> &size);
            static void eventPollingSystem(Registry &ecs, SparseArray<components::Event> &event, SparseArray<components::Window> &window,
                                           SparseArray<components::EventQueues> &event_queues);
            static void windowEventsSystem(Registry &ecs, SparseArray<components::Window> &window, SparseArray<components::EventQueues> &event_queues);
            static void playerMoveEvent(Registry &ecs, SparseArray<components::EventQueues> &event_queues,
                                            SparseArray<components::Velocity> &vel,
                                            SparseArray<components::EntityType> &type,
                                            SparseArray<components::Position> &pos);


            static void spriteAnimation(Registry &ecs, float deltatime, SparseArray<components::Drawable> &draw, SparseArray<components::Anim> &Anim);

    protected:

        private:


    };

} // client

#endif //R_TYPE_CLIENT_CLIENTSYSTEMS_HPP
