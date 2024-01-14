/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** PacketCallbacks.cpp
*/

#include "PacketCallbacks.hpp"

namespace server {

    /**
     * helloCallback
     * Hello packet callback
     * @param server: the server
     * @param _clients: the clients
     * @param fromId: the id of the client
     */
    void PacketCallbacks::helloCallback(Server *server, std::map<int, network::NetworkClient> &_clients, int &fromId)
    {
        server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, std::string>>(fromId, EPacketServer::DEBUG_PACKET_SERVER, "Hello from server");
        if (_clients.find(fromId) == _clients.end()) {
            std::cout << "Client not found" << std::endl;
            return;
        }
        if (_clients.at(fromId).isConnected()) {
            std::cout << "Client already connected" << std::endl;
            return;
        }
        if (_clients.size() == 5) {
            std::cout << "Server full" << std::endl;
            return;
        }
        std::cout << "New Client id {" << fromId << "}" << std::endl;
        _clients.at(fromId).setConnected(true);

        server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, bool>>(fromId, EPacketServer::SERVER_HELLO, true);
        for (int i = 0; i < _clients.size(); ++i) {
            if (i == fromId)
                continue;
            if (_clients.at(i).isConnected()) {
                std::cout << "Send to client {" << i << "}" << std::endl;
                server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, int, components::Position>>(fromId, EPacketServer::NOTIFY_NEW_CLIENT, i, components::Position{0, 0});
                server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, int, components::Position>>(i, EPacketServer::NOTIFY_NEW_CLIENT, fromId, components::Position{0, 0});
            }
        }
        server->registerNewPlayer(fromId, components::Position{0, (float)fromId * 100});
        server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, int, components::Position>>(fromId, EPacketServer::CLIENT_BASE_INFO, fromId, components::Position{0, (float)fromId * 100});

        auto &ids = server->getEcs().getComponent<components::Id>();

            for (auto &entity : server->getEcs().getEntities()) {
                if (ids.has_index(entity) && ids[entity] != fromId) {
                    server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, int, components::Position, components::Velocity>>(
                            fromId, EPacketServer::FORCE_SET_POS_VEL, ids[entity].value(), server->getEcs().getComponent<components::Position>()[entity].value(), server->getEcs().getComponent<components::Velocity>()[entity].value());
                    server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, int, components::Position, components::Velocity>>(
                            ids[entity].value(), EPacketServer::FORCE_SET_POS_VEL, fromId, server->getEcs().getComponent<components::Position>()[fromId].value(), server->getEcs().getComponent<components::Velocity>()[fromId].value());
                }
            }
    }

    /**
     * debugCallback
     * Debug packet callback
     * @param server: the server
     * @param _clients: the clients
     * @param fromId: the id of the client
     * @param data: the debug string
     */
    void PacketCallbacks::debugCallback(Server *server, std::map<int, network::NetworkClient> &_clients, int &fromId,
                                        std::string data)
    {
        std::cout << "Debug from client: " << data << std::endl;
    }

    /**
     * sendPosVelCallback
     * Send position and velocity packet callback
     * @param server: the server
     * @param _clients: the clients
     * @param fromId: the id of the client
     * @param pos: the position of the client
     * @param vel: the velocity of the client
     */
    void
    PacketCallbacks::sendPosVelCallback(Server *server, std::map<int, network::NetworkClient> &_clients, int &fromId,
                                        components::Position pos, components::Velocity vel)
    {
        auto &ids = server->getEcs().getComponent<components::Id>();
        auto &poss = server->getEcs().getComponent<components::Position>();
        auto &vels = server->getEcs().getComponent<components::Velocity>();

        server->setPlayerVel(fromId, vel);

        for (auto &entity : server->getEcs().getEntities()) {
            if (ids.has_index(entity) && ids[entity] != fromId) {
                server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, int, components::Position, components::Velocity>>(
                        ids[entity].value(), EPacketServer::SEND_POS_VEL, fromId, server->getEcs().getComponent<components::Position>()[fromId].value(), server->getEcs().getComponent<components::Velocity>()[fromId].value());
            }
        }
        for (auto &entity : server->getEcs().getEntities()) {
            if (ids.has_index(entity) && poss.has_index(entity) && vels.has_index(entity) && ids[entity] == fromId) {
                if (poss[entity].value().x - pos.x > 20 || poss[entity].value().y - pos.y > 20 || poss[entity].value().x - pos.x < -20 || poss[entity].value().y - pos.y < -20) {
                    server->getNetworkHandler().serializeSendPacket<network::GenericPacket<std::any, int, components::Position, components::Velocity>>(
                            fromId, EPacketServer::FORCE_SET_POS_VEL, ids[entity].value(), server->getEcs().getComponent<components::Position>()[entity].value(), server->getEcs().getComponent<components::Velocity>()[entity].value());
                }

            }
        }
    }

} // Server