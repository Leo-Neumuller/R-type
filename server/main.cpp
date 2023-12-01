/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** main.cpp
*/
#include <iostream>
#include "Server.hpp"

int main(int ac, char **av)
{
    Server::Server server;

    server.run(4242);
    return 0;
}