/*
** EPITECH PROJECT, 2024
** r-type_server
** File description:
** ServerSystems.cpp
*/

#include "ServerSystems.hpp"

namespace ecs {

    void ServerSystems::spawnEnemy(Registry &ecs, float &deltatime, SparseArray<components::EnemySpawnData> &EnemySpawnData)
    {
        auto network_handlers = ecs.getComponent<components::ServerNetworkHandler>();
        auto clients = ecs.getComponent<components::Id>();
        static float cooldown = 0;
        static int nbEnemies = 0;

//        for (int i = 0; i < EnemySpawnData.size(); i++) {
//            if (EnemySpawnData.has_index(i)) {
                cooldown += deltatime;
                int timeTmp = rand() % 4 + 2;
                if (cooldown > timeTmp) {
                    auto enemy(ecs.spawnEntity());
                    ecs.addComponent(enemy, components::Position{745, (float) (rand() % 971 + 30)});
                    ecs.addComponent(enemy, components::Velocity{0, 0});
                    ecs.addComponent(enemy, components::Size{55, 55});
                    ecs.addComponent(enemy, components::EntityType{components::EntityType::ENEMY});
                    ecs.addComponent(enemy, components::Enemy{2, 1, 0.0f, nbEnemies});
                    cooldown = 0;

                    for (int e = 0; e < network_handlers.size(); e++) {
                        if (network_handlers.has_index(e)) {
                            for (int j = 0; j < clients.size(); ++j) {
                                if (clients.has_index(j)) {
                                    network_handlers[e].value()->serializeSendPacket<network::GenericPacket<std::any, int, components::Position>>(
                                            clients[j].value(), EPacketServer::SPAWN_ENEMY, nbEnemies, ecs.getComponent<components::Position>()[enemy].value());
                                }
                            }
                        }
                    }
                    nbEnemies++;
                }
//            }
//        }
    }

    void ServerSystems::moveEnemy(Registry &ecs, float &deltatime, SparseArray<components::Position> &pos,
                                  SparseArray<components::Velocity> &vel, SparseArray<components::Enemy> &enemy)
    {
        auto network_handlers = ecs.getComponent<components::ServerNetworkHandler>();
        auto clients = ecs.getComponent<components::Id>();
        static float delay = 0;

        delay += deltatime;
        if (delay < 0.3f)
            return;
        delay = 0;
        for (int i = 0; i < enemy.size(); i++)
        {
            if (enemy.has_index(i))
            {
                pos[i]->y = std::max(0.0f, std::min(545.0f, pos[i]->y));

                float moveSpeed = 150;
                if (rand() % 500 == 0)
                {
                    vel[i]->vy = (vel[i]->vy > 0) ? -moveSpeed : moveSpeed;

                    for (int e = 0; e < network_handlers.size(); e++) {
                        if (network_handlers.has_index(e)) {
                            for (int j = 0; j < clients.size(); ++j) {
                                if (clients.has_index(j)) {
                                    network_handlers[e].value()->serializeSendPacket<network::GenericPacket<std::any, int, components::Position, components::Velocity, bool>>(
                                            clients[j].value(), EPacketServer::MOVE_ENEMY,
                                            enemy[i]->id,
                                            ecs.getComponent<components::Position>()[i].value(),
                                            ecs.getComponent<components::Velocity>()[i].value(),
                                            false);
                                    break;
                                }
                            }
                        }
                    }
                }

                enemy[i]->missileCouldown += deltatime;
                if (enemy[i]->missileCouldown >= rand() % 4 + 2)
                {
                    for (int e = 0; e < network_handlers.size(); e++) {
                        if (network_handlers.has_index(e)) {
                            for (int j = 0; j < clients.size(); ++j) {
                                if (clients.has_index(j)) {
                                    network_handlers[e].value()->serializeSendPacket<network::GenericPacket<std::any, int>>(
                                            clients[j].value(), EPacketServer::SHOOT_ENEMY, enemy[i]->id);
                                }
                            }
                        }
                    }
                    enemy[i]->missileCouldown = 0.0f;
                }
            }
        }
    }

} // server