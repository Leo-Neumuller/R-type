/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Systems.cpp
*/

#include "Systems.hpp"

namespace ecs {

    /**
     * moveSystem
     * Move the entity
     * @param r: the registry
     * @param deltaTime: the delta time
     * @param pos: the position
     * @param vel: the velocity
     */
    void
    Systems::moveSystem(Registry &r, float &deltaTime, SparseArray<components::Position> &pos,
                        SparseArray<components::Velocity> &vel)
    {
        for (int i = 0; i < pos.size() && i < vel.size(); i++) {
            if (pos.has_index(i) && vel.has_index(i)) {
                pos[i]->x += vel[i]->vx * deltaTime;
                pos[i]->y += vel[i]->vy * deltaTime;
            }
        }
    }

    /**
     * manageMissiles
     * Manage the missiles
     * @param ecs: the registry
     * @param deltatime: the delta time
     * @param Missiles: the missiles
     */
    void Systems::manageMissiles(Registry &ecs, float deltatime, SparseArray<components::MissileStruct> &Missiles)
    {
        for (int i = 0; i < Missiles.size(); i++) {
            if (Missiles.has_index(i)) {
                Missiles[i]->lifeTimer += deltatime;
                if (Missiles[i]->lifeTimer >= 7.0f) {
                    ecs.killEntity(i);
                }
            }
        }
    }

} // ecs