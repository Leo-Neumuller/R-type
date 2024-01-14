/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** ClientSystems.cpp
*/

#include "ClientSystems.hpp"

namespace ecs {


    /**
     * drawSystem
     * System for drawing entities
     * @param ecs
     * @param pos
     * @param draw
     * @param size
     */
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
        if (!window->isOpen())
            return;
        for (int i = 0; i < pos.size() && i < draw.size() && i < size.size(); i++) {
            if (pos.has_index(i) && draw.has_index(i) && size.has_index(i)) {
                draw[i]->setPosition(pos[i]->x, pos[i]->y);
                window->draw(*draw[i]);
            }
            if (i == 0 && pos[i]->x <= -1920) {
                pos[i]->x = 0;
            }
        }
    }

    /**
     * eventPollingSystem
     * System for polling events
     * @param ecs
     * @param event
     * @param window
     * @param event_queues
     */
    void ClientSystems::eventPollingSystem(Registry &ecs, SparseArray<components::Event> &event,
                                           SparseArray<components::Window> &window,
                                           SparseArray<components::EventQueues> &event_queues)
    {
        for (int i = 0; i < event.size() && i < window.size(); i++) {
            if (event.has_index(i) && window.has_index(i) && event_queues.has_index(i)) {
                if (!(*window[i]))
                    continue;
                if (!(*window[i])->isOpen())
                    continue;


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

    /**
     * windowEventsSystem
     * System for window events
     * @param ecs
     * @param window
     * @param event_queues
     */
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

    /**
     * playerMoveEvent
     * System for player move events
     * @param ecs
     * @param event_queues
     * @param vel
     * @param type
     * @param pos
     */
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


    /**
     * playerMissile
     * System for player missile
     * @param ecs
     * @param index
     * @param x
     * @param y
     */
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

    /**
     * playerMoveNetwork
     * System for player move network
     * @param ecs
     * @param deltatime
     * @param vel
     * @param pos
     * @param type
     * @param network_handler
     * @param last_vel
     */
    void ClientSystems::playerMoveNetwork(Registry &ecs, float &deltatime, SparseArray<components::Velocity> &vel,
                                          SparseArray<components::Position> &pos,
                                          SparseArray<components::EntityType> &type,
                                          SparseArray<components::NetworkHandler> &network_handler,
                                          SparseArray<components::LastVelocity> &last_vel)
    {
        for (int i = 0; i < vel.size() && i < type.size() && i < pos.size() && i < network_handler.size() && i < last_vel.size(); i++) {
            if (!vel.has_index(i) || !type.has_index(i) || !network_handler.has_index(i) || !pos.has_index(i) || !last_vel.has_index(i))
                continue;
            if (type[i] != components::EntityType::CURRENT_PLAYER)
                continue;
            if (vel[i]->vx == last_vel[i]->vx && vel[i]->vy == last_vel[i]->vy)
                continue;
            network_handler[i].value()->serializeSendPacket<network::GenericPacket<std::any, components::Position, components::Velocity>>(0, EPacketClient::CLIENT_SEND_POS_VEL, pos[i].value(), vel[i].value());
            last_vel[i]->vx = vel[i]->vx;
            last_vel[i]->vy = vel[i]->vy;
        }
    }

    /**
     * spriteAnimation
     * System for sprite animation
     * @param ecs
     * @param deltatime
     * @param draw
     * @param Anim
     */
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