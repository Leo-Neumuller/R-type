/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include "PacketCallbacks.hpp"

#include <utility>

namespace client {

    Client::Client() : _server_list(), _network(_network_handler), _packets_registry(), _network_handler(_server_list, _packets_registry), _server(nullptr), _connected(false)
    {
    }

    Client::~Client()
    {
    }

    void Client::connectToServer(std::string address, int port)
    {
        setup();
        auto first_data = _network_handler.serializePacket<network::GenericPacket<std::any>>(EPacketClient::CLIENT_HELLO);
        _network.run(std::move(address), port, *first_data);
    }

    void Client::runClient()
    {
        while (true) {
            _network_handler.waitForPacket();
            _server = &_server_list.begin()->second;
//            try {
                _network_handler.threatPacket();
//            } catch (std::exception &e) {
//                std::cerr << "invalid packet from server" << std::endl;
//            }
        }
    }

    network::PacketsRegistry &Client::getPacketsRegistry()
    {
        return _packets_registry;
    }

    network::NetworkHandler<EPacketServer> &Client::getNetworkHandler()
    {
        return _network_handler;
    }

    void Client::setup()
    {
        registerPacketClient(EPacketClient::CLIENT_HELLO);
        registerPacketClient<std::string>(EPacketClient::DEBUG_PACKET_CLIENT);

        registerPacketServer<bool>(PacketCallbacks::helloCallback, EPacketServer::SERVER_HELLO);
        registerPacketServer<std::string>(PacketCallbacks::debugCallback, EPacketServer::DEBUG_PACKET_SERVER);
    }

    bool Client::isConnected() const
    {
        return _connected;
    }

    void Client::setConnected(bool connected)
    {
        _connected = connected;
    }


} // client