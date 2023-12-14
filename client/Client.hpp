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
        protected:

        private:
            void setup();

            std::map<int, network::NetworkClient> _server_list;
            Network _network;
            network::PacketsRegistry _packets_registry;
            network::NetworkHandler<EPacketServer> _network_handler;
            network::NetworkClient *_server;
            bool _connected;

    };

} // client

#endif //R_TYPE_CLIENT_CLIENT_HPP
