/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Systems.cpp
*/

#include "Systems.hpp"

namespace ecs {

    void
    Systems::moveSystem(Registry &r, SparseArray<components::Position> &pos, SparseArray<components::Velocity> &vel)
    {
        for (int i = 0; i < pos.size() && i < vel.size(); i++) {
            if (pos.has_index(i) && vel.has_index(i)) {
                pos[i]->x += vel[i]->vx;
                pos[i]->y += vel[i]->vy;
            }
        }
    }

} // ecs