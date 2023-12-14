/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Server.hpp
*/

#ifndef R_TYPE_SERVER_SERVER_HPP
#define R_TYPE_SERVER_SERVER_HPP

#include <iostream>
#include "network/Network.hpp"
#include "network/NetworkHandler.hpp"
#include "network/NetworkClient.hpp"

namespace server {

    class Server {
        public:
            Server();
            ~Server();

            void runNetwork(int port);
            void runServer();
            network::PacketsRegistry &getPacketsRegistry();
            network::NetworkHandler<EPacketClient> &getNetworkHandler();
        protected:

        private:
            void setup();

            template<typename... Args, typename Func>
            void registerPacketClient(Func func, EPacketClient packet) {
                _packets_registry.registerPacketClient<Args...>([this, func](int id, Args... args) {func(this, _clients, id, args...);}, packet);
            }

            template<typename... Args>
            void registerPacketServer(EPacketServer packet) {
                _packets_registry.registerPacketServer<Args...>([](int id, Args... args) {}, packet);
            }

            std::map<int, network::NetworkClient> _clients;
            Network _network;
            network::PacketsRegistry _packets_registry;
            network::NetworkHandler<EPacketClient> _network_handler;


    };

} // Server

#endif //R_TYPE_SERVER_SERVER_HPP
