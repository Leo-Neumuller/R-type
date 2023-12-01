/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Client.hpp
*/

#ifndef R_TYPE_SERVER_CLIENT_HPP
#define R_TYPE_SERVER_CLIENT_HPP

#include <iostream>
#include "asio.hpp"

class Client {
    public:
        explicit Client(int id, asio::ip::udp::endpoint &endpoint);
        ~Client();

    protected:

    private:
        int _id;
        asio::ip::udp::endpoint &_endpoint;

};


#endif //R_TYPE_SERVER_CLIENT_HPP
