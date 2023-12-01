/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Network.hpp
*/

#ifndef R_TYPE_SERVER_NETWORK_HPP
#define R_TYPE_SERVER_NETWORK_HPP

#include <iostream>
#include "asio.hpp"
#include "NetworkHandler.hpp"

namespace Server {

    class Network {
        public:
            Network(NetworkHandler &network_handler);
            ~Network();

            void run(int port);

        protected:

        private:
            void _begin_receive();
            void _handle_receive(const asio::error_code &error, std::size_t bytes_transferred);

            asio::io_service _io_service;
            std::unique_ptr<asio::ip::udp::socket> _udp_socket;
            asio::ip::udp::endpoint _udp_client_endpoint;
            std::array<char, 1024> _data;
            NetworkHandler &_network_handler;

    };

} // Server

#endif //R_TYPE_SERVER_NETWORK_HPP
