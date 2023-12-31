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
#include "ClientSystems.hpp"

namespace client {

    Client::Client() : _server_list(), _network(_network_handler), _packets_registry(), _network_handler(_server_list, _packets_registry),
                        _server(nullptr), _connected(false), _ecs(), _renderer(_ecs), _current_player_id(0), _timed_events()
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
        _renderer.startRender();
        while (_renderer.isOpen()) {
            networkHandle();
            _ecs.runSystems();
            _timed_events.runEvents(deltatime);
            deltatime = _renderer.render();
        }
        _network.stop();
    }

    void Client::networkHandle()
    {
            while (!_network_handler.isPacketQueueEmpty()) {
                _server = &_server_list.begin()->second;
                try {
                    _network_handler.threatPacket();
                } catch (std::exception &e) {
                    std::cerr << "invalid packet from server: " << e.what() << std::endl;
                }
            }
            try {
                _network_handler.runPackets();
            } catch (std::exception &e) {
                std::cerr << "invalid packet from server: " << e.what() << std::endl;
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
        registerPacketClient<components::Position, components::Velocity>(EPacketClient::CLIENT_SEND_POS_VEL);

        registerPacketServer<bool>(PacketCallbacks::helloCallback, EPacketServer::SERVER_HELLO);
        registerPacketServer<std::string>(PacketCallbacks::debugCallback, EPacketServer::DEBUG_PACKET_SERVER);
        registerPacketServer<int, components::Position>(PacketCallbacks::newClientCallback, EPacketServer::NOTIFY_NEW_CLIENT);
        registerPacketServer<int, components::Position>(PacketCallbacks::clientBaseInfoCallback, EPacketServer::CLIENT_BASE_INFO);
        registerPacketServer<int, components::Position, components::Velocity>(PacketCallbacks::forceSetPosCallback, EPacketServer::FORCE_SET_POS_VEL);
        registerPacketServer<int, components::Position, components::Velocity>(PacketCallbacks::sendPosVelCallback, EPacketServer::SEND_POS_VEL);

        _ecs.registerComponent<components::Position>();
        _ecs.registerComponent<components::Velocity>();
        _ecs.registerComponent<components::Anim>();

        _ecs.registerComponent<components::MissileStruct>();
        _ecs.registerComponent<Loader *>();
        _ecs.registerComponent<components::Id>();
        _ecs.registerComponent<components::Drawable>();
        _ecs.registerComponent<components::Size>();
        _ecs.registerComponent<components::Event>();
        _ecs.registerComponent<components::Window>();
        _ecs.registerComponent<components::EventQueues>();
        _ecs.registerComponent<components::EntityType>();
        _ecs.registerComponent<components::NetworkHandler>();
        _ecs.registerComponent<components::LastVelocity>();
        _ecs.addSystem<components::Position, components::Velocity>(ecs::Systems::moveSystem, deltatime);
        _ecs.addSystem<components::Position, components::Drawable, components::Size>(ecs::ClientSystems::drawSystem);
        _ecs.addSystem<components::Event, components::Window, components::EventQueues>(ecs::ClientSystems::eventPollingSystem);
        _ecs.addSystem<components::Window, components::EventQueues>(ecs::ClientSystems::windowEventsSystem);
        _ecs.addSystem<components::EventQueues, components::Velocity, components::EntityType, components::Position>(ecs::ClientSystems::playerMoveEvent);
        _ecs.addSystem<components::Velocity, components::Position, components::EntityType, components::NetworkHandler, components::LastVelocity>(ecs::ClientSystems::playerMoveNetwork, deltatime);
        setupBackground();
        _ecs.addSystem<components::EventQueues, components::Velocity, components::EntityType, components::Position>(ecs::ClientSystems::playerMoveEvent);
        _ecs.addSystem<components::Drawable, components::Anim>(ecs::ClientSystems::spriteAnimation, deltatime);
        _ecs.addSystem<components::MissileStruct>(ecs::Systems::manageMissiles, deltatime);

        auto entity (_ecs.spawnEntity());
        _ecs.addComponent(entity, &_texturesFonts);
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
        _ecs.addComponent(entity, components::LastVelocity{0, 0});
        _ecs.addComponent(entity, components::Id{id});

        std::map<int, sf::IntRect> spriteRects;
        for (int i = 0; i < 5; ++i)
            spriteRects[i] = sf::IntRect(i * 58, 0, 58, 40);

        int n = id;
        for (; n > 4;)
            n -= 5;

        _ecs.addComponent(entity, components::Anim{5, 0, 0.1f, 0.0f, spriteRects});
        _ecs.addComponent(entity, components::Drawable(_texturesFonts.getTexture("player" + std::to_string(n + 1))));
        _ecs.addComponent(entity, components::Size{58, 40});
        _ecs.addComponent(entity, components::EntityType{components::EntityType::PLAYER});
    }

    void Client::setupBackground()
    {
        auto entity = _ecs.spawnEntity();

        _ecs.addComponent(entity, components::Position{0, 0});
        _ecs.addComponent(entity, components::Velocity{-500, 0});
        _ecs.addComponent(entity, components::Drawable{_texturesFonts.getTexture("background")});
        _ecs.addComponent(entity, components::Size{3840, 1080});
        _ecs.addComponent(entity, components::EntityType{components::EntityType::BACKGROUND});
    }

    Registry &Client::getEcs()
    {
        return _ecs;
    }

    void Client::setCurrentPlayer(int id)
    {
        auto &ids = getEcs().getComponent<components::Id>();
        auto &entity_types = getEcs().getComponent<components::EntityType>();

        for (auto entity : getEcs().getEntities()) {
            if (ids.has_index(entity) && entity_types.has_index(entity) && ids[entity] == id) {
                entity_types[entity] = components::EntityType::CURRENT_PLAYER;
                _ecs.addComponent(entity, &_network_handler);
                break;
            }
        }
        _current_player_id = id;
    }


} // client