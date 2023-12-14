/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Network.hpp
*/

#ifndef R_TYPE_CLIENT_NETWORK_HPP
#define R_TYPE_CLIENT_NETWORK_HPP

#include <iostream>
#include <asio.hpp>
#include "network/NetworkHandler.hpp"
#include <thread>

namespace client {

    class Network {
        public:
            Network(network::NetworkHandler<EPacketServer> &networkHandler);
            ~Network();

            void run(std::string address, int port, std::vector<char> &first_data);
            const std::shared_ptr<asio::ip::udp::socket> &getUdpSocket() const;
            const asio::ip::udp::endpoint &getUdpClientEndpoint() const;
        protected:

        private:
            void _begin_receive();
            void _handle_receive(const asio::error_code &error, std::size_t bytes_transferred);
            void _fake_handle(const asio::error_code &error, std::size_t bytes_transferred);

            asio::io_service _io_service;
            std::shared_ptr<asio::ip::udp::socket> _udp_socket;
            asio::ip::udp::endpoint _udp_client_endpoint;
            std::array<char, 1024> _data;
            network::NetworkHandler<EPacketServer> &_network_handler;
            std::thread _thread;

    };

} // Client

#endif //R_TYPE_CLIENT_NETWORK_HPP
