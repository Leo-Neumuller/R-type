/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Render.cpp
*/

#include "Render.hpp"

namespace client {

    Render::Render(Registry &ecs) : _ecs(ecs), _window(), _clock(), _texturesFonts()
    {
    }

    Render::~Render()
    {
    }

    void Render::startRender()
    {
        _window.create(sf::VideoMode(800, 600), "R-Type");

        _ecs.addSystem<components::Position, components::Drawable, components::Size>([this](Registry &ecs, SparseArray<components::Position> &pos, SparseArray<components::Drawable> &draw, SparseArray<components::Size> &size) {
            drawSystem(ecs, pos, draw, size);
        });
        _clock.restart();
    }

    float Render::render()
    {
        _window.display();
        _window.clear();

        return _clock.restart().asSeconds();

        Entity test(_ecs.spawnEntity());
        _ecs.addComponent(test, components::Size{100, 100});
        _ecs.addComponent(test, components::Position{100, 100});
        _ecs.addComponent(test, components::Velocity{1, 0});

        sf::Texture text;
        _ecs.addComponent(test, components::Drawable (_texturesFonts.getTexture("player1.png")));


    }

    bool Render::isOpen()
    {
        return _window.isOpen();
    }

    void
    Render::drawSystem(Registry &ecs, SparseArray<components::Position> &pos, SparseArray<components::Drawable> &draw,
                       SparseArray<components::Size> &size)
    {
        for (int i = 0; i < pos.size() && i < draw.size() && i < size.size(); i++) {
            if (pos.has_index(i) && draw.has_index(i) && size.has_index(i)) {
                draw[i]->setPosition(pos[i]->x, pos[i]->y);
                _window.draw(*draw[i]);
            }
        }

    }
} // client