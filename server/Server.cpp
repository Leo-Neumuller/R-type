/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Server.cpp
*/

#include "Server.hpp"
#include "PacketCallbacks.hpp"

namespace server {

    Server::Server() : _clients(), _network(_network_handler), _packets_registry(), _network_handler(_clients, _packets_registry)
    {
    }

    Server::~Server()
    {
    }

    void Server::runNetwork(int port)
    {
        _network.run(port);
    }

    void Server::runServer()
    {
        setup();
        while (true) {
            _network_handler.waitForPacket();
            try {
                _network_handler.threatPacket();
            } catch (std::exception &e) {
                std::cerr << "invalid packet from client" << std::endl;
            }
        }
    }

    void Server::setup()
    {
        registerPacketClient(PacketCallbacks::helloCallback,EPacketClient::CLIENT_HELLO);
        registerPacketServer<bool>(EPacketServer::SERVER_HELLO);
        registerPacketServer<std::string>(EPacketServer::DEBUG_PACKET_SERVER);
        registerPacketClient<std::string>(PacketCallbacks::debugCallback, EPacketClient::DEBUG_PACKET_CLIENT);
    }

    network::PacketsRegistry &Server::getPacketsRegistry()
    {
        return _packets_registry;
    }

    network::NetworkHandler<EPacketClient> &Server::getNetworkHandler()
    {
        return _network_handler;
    }


} // Server