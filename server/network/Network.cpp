/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Network.cpp
*/

#include "Network.hpp"

namespace Server {

    Network::Network(NetworkHandler &network_handler)
            : _io_service(), _udp_socket(), _udp_client_endpoint(),
              _data(), _network_handler(network_handler)
    {

    }

    Network::~Network()
    {
    }

    void Network::_begin_receive()
    {
        _udp_socket->async_receive_from(asio::buffer(_data, 1024), _udp_client_endpoint, std::bind(&Network::_handle_receive, this, std::placeholders::_1, std::placeholders::_2));
    }

    void Network::_handle_receive(const asio::error_code &error, std::size_t bytes_transferred)
    {
        if (!error || error == asio::error::message_size) {
            std::cout << "Received: " << _data.data() << std::endl;
            std::cout << bytes_transferred << std::endl;
            _network_handler.handleReceive(_data, bytes_transferred, _udp_client_endpoint);
            _begin_receive();
        }
    }

    void Network::run(int port)
    {
        _udp_socket = std::make_unique<asio::ip::udp::socket>(_io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), port));
        _begin_receive();
        _io_service.run();
    }

} // Server