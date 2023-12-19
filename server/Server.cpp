/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Server.cpp
*/

#include "Server.hpp"
#include "PacketCallbacks.hpp"
#include "Entity.hpp"
#include "Systems.hpp"

namespace server {

    Server::Server() : _clients(), _network(_network_handler), _packets_registry(), _network_handler(_clients, _packets_registry),
                       _ecs()
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
                std::cerr << "invalid packet from client: " << e.what() << std::endl;
            }
            _ecs.runSystems();
        }
    }

    void Server::setup()
    {
        registerPacketClient(PacketCallbacks::helloCallback,EPacketClient::CLIENT_HELLO);
        registerPacketServer<bool>(EPacketServer::SERVER_HELLO);
        registerPacketServer<std::string>(EPacketServer::DEBUG_PACKET_SERVER);
        registerPacketClient<std::string>(PacketCallbacks::debugCallback, EPacketClient::DEBUG_PACKET_CLIENT);
        registerPacketServer<int, components::Position>(EPacketServer::NOTIFY_NEW_CLIENT);

        _ecs.registerComponent<components::Position>();
        _ecs.registerComponent<components::Velocity>();
        _ecs.registerComponent<components::Id>();
        _ecs.addSystem<components::Position, components::Velocity>(ecs::Systems::moveSystem);
    }

    network::PacketsRegistry &Server::getPacketsRegistry()
    {
        return _packets_registry;
    }

    network::NetworkHandler<EPacketClient> &Server::getNetworkHandler()
    {
        return _network_handler;
    }

    void Server::registerNewPlayer(int id, components::Position pos)
    {
        auto entity = _ecs.spawnEntity();

        _ecs.addComponent(entity, components::Position{pos.x, pos.y});
        _ecs.addComponent(entity, components::Velocity{0, 0});
        _ecs.addComponent(entity, components::Id{id});
    }


} // Server