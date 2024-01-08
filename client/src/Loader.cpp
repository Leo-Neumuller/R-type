/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** main.cpp
*/

#include "Loader.hpp"
#include <filesystem>

Loader::Loader()
{
    try {
        loadTextures("./client/assets/loadtextures.conf");
        std::cout << "Textures loaded." << std::endl;

        loadFonts("./client/assets/loadfonts.conf");
        std::cout << "Fonts loaded." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

Loader::~Loader()
{
}

void Loader::loadTextures(const std::string& filePath)
{
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
            _textures[textureId] = texture;
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

const std::map<std::string, sf::Texture>& Loader::getAllTextures() const
{
    std::cout << _textures.size() << std::endl;
    return _textures;
}

sf::Texture& Loader::getTexture(const std::string& id)
{
    return _textures.at(id);
}




void Loader::loadFonts(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line, fontId, fontSource;
    bool insideFontBlock = false;

    if (!file.is_open()) {
        throw std::runtime_error("Fonts : Impossible d'ouvrir le fichier " + filePath);
    }
    while (std::getline(file, line)) {
        if (line == "Font") {
            insideFontBlock = true;
            fontId.clear();
            fontSource.clear();
        } else if (line == "Font-end" && insideFontBlock) {
            if (fontId.empty() || fontSource.empty())
                throw std::runtime_error("Bloc Font incomplet ou mal formé");
            sf::Font font;
            if (!font.loadFromFile(fontSource))
                throw std::runtime_error("Erreur de chargement de la font : " + fontSource);
            _fonts[fontId] = font;
            insideFontBlock = false;
        } else if (insideFontBlock) {
            if (line.find("id:") == 0)
                fontId = line.substr(line.find(":") + 2);
            else if (line.find("source:") == 0)
                fontSource = line.substr(line.find(":") + 2);
            else {
                // Si la ligne ne correspond à aucun des champs attendus
                throw std::runtime_error("Bloc Font mal formé : " + line);
            }
        } else if (!line.empty()) {
            // Si la ligne n'est pas vide et qu'on n'est pas dans un bloc Font
            throw std::runtime_error("Bloc Font mal formé : " + line);
        }
    }
}

const std::map<std::string, sf::Font>& Loader::getAllFonts() const
{
    return _fonts;
}

sf::Font& Loader::getFont(const std::string& id) {
    return _fonts.at(id);
}