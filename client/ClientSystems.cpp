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
                window->draw(*draw[i]);
            }
        }
    }

    void ClientSystems::eventPollingSystem(Registry &ecs, SparseArray<components::Event> &event,
                                           SparseArray<components::Window> &window,
                                           SparseArray<components::EventQueues> &event_queues)
    {
        for (int i = 0; i < event.size() && i < window.size(); i++) {
            if (event.has_index(i) && window.has_index(i) && event_queues.has_index(i)) {
                while ((*window[i])->pollEvent((*event[i]))) {
                    switch ((*event[i]).type) {
                        case sf::Event::Closed:
                            event_queues[i]->windowEvents.push(event[i].value());
                            break;
                        case sf::Event::KeyPressed:
                            event_queues[i]->keyboardEvents.push(event[i].value());
                            break;
                        case sf::Event::KeyReleased:
                            event_queues[i]->keyboardEvents.push(event[i].value());
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void ClientSystems::windowEventsSystem(Registry &ecs, SparseArray<components::Window> &window,
                                           SparseArray<components::EventQueues> &event_queues)
    {
        for (int i = 0; i < window.size() && i < event_queues.size(); i++) {
            if (window.has_index(i) && event_queues.has_index(i)) {
                while (!event_queues[i]->windowEvents.empty()) {
                    if (event_queues[i]->windowEvents.front().type == sf::Event::Closed) {
                        (*window[i])->close();
                    }
                    event_queues[i]->windowEvents.pop();
                }
            }
        }
    }

    void ClientSystems::playerMoveEvent(Registry &ecs, SparseArray<components::EventQueues> &event_queues,
                                        SparseArray<components::Velocity> &vel,
                                        SparseArray<components::EntityType> &type,
                                        SparseArray<components::Position> &pos)
    {
        std::queue<sf::Event> *events = nullptr;
        sf::Event singleEvent = sf::Event();

        for (int i = 0; i < event_queues.size(); ++i) {
            if (event_queues.has_index(i)) {
                events = &event_queues[i]->keyboardEvents;
                break;
            }
        }
        if (!events)
            return;
        if (events->empty())
            return;

        for (int i = 0; i < vel.size() && i < type.size(); i++) {
            if (vel.has_index(i) && type.has_index(i)) {
                if (type[i] != components::EntityType::CURRENT_PLAYER)
                    continue;
                while (!events->empty()) {
                    singleEvent = events->front();
                    if (singleEvent.type == sf::Event::KeyPressed) {
                        switch (singleEvent.key.code) {
                            case sf::Keyboard::Q:
                                vel[i]->vx = -100;
                                break;
                            case sf::Keyboard::D:
                                vel[i]->vx = 100;
                                break;
                            case sf::Keyboard::Z:
                                vel[i]->vy = -100;
                                break;
                            case sf::Keyboard::S:
                                vel[i]->vy = 100;
                                break;
                            case sf::Keyboard::Space:
                                if (pos.has_index(i))
                                    playerMissile(ecs, i, pos[i]->x, pos[i]->y);
                                break;
                            default:
                                break;

                        }
                    } else if (singleEvent.type == sf::Event::KeyReleased) {
                        switch (singleEvent.key.code) {
                            case sf::Keyboard::Q:
                                vel[i]->vx = 0;
                                break;
                            case sf::Keyboard::D:
                                vel[i]->vx = 0;
                                break;
                            case sf::Keyboard::Z:
                                vel[i]->vy = 0;
                                break;
                            case sf::Keyboard::S:
                                vel[i]->vy = 0;
                                break;
                            default:
                                break;

                        }
                    }
                    events->pop();
                }
            }
        }
    }



    void ClientSystems::playerMissile(Registry &ecs, int index, float x, float y)
    {
        auto loaderTmp = ecs.getComponent<Loader *>();
        Loader *loader;


        for (int i = 0; i < loaderTmp.size(); ++i) {
            if (loaderTmp.has_index(i)) {
                loader = loaderTmp[i].value();
                break;
            }
        }
        if (!loader)
            return;

        auto missile (ecs.spawnEntity());

        ecs.addComponent(missile, components::Position{x + 40, y});
        ecs.addComponent(missile, components::Velocity{200, 0});

        std::map<int, sf::IntRect> spriteRects;
        for (int i = 0; i < 6; ++i)
            spriteRects[i] = sf::IntRect(i * 30, 0, 30, 30);
        ecs.addComponent(missile, components::MissileStruct{0.0f, true});
        sf::Sprite tmp (loader->getTexture("missile"));
        tmp.setTextureRect(spriteRects[0]);

        ecs.addComponent(missile, components::Anim{6, 0, 0.1f, 0.0f, spriteRects});
        ecs.addComponent(missile, components::Drawable(tmp));
        ecs.addComponent(missile, components::Size{30, 30});
        ecs.addComponent(missile, components::EntityType{components::EntityType::BULLET});

    }




    void ClientSystems::spriteAnimation(Registry &ecs, float deltatime, SparseArray<components::Drawable> &draw, SparseArray<components::Anim> &Anim)
    {
        for (int i = 0; i < draw.size(); i++) {
            if (Anim.has_index(i) && draw.has_index(i)) {
                Anim[i]->animationTimer += deltatime;
                if (Anim[i]->animationTimer >= Anim[i]->animationInterval) {
                    Anim[i]->animationTimer = 0.0f;
                    Anim[i]->actualFrame = (Anim[i]->actualFrame + 1);
                    if (Anim[i]->actualFrame > Anim[i]->nbFrame - 1)
                        Anim[i]->actualFrame = 0;
                    draw[i]->setTextureRect(Anim[i]->spriteFrames.at(Anim[i]->actualFrame));
                }
            }
        }
    }

} // client