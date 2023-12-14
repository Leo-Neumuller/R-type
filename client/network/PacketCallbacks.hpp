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

namespace client {

    class PacketCallbacks {
        public:
            PacketCallbacks() = delete;
            ~PacketCallbacks() = delete;

            static void helloCallback(Client *client, network::NetworkClient &server, int &fromId, bool &data);
            static void debugCallback(Client *client, network::NetworkClient &server, int &fromId, std::string &data);
        protected:

        private:

    };

} // client

#endif //R_TYPE_CLIENT_PACKETCALLBACKS_HPP
