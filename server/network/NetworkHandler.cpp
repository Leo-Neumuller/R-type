/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** NetworkHandler.cpp
*/

#include "NetworkHandler.hpp"

namespace Server {

    NetworkHandler::NetworkHandler(std::map<int, Client> &_clients) : _id_generator(), _clients(_clients), _network_mutex()
    {
    }

    NetworkHandler::~NetworkHandler()
    {
    }

    void NetworkHandler::handleReceive(std::array<char, 1024> &data, std::size_t &bytes_transferred,
                                       asio::ip::udp::endpoint &endpoint)
    {
        std::lock_guard<std::mutex> lock(_network_mutex);
        int id = _id_generator.getId(endpoint.address().to_string() + std::to_string(endpoint.port()));

        if (_clients.find(id) == _clients.end()) {
            _clients.emplace(id, Client(id, endpoint));
        }
        if (bytes_transferred < 6) {
            std::cout << "Malformed packet" << std::endl;
            return;
        }
        std::vector<char> packet(data.begin(), data.begin() + bytes_transferred);

        _packet_stack.emplace(id, packet);
    }
}