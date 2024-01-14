/*
** EPITECH PROJECT, 2024
** r-type_server
** File description:
** ServerComponents.hpp
*/

#ifndef R_TYPE_SERVER_SERVERCOMPONENTS_HPP
#define R_TYPE_SERVER_SERVERCOMPONENTS_HPP

#include <iostream>
#include "network/NetworkHandler.hpp"

namespace components {

    /**
     * NetworkHandler
     * Component of the network handler
     * @networkHandler: pointer to the network handler
     */
    typedef network::NetworkHandler<EPacketClient> *ServerNetworkHandler;


} // ecs

#endif //R_TYPE_SERVER_SERVERCOMPONENTS_HPP
