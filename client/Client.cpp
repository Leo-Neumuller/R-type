/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include "PacketCallbacks.hpp"
#include "Systems.hpp"
#include <utility>
#include "ClientComponents.hpp"

namespace client {

    Client::Client() : _server_list(), _network(_network_handler), _packets_registry(), _network_handler(_server_list, _packets_registry),
                        _server(nullptr), _connected(false), _ecs(), _renderer(_ecs), _current_player_id(0)
    {
    }

    Client::~Client()
    {
    }

    void Client::connectToServer(std::string address, int port)
    {
        registerPacketClient(EPacketClient::CLIENT_HELLO);
        auto first_data = _network_handler.serializePacket<network::GenericPacket<std::any>>(EPacketClient::CLIENT_HELLO);
        _network.run(std::move(address), port, *first_data);
    }

    void Client::runClient()
    {
        float deltatime = 0;

        setup(deltatime);
        std::thread network_thread(&Client::networkHandle, this);
        _renderer.startRender();
        while (_renderer.isOpen()) {
            _ecs.runSystems();
            deltatime = _renderer.render();
        }
    }

    void Client::networkHandle()
    {
        while (true) {
            _network_handler.waitForPacket();
            _server = &_server_list.begin()->second;
            try {
                _network_handler.threatPacket();
            } catch (std::exception &e) {
                std::cerr << "invalid packet from server: " << e.what() << std::endl;
            }
        }
    }

    network::PacketsRegistry &Client::getPacketsRegistry()
    {
        return _packets_registry;
    }

    network::NetworkHandler<EPacketServer> &Client::getNetworkHandler()
    {
        return _network_handler;
    }

    void Client::setup(float &deltatime)
    {
        registerPacketClient<std::string>(EPacketClient::DEBUG_PACKET_CLIENT);

        registerPacketServer<bool>(PacketCallbacks::helloCallback, EPacketServer::SERVER_HELLO);
        registerPacketServer<std::string>(PacketCallbacks::debugCallback, EPacketServer::DEBUG_PACKET_SERVER);
        registerPacketServer<int, components::Position>(PacketCallbacks::newClientCallback, EPacketServer::NOTIFY_NEW_CLIENT);
        registerPacketServer<int, components::Position>(PacketCallbacks::clientBaseInfoCallback, EPacketServer::CLIENT_BASE_INFO);
        registerPacketServer<int, components::Position, components::Velocity>(PacketCallbacks::forceSetPosCallback, EPacketServer::FORCE_SET_POS_VEL);
        registerPacketServer<int, components::Position, components::Velocity>(PacketCallbacks::sendPosVelCallback, EPacketServer::SEND_POS_VEL);

        _ecs.registerComponent<components::Position>();
        _ecs.registerComponent<components::Velocity>();
        _ecs.registerComponent<components::Id>();
        _ecs.addSystem<components::Position, components::Velocity>(ecs::Systems::moveSystem, deltatime);
        _ecs.registerComponent<components::Drawable>();
        _ecs.registerComponent<components::Size>();
    }

    bool Client::isConnected() const
    {
        return _connected;
    }

    void Client::setConnected(bool connected)
    {
        _connected = connected;
    }

    void Client::registerNewPlayer(int id, components::Position pos)
    {
        auto entity = _ecs.spawnEntity();

        _ecs.addComponent(entity, components::Position{pos.x, pos.y});
        _ecs.addComponent(entity, components::Velocity{0, 0});
        _ecs.addComponent(entity, components::Id{id});
        _ecs.addComponent(entity, components::Drawable{});
        _ecs.addComponent(entity, components::Size{100, 100});
    }

    int Client::getCurrentPlayerId() const
    {
        return _current_player_id;
    }

    void Client::setCurrentPlayerId(int currentPlayerId)
    {
        _current_player_id = currentPlayerId;
    }

    Registry &Client::getEcs()
    {
        return _ecs;
    }

} // client