/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Render.cpp
*/

#include "Render.hpp"

namespace client {

    Render::Render(Registry &ecs) : _ecs(ecs), _window()
    {
    }

    Render::~Render()
    {
    }

    void Render::startRender()
    {
        _window.create(sf::VideoMode(800, 600), "R-Type");

        _ecs.addSystem<components::Position, components::sDrawable , components::Size>([this](Registry &ecs, SparseArray<components::Position> &pos, SparseArray<components::sDrawable> &draw, SparseArray<components::Size> &size) {
            drawSystem(ecs, pos, draw, size);
        });

        Entity test(_ecs.spawnEntity());
        _ecs.addComponent(test, components::Size{100, 100});
        _ecs.addComponent(test, components::Position{100, 100});
        _ecs.addComponent(test, components::Velocity{1, 0});

        sf::Texture text;
        text.loadFromFile("../client/assets/Sprites/player1.png");
        _ecs.addComponent(test, components::sDrawable(text));
    }

    void Render::render()
    {
        _window.display();
        _window.clear();
    }

    bool Render::isOpen()
    {
        return _window.isOpen();
    }

    void
    Render::drawSystem(Registry &ecs, SparseArray<components::Position> &pos, SparseArray<components::sDrawable> &draw,
                       SparseArray<components::Size> &size)
    {
        for (int i = 0; i < pos.size() && i < draw.size() && i < size.size(); i++) {
            if (pos.has_index(i) && draw.has_index(i) && size.has_index(i)) {
                draw[i]->setPosition(pos[i]->x, pos[i]->y);
                //draw[i]->setSize(sf::Vector2f(size[i]->width, size[i]->height));
                _window.draw(*draw[i]);
            }
        }

    }
} // client