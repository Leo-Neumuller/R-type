/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** main.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Loader.hpp"
#include "Client.hpp"

int main() {
    client::Client client;

    client.connectToServer("127.0.0.1", 4242);
    client.runClient();
    return 0;
}
