/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Client.hpp
*/

#ifndef R_TYPE_CLIENT_CLIENT_HPP
#define R_TYPE_CLIENT_CLIENT_HPP

#include <iostream>
#include "network/Network.hpp"
#include "network/NetworkHandler.hpp"
#include "network/NetworkClient.hpp"
#include "Registry.hpp"
#include "Components.hpp"
#include "Render.hpp"
#include <chrono>

namespace client {

    class Client {
        public:
            Client();
            ~Client();

            void connectToServer(std::string address, int port);
            void runClient();
            network::PacketsRegistry &getPacketsRegistry();
            network::NetworkHandler<EPacketServer> &getNetworkHandler();

            template<typename... Args, typename Func>
            void registerPacketServer(Func func, EPacketServer packet) {
                _packets_registry.registerPacketServer<Args...>([this, func](int id, Args... args) {func(this, *_server, id, args...);}, packet);
            }

            template<typename... Args>
            void registerPacketClient(EPacketClient packet) {
                _packets_registry.registerPacketClient<Args...>([](int id, Args... args) {}, packet);
            }

            bool isConnected() const;
            void setConnected(bool connected);
            void registerNewPlayer(int id, components::Position pos);
            int getCurrentPlayerId() const;
            void setCurrentPlayerId(int currentPlayerId);
            Registry &getEcs();
        protected:

        private:
            void setup(float &deltatime);
            void networkHandle();

            std::map<int, network::NetworkClient> _server_list;
            Network _network;
            network::PacketsRegistry _packets_registry;
            network::NetworkHandler<EPacketServer> _network_handler;
            network::NetworkClient *_server;
            bool _connected;
            Registry _ecs;
            Render _renderer;
            int _current_player_id;

    };

} // client

#endif //R_TYPE_CLIENT_CLIENT_HPP
