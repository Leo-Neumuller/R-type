/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** ClientSystems.cpp
*/

#include "ClientSystems.hpp"

namespace ecs {


    void ClientSystems::drawSystem(Registry &ecs, SparseArray<components::Position> &pos,
                                   SparseArray<components::Drawable> &draw, SparseArray<components::Size> &size)
    {
        auto &window_comps = ecs.getComponent<components::Window>();
        components::Window window = nullptr;

        for (int i = 0; i < window_comps.size(); ++i) {
            if (window_comps.has_index(i)) {
                window = window_comps[i].value();
                break;
            }
        }
        if (!window)
            return;
        for (int i = 0; i < pos.size() && i < draw.size() && i < size.size(); i++) {
            if (pos.has_index(i) && draw.has_index(i) && size.has_index(i)) {
                draw[i]->setPosition(pos[i]->x, pos[i]->y);
                draw[i]->setSize(sf::Vector2f(size[i]->width, size[i]->height));
                window->draw(*draw[i]);
            }
        }
    }

    void ClientSystems::eventPollingSystem(Registry &ecs, SparseArray<components::Event> &event,
                                           SparseArray<components::Window> &window,
                                           SparseArray<components::KeyboardEvents> &keyboardEvents,
                                           SparseArray<components::WindowEvents> &windowEvents)
    {
        for (int i = 0; i < event.size() && i < window.size(); i++) {
            if (event.has_index(i) && window.has_index(i) && keyboardEvents.has_index(i) && windowEvents.has_index(i)) {
                while ((*window[i])->pollEvent((*event[i]))) {
                    switch ((*event[i]).type) {
                        case sf::Event::Closed:
                            windowEvents[i]->push((*event[i]));
                            break;
                        case sf::Event::KeyPressed:
                            keyboardEvents[i]->push((*event[i]));
                            break;
                        case sf::Event::KeyReleased:
                            keyboardEvents[i]->push((*event[i]));
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void ClientSystems::windowEventsSystem(Registry &ecs, SparseArray<components::Window> &window,
                                           SparseArray<components::WindowEvents> &windowEvents)
    {
        for (int i = 0; i < window.size() && i < windowEvents.size(); i++) {
            if (window.has_index(i) && windowEvents.has_index(i)) {
                while (!windowEvents[i]->empty()) {
                    if (windowEvents[i]->front().type == sf::Event::Closed) {
                        (*window[i])->close();
                    }
                    windowEvents[i]->pop();
                }
            }
        }
    }
} // client