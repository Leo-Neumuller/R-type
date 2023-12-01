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
#include "Client.hpp"

namespace Server {

    class Server {
        public:
            Server();
            ~Server();

            void run(int port);
        protected:

        private:
            std::map<int, Client> _clients;
            NetworkHandler _network_handler;
            Network _network;


    };

} // Server

#endif //R_TYPE_SERVER_SERVER_HPP
