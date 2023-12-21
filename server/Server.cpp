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
                       _ecs(), _network_thread(), _running(true), _timed_events()
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
        auto clock = std::chrono::high_resolution_clock::now();
        float deltatime = 0;
        float tick_duration = 40.96;

        setup(deltatime);
        while (_running) {
            auto newClock = std::chrono::high_resolution_clock::now();
            deltatime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(newClock - clock).count() / 1000;
            clock = newClock;
            networkHandler();
            _ecs.runSystems();
            _timed_events.runEvents(deltatime);
            std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::duration<float, std::milli>(tick_duration) - std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - newClock)));
        }

    }

    void Server::networkHandler()
    {
        if (!_network_handler.isPacketQueueEmpty()) {
            try {
                _network_handler.threatPacket();
            } catch (std::exception &e) {
                std::cerr << "invalid packet from client: " << e.what() << std::endl;
            }
        }
    }

    void Server::setup(float &deltatime)
    {
        registerPacketServer<bool>(EPacketServer::SERVER_HELLO);
        registerPacketServer<std::string>(EPacketServer::DEBUG_PACKET_SERVER);
        registerPacketServer<int, components::Position>(EPacketServer::NOTIFY_NEW_CLIENT);
        registerPacketServer<int, components::Position>(EPacketServer::CLIENT_BASE_INFO);
        registerPacketServer<int, components::Position, components::Velocity>(EPacketServer::FORCE_SET_POS_VEL);
        registerPacketServer<int, components::Position, components::Velocity>(EPacketServer::SEND_POS_VEL);

        registerPacketClient(PacketCallbacks::helloCallback, EPacketClient::CLIENT_HELLO);
        registerPacketClient<std::string>(PacketCallbacks::debugCallback, EPacketClient::DEBUG_PACKET_CLIENT);

        _ecs.registerComponent<components::Position>();
        _ecs.registerComponent<components::Velocity>();
        _ecs.registerComponent<components::Id>();
        _ecs.addSystem<components::Position, components::Velocity>(ecs::Systems::moveSystem, deltatime);

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

    TimedEvents &Server::getTimedEvents()
    {
        return _timed_events;
    }

    Registry &Server::getEcs()
    {
        return _ecs;
    }

    void Server::setPlayerPos(int id, components::Position pos)
    {
        auto &ids = getEcs().getComponent<components::Id>();

        for (auto &entity : getEcs().getEntities()) {
            if (ids[entity] == id) {
                _ecs.getComponent<components::Position>()[entity] = pos;
            }
        }
    }

    void Server::setPlayerVel(int id, components::Velocity vel)
    {
        auto &ids = getEcs().getComponent<components::Id>();

        for (auto &entity : getEcs().getEntities()) {
            if (ids[entity] == id) {
                _ecs.getComponent<components::Velocity>()[entity] = vel;
            }
        }
    }


} // Server