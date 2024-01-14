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
#include "ServerComponents.hpp"
#include "ServerSystems.hpp"

namespace server {

    /**
     * Server
     * Constructor of Server
     */
    Server::Server() : _clients(), _network(_network_handler), _packets_registry(), _network_handler(_clients, _packets_registry),
                       _ecs(), _network_thread(), _running(true), _timed_events()
    {
    }

    /**
     * ~Server
     * Destructor of Server
     */
    Server::~Server()
    {
    }

    /**
     * runNetwork
     * Run the network
     * @param port: the port
     */
    void Server::runNetwork(int port)
    {
        _network.run(port);
    }

    /**
     * runServer
     * Run the server
     */
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

    /**
     * networkHandler
     * Handle the network
     */
    void Server::networkHandler()
    {
        while (!_network_handler.isPacketQueueEmpty()) {
//            try {
                _network_handler.threatPacket();
//            } catch (std::exception &e) {
//                std::cerr << "invalid packet from client: " << e.what() << std::endl;
//            }
        }
//        try {
            _network_handler.runPackets();
//        } catch (std::exception &e) {
//            std::cerr << "invalid packet from server: " << e.what() << std::endl;
//        }
    }

    /**
     * setup
     * Setup the server (register packets, components, systems)
     * @param deltatime: the deltatime
     */
    void Server::setup(float &deltatime)
    {
        registerPacketServer<bool>(EPacketServer::SERVER_HELLO);
        registerPacketServer<std::string>(EPacketServer::DEBUG_PACKET_SERVER);
        registerPacketServer<int, components::Position>(EPacketServer::NOTIFY_NEW_CLIENT);
        registerPacketServer<int, components::Position>(EPacketServer::CLIENT_BASE_INFO);
        registerPacketServer<int, components::Position, components::Velocity>(EPacketServer::FORCE_SET_POS_VEL);
        registerPacketServer<int, components::Position, components::Velocity>(EPacketServer::SEND_POS_VEL);
        registerPacketServer<int>(EPacketServer::PLAYER_SHOOT_BULLET);
        registerPacketServer<int, components::Position>(EPacketServer::SPAWN_ENEMY);
        registerPacketServer<int, components::Position, components::Velocity, bool>(EPacketServer::MOVE_ENEMY);
        registerPacketServer<int>(EPacketServer::SHOOT_ENEMY);

        registerPacketClient(PacketCallbacks::helloCallback, EPacketClient::CLIENT_HELLO);
        registerPacketClient<std::string>(PacketCallbacks::debugCallback, EPacketClient::DEBUG_PACKET_CLIENT);
        registerPacketClient<components::Position, components::Velocity>(PacketCallbacks::sendPosVelCallback, EPacketClient::CLIENT_SEND_POS_VEL);
        registerPacketClient(PacketCallbacks::playerShootCallback, EPacketClient::SHOOT_BULLET);

        _ecs.registerComponent<components::ServerNetworkHandler>();
        _ecs.registerComponent<components::Position>();
        _ecs.registerComponent<components::Velocity>();
        _ecs.registerComponent<components::Id>();
        _ecs.registerComponent<components::EntityType>();
        _ecs.registerComponent<components::Size>();
        _ecs.registerComponent<components::MissileStruct>();
        _ecs.registerComponent<components::Enemy>();
        _ecs.registerComponent<components::EnemySpawnData>();
        _ecs.addSystem<components::Position, components::Velocity>(ecs::Systems::moveSystem, deltatime);
        _ecs.addSystem<components::MissileStruct>(ecs::Systems::manageMissiles, deltatime);
//        _ecs.addSystem<components::EnemySpawnData>(ecs::ServerSystems::spawnEnemy, deltatime);
//        _ecs.addSystem<components::Position, components::Velocity, components::Enemy>(ecs::ServerSystems::moveEnemy, deltatime);

    }

    /**
     * getPacketsRegistry
     * Get the packets registry
     * @return: the packets registry
     */
    network::PacketsRegistry &Server::getPacketsRegistry()
    {
        return _packets_registry;
    }

    /**
     * getNetworkHandler
     * Get the network handler
     * @return: the network handler
     */
    network::NetworkHandler<EPacketClient> &Server::getNetworkHandler()
    {
        return _network_handler;
    }

    /**
     * registerNewPlayer
     * Register a new player
     * @param id: the id of the player
     * @param pos: the position of the player
     */
    void Server::registerNewPlayer(int id, components::Position pos)
    {
        auto entity = _ecs.spawnEntity();

        _ecs.addComponent(entity, components::ServerNetworkHandler{&_network_handler});
        _ecs.addComponent(entity, components::Position{pos.x, pos.y});
        _ecs.addComponent(entity, components::Velocity{0, 0});
        _ecs.addComponent(entity, components::Id{id});
    }

    /**
     * getTimedEvents
     * Get the timed events
     * @return: the timed events
     */
    TimedEvents &Server::getTimedEvents()
    {
        return _timed_events;
    }

    /**
     * getEcs
     * Get the ecs
     * @return: the ecs
     */
    Registry &Server::getEcs()
    {
        return _ecs;
    }

    /**
     * setPlayerPos
     * Set the player position
     * @param id: the id of the player
     * @param pos: the position of the player
     */
    void Server::setPlayerPos(int id, components::Position pos)
    {
        auto &ids = getEcs().getComponent<components::Id>();

        for (auto &entity : getEcs().getEntities()) {
            if (ids[entity] == id) {
                _ecs.getComponent<components::Position>()[entity] = pos;
            }
        }
    }

    /**
     * setPlayerVel
     * Set the player velocity
     * @param id: the id of the player
     * @param vel: the velocity of the player
     */
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