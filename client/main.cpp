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
#include <stdlib.h>
#include "src/Menu.hpp"

int main() {
    if (Menu() == 1)
        return 1;
    else {
        client::Client client;
        client.connectToServer(Ip, Port);
        client.runClient();
    }
    return 0;
}
