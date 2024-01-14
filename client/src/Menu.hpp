/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Menu.hpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Loader.hpp"
#include "Client.hpp"
#include <stdlib.h>
#include <string>

std::string Ip;
int Port;

int Menu() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "IP and Port Input");

    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("../client/assets/menu.png")) {
        std::cerr << "Error loading menu.png" << std::endl;
        return 1;
    }

    sf::Sprite menuSprite;
    menuSprite.setTexture(menuTexture);

    std::string input = "";
    sf::Text inputText, portText;
    sf::Font font;

    sf::Font RTypeFont;
    if (!RTypeFont.loadFromFile("../client/assets/Fonts/Minecraft.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }
    if (!font.loadFromFile("../client/assets/Fonts/font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }

    sf::Text titleText("R-TYPE", RTypeFont, 50);
    titleText.setFillColor(sf::Color::White);

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(270, 300);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(window.getSize().x / 2, 50);

    sf::Text explanationText;
    explanationText.setFont(font);
    explanationText.setCharacterSize(20);
    explanationText.setFillColor(sf::Color::White);
    explanationText.setString("Type the ip and port with space in between");
    explanationText.setPosition(200, 260);

    sf::RectangleShape inputBackground;
    inputBackground.setSize(sf::Vector2f(270, 50)); // Largeur et hauteur du rectangle
    inputBackground.setFillColor(sf::Color::Black);
    inputBackground.setPosition(270, 290); // Position du rectangle

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 8 && !input.empty()) {
                        input.pop_back();
                    } else if (event.text.unicode != 8) {
                        input += static_cast<char>(event.text.unicode);
                    }
                }

                std::istringstream iss(input);
                std::string ipAddress, port;
                iss >> ipAddress >> port;

                try {
                    if (!ipAddress.empty() && !port.empty() && port.length() == 4) {
                        int portNumber = std::stoi(port); 
                        Port = std::stoi(port);
                        Ip = ipAddress;
                        std::cout << "IP: " << Ip << "\nPort: " << Port << std::endl;
                        window.close();
                        return 0;
                    }
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Invalid port number: " << e.what() << std::endl;
                } catch (const std::out_of_range &e) {
                    std::cerr << "Port number out of range: " << e.what() << std::endl;
                }
            }
        }
        inputText.setString(input);
        window.clear();
        window.draw(menuSprite);
        window.draw(titleText);
        window.draw(inputBackground);
        window.draw(inputText);
        window.draw(explanationText);

        window.display();
    }
    return 1;
}