/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Render.cpp
*/

#include "Render.hpp"
#include "Entity.hpp"

namespace client {

    Render::Render(Registry &ecs) : _ecs(ecs), _window(), _clock()
    {
    }

    Render::~Render()
    {
    }

    void Render::startRender()
    {
        Entity render_entity(_ecs.spawnEntity());

        _window.create(sf::VideoMode(800, 600), "R-Type");

        _ecs.addComponent<components::Window>(render_entity, &_window);
        _ecs.addComponent<components::Event>(render_entity, sf::Event());
        _ecs.addComponent<components::EventQueues>(render_entity, {std::queue<sf::Event>(), std::queue<sf::Event>()});
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

} // client