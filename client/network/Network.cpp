/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Network.cpp
*/

#include "Network.hpp"

namespace client {

    Network::Network(network::NetworkHandler<EPacketServer> &networkHandler)
            : _io_service(), _udp_socket(), _udp_client_endpoint(),
              _data(), _network_handler(networkHandler)
    {
    }

    Network::~Network()
    {
    }

    void Network::_begin_receive()
    {
        _data.fill(0);
        _udp_socket->async_receive_from(asio::buffer(_data, 1024), _udp_client_endpoint, std::bind(&Network::_handle_receive, this, std::placeholders::_1, std::placeholders::_2));
    }

    void Network::_handle_receive(const asio::error_code &error, std::size_t bytes_transferred)
    {
        if (!error || error == asio::error::message_size) {
            _network_handler.handleReceive(_data, bytes_transferred, _udp_client_endpoint, *_udp_socket);
            _begin_receive();
        }
    }

    void Network::run(std::string address, int port, std::vector<char> &first_data)
    {
        asio::ip::address ip = asio::ip::make_address(address);
        _udp_client_endpoint = asio::ip::udp::endpoint(ip, port);

        _udp_socket = std::make_shared<asio::ip::udp::socket>(_io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
        _udp_socket->connect(_udp_client_endpoint);
        _thread = std::thread([this, first_data](){
            _udp_socket->async_send(asio::buffer(first_data, 1024), std::bind(&Network::_fake_handle, this, std::placeholders::_1, std::placeholders::_2));
            _begin_receive();
            _io_service.run();
        });

    }

    const std::shared_ptr<asio::ip::udp::socket> &Network::getUdpSocket() const
    {
        return _udp_socket;
    }

    const asio::ip::udp::endpoint &Network::getUdpClientEndpoint() const
    {
        return _udp_client_endpoint;
    }

    void Network::_fake_handle(const asio::error_code &error, std::size_t bytes_transferred)
    {

    }

    void Network::stop()
    {
        _io_service.stop();
        _thread.join();
    }

} // Client