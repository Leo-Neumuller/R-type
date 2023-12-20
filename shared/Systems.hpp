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

namespace ecs {

    class Systems {
        public:
            Systems() = delete;
            ~Systems() = delete;

            static void moveSystem(Registry &r, float &deltaTime, SparseArray<components::Position> &pos,
                                   SparseArray<components::Velocity> &vel);
        protected:

        private:

    };

} // ecs

#endif //R_TYPE_SERVER_SYSTEMS_HPP
