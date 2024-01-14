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

    void Systems::manageHitBox(Registry &ecs, float &deltatime, SparseArray<components::EntityType> &entityType,
                               SparseArray<components::Position> &pos, SparseArray<components::Size> &size,
                               SparseArray<components::playerData> &plyData, SparseArray<components::Enemy> &enemy) {

        for (int i = 0; i < pos.size(); i++) {
            if (pos.has_index(i) && entityType.has_index(i) && size.has_index(i)) {
                if ((entityType[i] == components::EntityType::PLAYER || entityType[i] == components::EntityType::CURRENT_PLAYER)&& plyData.has_index(i)) {
                    for (int v = 0; v < pos.size(); v++) {
                        if (pos.has_index(v) && entityType.has_index(v) && size.has_index(v)) {
                            if (entityType[v] == components::EntityType::ENEMYBULLET) {
                                if (((pos[v]->x > pos[i]->x && pos[v]->x < pos[i]->x + size[i]->width) &&
                                    (pos[v]->y > pos[i]->y && pos[v]->y < pos[i]->y + size[i]->height)) ||
                                    ((pos[v]->x + size[v] ->width > pos[i]->x && pos[v]->x + size[v] ->width  < pos[i]->x + size[i]->width) &&
                                    (pos[v]->y + size[v]->height > pos[i]->y && pos[v]->y + size[v]->height < pos[i]->y + size[i]->height))) {
                                    ecs.killEntity(v);
                                    plyData[i]->life--; // trouver de quel enemy vient la bullet pour recuperer l'attack (si on a le temps de faire d'autres enemy)

                                }
                            }

                        }
                    }
                }
                if (entityType[i] == components::EntityType::ENEMY && enemy.has_index(i)) {
                    for (int v = 0; v < pos.size(); v++) {
                        if (pos.has_index(v) && entityType.has_index(v) && size.has_index(v)) {
                            if (entityType[v] == components::EntityType::BULLET) {
                                if (((pos[v]->x > pos[i]->x && pos[v]->x < pos[i]->x + size[i]->width) &&
                                     (pos[v]->y > pos[i]->y && pos[v]->y < pos[i]->y + size[i]->height)) ||
                                    ((pos[v]->x + size[v] ->width > pos[i]->x && pos[v]->x + size[v] ->width  < pos[i]->x + size[i]->width) &&
                                     (pos[v]->y + size[v]->height > pos[i]->y && pos[v]->y + size[v]->height < pos[i]->y + size[i]->height))) {
                                    ecs.killEntity(v);
                                    enemy[i]->life--;
                                    // rajouter a qui appartient le missile et ajouter un aux kills
                                }
                            }

                        }
                    }
                }
            }
        }
    }

    void Systems::enemyDeath(Registry &ecs, float deltatime, SparseArray<components::Enemy> &enemy, SparseArray<components::EnemySpawnData> &enemySpawnData)
    {
        for (int i = 0; i < enemy.size(); i++) {
            if (enemy.has_index(i)) {
                if (enemy[i]->life == 0) {
                    ecs.killEntity(i);
                    for (int c = 0; c < enemySpawnData.size(); c++) {
                        if (enemy.has_index(c)) {
                            enemySpawnData[i]->nbEnemy--;
                        }
                    }
                }
            }
        }
    }

    void Systems::playerDeath(Registry &ecs, float deltatime, SparseArray<components::playerData> &plyData)
    {
        for (int i = 0; i < plyData.size(); i++) {
            if (plyData.has_index(i)) {
                if (plyData[i]->life == 0) {
                    ecs.killEntity(i);
                }
            }
        }
    }


} // ecs