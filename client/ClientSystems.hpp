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

namespace ecs {

    class ClientSystems {
        public:
            ClientSystems() = delete;
            ~ClientSystems() = delete;

            static void drawSystem(Registry &ecs, SparseArray<components::Position> &pos, SparseArray<components::Drawable> &draw,
                                   SparseArray<components::Size> &size);
            static void eventPollingSystem(Registry &ecs, SparseArray<components::Event> &event, SparseArray<components::Window> &window,
                                           SparseArray<components::KeyboardEvents> &keyboardEvents, SparseArray<components::WindowEvents> &windowEvents);
            static void windowEventsSystem(Registry &ecs, SparseArray<components::Window> &window, SparseArray<components::WindowEvents> &windowEvents);

        protected:

        private:

    };

} // client

#endif //R_TYPE_CLIENT_CLIENTSYSTEMS_HPP
