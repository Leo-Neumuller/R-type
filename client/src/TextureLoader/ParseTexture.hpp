/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#ifndef R_TYPE_PARSETEXTURE_HPP
    #define R_TYPE_PARSETEXTURE_HPP

#include <iostream>
#include "SFML/Graphics.hpp"
#include <fstream>
#include <map>
#include <string>
#include <sstream>

class TextureLoader {
private:
    std::map<std::string, sf::Texture> textures;

    std::string extractInfo(const std::string& line) {
        std::istringstream iss(line);
        std::string key, value;
        std::getline(iss, key, ':');
        std::getline(iss, value);
        return value.empty() ? value : value.substr(1);
    }

public:

    const std::map<std::string, sf::Texture>& getAllTextures() const {
        std::cout << textures.size() << std::endl;
        return textures;
    }
    void loadTextures(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line, textureId, textureSource;
        bool insideTextureBlock = false;

        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier " + filePath);
        }

        while (std::getline(file, line)) {
            if (line == "Texture") {
                insideTextureBlock = true;
                textureId.clear();
                textureSource.clear();
            } else if (line == "Texture-end" && insideTextureBlock) {
                if (textureId.empty() || textureSource.empty()) {
                    throw std::runtime_error("Bloc Texture incomplet ou mal formé");
                }

                sf::Texture texture;
                if (!texture.loadFromFile(textureSource)) {
                    throw std::runtime_error("Erreur de chargement de la texture : " + textureSource);
                }
                textures[textureId] = texture;
                insideTextureBlock = false;
            } else if (insideTextureBlock) {
                if (line.find("id:") == 0) {
                    textureId = line.substr(line.find(":") + 2);
                } else if (line.find("source:") == 0) {
                    textureSource = line.substr(line.find(":") + 2);
                } else {
                    // Si la ligne ne correspond à aucun des champs attendus
                    throw std::runtime_error("Bloc Texture mal formé : " + line);
                }
            } else if (!line.empty()) {
                // Si la ligne n'est pas vide et qu'on n'est pas dans un bloc Texture
                throw std::runtime_error("Bloc Texture mal formé : " + line);
            }
        }
    }


    sf::Texture& getTexture(const std::string& id) {
        return textures.at(id);
    }
};

#endif //R_TYPE_PARSETEXTURE_HPP
