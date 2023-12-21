/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** PacketCallback.cpp
*/

#include "PacketCallbacks.hpp"

namespace client {

    void PacketCallbacks::helloCallback(Client *client, network::NetworkClient &server, int &fromId, bool &data)
    {
        if (data) {
            std::cout << "Server accepted connection" << std::endl;
            client->setConnected(true);
        } else {
            std::cout << "Server refused connection" << std::endl;
            client->setConnected(false);
        }

        client->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, std::string>>(fromId, EPacketClient::DEBUG_PACKET_CLIENT, "Hello from client");
    }

    void PacketCallbacks::debugCallback(Client *client, network::NetworkClient &server, int &fromId, std::string &data)
    {
        std::cout << "Debug from server: " << data << std::endl;
    }

    void PacketCallbacks::newClientCallback(Client *client, network::NetworkClient &server, int &fromId, int &id,
                                            components::Position &pos)
    {
        std::cout << "New client {" << id << "} at {" << pos.x << ", " << pos.y << "}" << std::endl;
        client->registerNewPlayer(id, pos);
    }

    void PacketCallbacks::clientBaseInfoCallback(Client *client, network::NetworkClient &server, int &fromId, int &id,
                                                 components::Position &pos)
    {
        client->setCurrentPlayerId(id);
        client->registerNewPlayer(id, pos);

    }

    void PacketCallbacks::forceSetPosCallback(Client *client, network::NetworkClient &server, int &fromId, int &id,
                                              components::Position &pos, components::Velocity &vel)
    {
        auto &ids = client->getEcs().getComponent<components::Id>();

        for (auto &entity : client->getEcs().getEntities()) {
            if (ids.has_index(entity) && ids[entity] == id) {
                client->getEcs().getComponent<components::Position>()[entity] = pos;
                client->getEcs().getComponent<components::Velocity>()[entity] = vel;
                break;
            }
        }
    }

    void PacketCallbacks::sendPosVelCallback(Client *client, network::NetworkClient &server, int &fromId, int &id,
                                             components::Position &pos, components::Velocity &vel)
    {
        auto &ids = client->getEcs().getComponent<components::Id>();

        for (auto &entity : client->getEcs().getEntities()) {
            if (ids.has_index(entity) && ids[entity] == id) {
                client->getEcs().getComponent<components::Position>()[entity] = pos;
                client->getEcs().getComponent<components::Velocity>()[entity] = vel;
                break;
            }
        }

    }

} // client