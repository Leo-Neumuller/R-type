/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include "asio.hpp"

Client::Client(int id, asio::ip::udp::endpoint &endpoint) : _id(id), _endpoint(endpoint)
{

}

Client::~Client()
{
}

