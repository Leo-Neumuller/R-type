/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** font parsing
*/

#ifndef R_TYPE_PARSEFONT_HPP
#define R_TYPE_PARSEFONT_HPP

#include <iostream>
#include "SFML/Graphics.hpp"
#include <fstream>
#include <map>
#include <string>
#include <sstream>

class FontLoader {
private:
    std::map<std::string, sf::Font> _fonts;

    std::string extractInfo(const std::string& line) {
        std::istringstream iss(line);
        std::string key, value;
        std::getline(iss, key, ':');
        std::getline(iss, value);
        return value.empty() ? value : value.substr(1);
    }

public:

    const std::map<std::string, sf::Font>& getAllFonts() const {
        std::cout << _fonts.size() << std::endl;
        return _fonts;
    }

    void loadFonts(const std::string& filePath) {
        std::cout << filePath << std::endl;

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
            }
            else if (line == "Font-end" && insideFontBlock){
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
                std::cout << fontSource << std::endl;
            } else if (!line.empty()) {
                // Si la ligne n'est pas vide et qu'on n'est pas dans un bloc Font
                throw std::runtime_error("Bloc Font mal formé : " + line);
            }
        }
    }

    sf::Font& getFont(const std::string& id) {
        return _fonts.at(id);
    }
};

#endif //R_TYPE_PARSEFONT_HPP
