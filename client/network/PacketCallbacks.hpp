/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** PacketCallback.hpp
*/

#ifndef R_TYPE_CLIENT_PACKETCALLBACKS_HPP
#define R_TYPE_CLIENT_PACKETCALLBACKS_HPP

#include <iostream>
#include "Client.hpp"
#include "Components.hpp"

namespace client {

    class PacketCallbacks {
        public:
            PacketCallbacks() = delete;
            ~PacketCallbacks() = delete;

            static void helloCallback(Client *client, network::NetworkClient &server, int &fromId, bool &data);
            static void debugCallback(Client *client, network::NetworkClient &server, int &fromId, std::string &data);
            static void newClientCallback(Client *client, network::NetworkClient &server, int &fromId, int &id, components::Position &pos);
            static void clientBaseInfoCallback(Client *client, network::NetworkClient &server, int &fromId, int &id, components::Position &pos);
            static void forceSetPosCallback(Client *client, network::NetworkClient &server, int &fromId, int &id,
                                            components::Position &pos, components::Velocity &vel);
            static void sendPosVelCallback(Client *client, network::NetworkClient &server, int &fromId, int &id,
                                           components::Position &pos, components::Velocity &vel);
        protected:

        private:

    };

} // client

#endif //R_TYPE_CLIENT_PACKETCALLBACKS_HPP
