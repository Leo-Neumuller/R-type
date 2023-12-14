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
    server::Server server;

    server.runNetwork(4242);
    server.runServer();
    return 0;
}