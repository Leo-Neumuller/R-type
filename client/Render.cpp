/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Render.cpp
*/

#include "Render.hpp"

namespace client {

    Render::Render(Registry &ecs) : _ecs(ecs), _window(), _clock()
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
                draw[i]->setSize(sf::Vector2f(size[i]->width, size[i]->height));
                _window.draw(*draw[i]);
            }
        }

    }
} // client