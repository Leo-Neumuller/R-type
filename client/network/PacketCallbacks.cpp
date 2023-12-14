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

} // client