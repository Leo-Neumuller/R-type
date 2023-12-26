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

int main()
{


    client::Client client;
    client.connectToServer("127.0.0.1", 4242);
    client.runClient();
    return 0;
}

/*sf::RenderWindow window(sf::VideoMode(1920, 1080), "Texture Display");
    TextureLoader loader;

    try {
        loader.loadTextures("../assets/loadtextures.conf");
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    const auto& loadedTextures = loader.getAllTextures();  // Utilise la nouvelle méthode
    std::vector<sf::Sprite> sprites;
    float x = 0.0f, y = 0.0f;
    const float padding = 10.0f;  // Espace entre les sprites

    for (const auto& pair : loadedTextures) {
        std::cout << "Texture " << pair.first << " chargée" << std::endl;
        sf::Sprite sprite;
        sprite.setTexture(pair.second);
        sprite.setPosition(x, y);
        sprites.push_back(sprite);

        // Mise à jour de la position x pour le prochain sprite
        x += sprite.getGlobalBounds().width + padding;
        if (x + sprite.getGlobalBounds().width > window.getSize().x) {
            x = 0;
            y += sprite.getGlobalBounds().height + padding;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // Dessiner chaque sprite
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
        window.display();
    }*/