/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Server.cpp
*/

#include "Server.hpp"

namespace Server {

    Server::Server() : _clients(), _network_handler(_clients), _network(_network_handler)
    {
    }

    Server::~Server()
    {
    }

    void Server::run(int port)
    {
        _network.run(port);
    }

} // Server