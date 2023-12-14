/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** main.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Client.hpp"

int main(int ac, char **av)
{
    client::Client client;

    client.connectToServer("127.0.0.1", 4242);
    client.runClient();
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test Window");
//
//    // Main loop that continues until the window is closed
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            // Check for window close event
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        // Clear the window with a black color
//        window.clear(sf::Color::Black);
//
//        // You can add your drawing code here
//
//        // Display what has been drawn to the window
//        window.display();
}
