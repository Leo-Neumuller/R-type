/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** NetworkHandler.hpp
*/

#ifndef R_TYPE_SERVER_NETWORKHANDLER_HPP
#define R_TYPE_SERVER_NETWORKHANDLER_HPP

#include <iostream>
#include <array>
#include "IdGenerator.hpp"
#include "Client.hpp"
#include "asio.hpp"
#include <mutex>
#include <stack>

namespace Server{

    class NetworkHandler {
        public:
            NetworkHandler(std::map<int, Client> &_clients);
            ~NetworkHandler();

            void handleReceive(std::array<char, 1024> &data, std::size_t &bytes_transferred,
                               asio::ip::udp::endpoint &endpoint);
        protected:

        private:
            IdGenerator _id_generator;
            std::map<int, Client> &_clients;
            std::mutex _network_mutex;
            std::stack<std::pair<int, std::vector<char>>> _packet_stack;

    };

}
#endif //R_TYPE_SERVER_NETWORKHANDLER_HPP
