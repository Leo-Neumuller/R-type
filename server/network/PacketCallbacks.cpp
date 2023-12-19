/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** PacketCallbacks.cpp
*/

#include "PacketCallbacks.hpp"

namespace server {

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
        server->registerNewPlayer(fromId, components::Position{0, 0});
    }

    void PacketCallbacks::debugCallback(Server *server, std::map<int, network::NetworkClient> &_clients, int &fromId,
                                        std::string data)
    {
        std::cout << "Debug from client: " << data << std::endl;
    }

} // Server