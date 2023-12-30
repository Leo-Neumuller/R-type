/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** R-Type
*/

#include "./playerSprite.hpp"

PlayerSprite::PlayerSprite(sf::Texture texture, sf::Sprite tmp, sf::Vector2f pos) : _texture(texture), _sprite(tmp), _currentFrame(2), _animationTimer(0.0f), _animationInterval(0.25f), _changingSprite(1), _actualPos(pos)
{
    for (int i = 0; i < 5; ++i) {
        _spriteRects[i] = sf::IntRect(i * 57.9, 0, 57.9, 40);
    }
    _sprite.setPosition(_actualPos);
}

PlayerSprite::~PlayerSprite()
{
}

void PlayerSprite::plAnimation()
{
    if (_animationTimer >= _animationInterval) {
        _animationTimer = 0.0f;
        if (_currentFrame == 4) {
            _changingSprite = -1;
        } else if (_currentFrame == 0) {
            _changingSprite = 1;
        }
        _currentFrame = (_currentFrame + _changingSprite);
        _sprite.setTextureRect(_spriteRects[_currentFrame]);
    }
}

void PlayerSprite::setPosition(sf::Vector2f newPos)
{
    _sprite.setPosition(newPos);
    _actualPos = newPos;
}

void PlayerSprite::AddToAnimationTimer(float nb) {
    _animationTimer += nb;
}

sf::Sprite PlayerSprite::getSprite()
{
    return (_sprite);
}

sf::Texture PlayerSprite::getTexture()
{
    return (_texture);
}

sf::IntRect PlayerSprite::getRect()
{
    return (_spriteRects[5]);
}