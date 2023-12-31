/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#ifndef R_TYPE_PLAYERSPRITE_HPP
    #define R_TYPE_PLAYERSPRITE_HPP

#include <iostream>
#include "SFML/Graphics.hpp"
#include <fstream>
#include <map>
#include <string>

class PlayerSprite {
public:
    PlayerSprite(sf::Texture texture, sf::Sprite tmp, sf::Vector2f pos);
    ~PlayerSprite();


    void plAnimation(); // change le rect de la sprite
    void setPosition(sf::Vector2f newPos); // change la position selon un Vecteur
    void AddToAnimationTimer(float nb); // permet d'ajouter un int au AnimationTimer


    int _currentFrame;

    // get
    sf::Sprite getSprite();
    sf::Texture getTexture();
    sf::IntRect getRect();

private:
    // Paramètre du sprite
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _actualPos;

    // Pour animer le sprite
    sf::IntRect _spriteRects[5];
    float _animationTimer;
    float _animationInterval;
    int _changingSprite;
};

#endif //R_TYPE_PLAYERSPRITE_HPP
