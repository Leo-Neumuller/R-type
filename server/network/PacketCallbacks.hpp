/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** PacketCallbacks.hpp
*/

#ifndef R_TYPE_SERVER_PACKETCALLBACKS_HPP
#define R_TYPE_SERVER_PACKETCALLBACKS_HPP

#include <iostream>
#include "Server.hpp"
#include "Components.hpp"

namespace server {

    class PacketCallbacks {
        public:
            PacketCallbacks() = delete;
            ~PacketCallbacks() = delete;

            static void helloCallback(Server *server, std::map<int, network::NetworkClient> &_clients, int &fromId);
            static void debugCallback(Server *server, std::map<int, network::NetworkClient> &_clients, int &fromId, std::string data);
            static void sendPosVelCallback(Server *server, std::map<int, network::NetworkClient> &_clients, int &fromId, components::Position pos, components::Velocity vel);
        protected:

        private:

    };

} // Server

#endif //R_TYPE_SERVER_PACKETCALLBACKS_HPP
