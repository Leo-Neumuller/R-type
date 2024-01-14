/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Network.cpp
*/

#include "Network.hpp"

namespace client {

    /**
     * Constructor
     * @param networkHandler
     */
    Network::Network(network::NetworkHandler<EPacketServer> &networkHandler)
            : _io_service(), _udp_socket(), _udp_client_endpoint(),
              _data(), _network_handler(networkHandler)
    {
    }

    /**
     * Destructor
     */
    Network::~Network()
    {
    }

    /**
     * _begin_receive
     * Start the receive of the udp socket
     */
    void Network::_begin_receive()
    {
        _data.fill(0);
        _udp_socket->async_receive_from(asio::buffer(_data, 1024), _udp_client_endpoint, std::bind(&Network::_handle_receive, this, std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * _handle_receive
     * Handle the receive of the udp socket
     */
    void Network::_handle_receive(const asio::error_code &error, std::size_t bytes_transferred)
    {
        if (!error || error == asio::error::message_size) {
            _network_handler.handleReceive(_data, bytes_transferred, _udp_client_endpoint, *_udp_socket);
            _begin_receive();
        }
    }

    /**
     * run
     * Run the network
     * @param address
     * @param port
     * @param first_data
     */
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

    /**
     * getUdpSocket
     * Get the udp socket
     * @return udp socket
     */
    const std::shared_ptr<asio::ip::udp::socket> &Network::getUdpSocket() const
    {
        return _udp_socket;
    }

    /**
     * getUdpClientEndpoint
     * Get the udp client endpoint
     * @return udp client endpoint
     */
    const asio::ip::udp::endpoint &Network::getUdpClientEndpoint() const
    {
        return _udp_client_endpoint;
    }

    /**
     * _fake_handle
     * Fake handle for the async_send
     * @param error
     * @param bytes_transferred
     */
    void Network::_fake_handle(const asio::error_code &error, std::size_t bytes_transferred)
    {

    }

    /**
     * stop
     * Stop the network
     */
    void Network::stop()
    {
        _io_service.stop();
        _thread.join();
    }

} // Client