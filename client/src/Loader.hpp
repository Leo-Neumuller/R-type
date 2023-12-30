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

class Loader {
private:
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::Font> _fonts;


    std::string extractInfo(const std::string& line) {
        std::istringstream iss(line);
        std::string key, value;
        std::getline(iss, key, ':');
        std::getline(iss, value);
        return value.empty() ? value : value.substr(1);
    }

public:

    Loader();
    ~Loader();


    void loadTextures(const std::string& filePath);
    void loadFonts(const std::string& filePath);

    const std::map<std::string, sf::Texture>& getAllTextures() const;
    sf::Texture& getTexture(const std::string& id);

    const std::map<std::string, sf::Font>& getAllFonts() const;
    sf::Font& getFont(const std::string& id);



};

#endif //R_TYPE_PARSETEXTURE_HPP
