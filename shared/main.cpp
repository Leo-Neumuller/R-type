/*
** EPITECH PROJECT, 2023
** bs-rtype
** File description:
** main.cpp
*/
#include "Registry.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

struct position {
    float x;
    float y;
};

struct velocity {
    float vx;
    float vy;
};

struct keyboard {
    bool up;
    bool down;
    bool left;
    bool right;
    bool rright;
    bool rleft;
};

void logging_system(Registry& r, SparseArray<position> &positions, SparseArray<velocity> &velocities) {
    for ( size_t i = 0; i < positions.size() && i < velocities.size(); ++ i ) {
        auto const & pos = positions[i];
        auto const & vel = velocities[i];

        std :: cerr << i << ": Position = { " << pos->x << ", " << pos->y << " } , Velocity = { " << vel->vx << ", " << vel->vy << " }" << std::endl;
    }
}

void movement_system(Registry& r, SparseArray<position> &pos, SparseArray<velocity> &vel) {
    for (int i = 0; i < pos.size() && i < vel.size(); i++) {
        if (pos.has_index(i) && vel.has_index(i)) {
            pos[i]->x += vel[i]->vx;
            pos[i]->y += vel[i]->vy;
        }
    }
}

void event_system(Registry &r, SparseArray<sf::Event*> &events) {
    auto &keyEvents = r.getComponent<keyboard>();
    for (int i = 0; i < events.size(); i++) {
        if (events.has_index(i)) {
            if (events[i].value()->type == sf::Event::KeyPressed) {
                for (int j = 0; j < keyEvents.size(); ++j) {
                    if (keyEvents.has_index(j)) {
                        switch (events[i].value()->key.code) {
                            case sf::Keyboard::Left:
                                keyEvents[j]->left = true;
                                break;
                            case sf::Keyboard::Right:
                                keyEvents[j]->right = true;
                                break;
                            case sf::Keyboard::Up:
                                keyEvents[j]->up = true;
                                break;
                            case sf::Keyboard::Down:
                                keyEvents[j]->down = true;
                                break;
                            default:
                                break;

                        }
                    }
                }
            } else if (events[i].value()->type == sf::Event::KeyReleased) {
                for (int j = 0; j < keyEvents.size(); ++j) {
                    if (keyEvents.has_index(j)) {
                        switch (events[i].value()->key.code) {
                            case sf::Keyboard::Left:
                                keyEvents[j]->left = false;
                                break;
                            case sf::Keyboard::Right:
                                keyEvents[j]->right = false;
                                break;
                            case sf::Keyboard::Up:
                                keyEvents[j]->up = false;
                                break;
                            case sf::Keyboard::Down:
                                keyEvents[j]->down = false;
                                break;
                            default:
                                break;

                        }
                    }
                }
            }
        }
    }
}

void keyboard_system(Registry &registry, SparseArray<keyboard> &event, SparseArray<velocity> &vel)
{
    for (int i = 0; i < event.size() && i < vel.size(); i++) {
        if (event.has_index(i) && vel.has_index(i)) {
            if (event[i]->up)
                vel[i]->vy -= 0.01;
            else if (event[i]->down)
                vel[i]->vy += 0.01;
            else {
                vel[i]->vx *= 0.999;
                vel[i]->vy *= 0.999;
            }

            if (event[i]->left)
                vel[i]->vx -= 0.01;
            else if (event[i]->right)
                vel[i]->vx += 0.01;
            else {
                vel[i]->vx *= 0.999;
                vel[i]->vy *= 0.999;
            }

        }
    }
}

void draw_system(Registry &registry, SparseArray<sf::Shape *> &drawables, SparseArray<position> &positions)
{
    auto &windows = registry.getComponent<sf::RenderWindow *>();
    sf::RenderWindow *window = nullptr;

    for (int i = 0; i < windows.size(); ++i) {
        if (windows.has_index(i)) {
            window = *windows[i];
        }
    }
    if (window == nullptr)
        return;
    for (int i = 0; i < drawables.size() && i < positions.size(); i++) {
        if (drawables.has_index(i) && positions.has_index(i)) {
            drawables[i].value()->setFillColor(sf::Color::Green);
            drawables[i].value()->setPosition(positions[i]->x, positions[i]->y);
            window->draw(*(*drawables[i]));
        }
    }
}

int main()
{
    Registry registry;
    Entity entity(registry.spawnEntity());
    Entity entity2(registry.spawnEntity());
    Entity entity3(registry.spawnEntity());
    Entity entity4(registry.spawnEntity());
    Entity entity5(registry.spawnEntity());
    Entity entity6(registry.spawnEntity());
    Entity eventEntity(registry.spawnEntity());
    Entity windowEntity(registry.spawnEntity());
    sf::Event event;

    registry.registerComponent<position>();
    registry.registerComponent<velocity>();
    registry.registerComponent<sf::Event*>();
    registry.registerComponent<keyboard>();
    registry.registerComponent<sf::Shape *>();
    registry.registerComponent<sf::RenderWindow *>();

    registry.addComponent<position>(entity, {100, 50});
    registry.addComponent<position>(entity2, {100, 100});
    registry.addComponent<position>(entity3, {100, 150});
    registry.addComponent<position>(entity4, {100, 200});
    registry.addComponent<position>(entity5, {10, 300});
    registry.addComponent<position>(entity6, {190, 300});
    registry.addComponent(entity, velocity{0, 0});
    registry.addComponent(entity2, velocity{0, 0});
    registry.addComponent(entity3, velocity{0, 0});
    registry.addComponent(entity4, velocity{0, 0});
    registry.addComponent(entity5, velocity{0, 0});
    registry.addComponent(entity6, velocity{0, 0});
//    registry.addComponent(entity, keyboard{&event});
    registry.addComponent<sf::Shape *>(entity, new sf::CircleShape(100.0f));
    registry.addComponent<sf::Shape *>(entity2, new sf::CircleShape(100.0f));
    registry.addComponent<sf::Shape *>(entity3, new sf::CircleShape(100.0f));
    registry.addComponent<sf::Shape *>(entity4, new sf::CircleShape(100.0f));
    registry.addComponent<sf::Shape *>(entity5, new sf::CircleShape(100.0f));
    registry.addComponent<sf::Shape *>(entity6, new sf::CircleShape(100.0f));

    registry.addComponent(eventEntity, &event);
    registry.addComponent(entity, keyboard{false, false, false, false});
    registry.addComponent(entity2, keyboard{false, false, false, false});
    registry.addComponent(entity3, keyboard{false, false, false, false});
    registry.addComponent(entity4, keyboard{false, false, false, false});
    registry.addComponent(entity5, keyboard{false, false, false, false});
    registry.addComponent(entity6, keyboard{false, false, false, false});

    registry.addSystem<position, velocity>(movement_system);
//    registry.addSystem<position, velocity>(logging_system);
    registry.addSystem<sf::Event*>(event_system);
    registry.addSystem<keyboard, velocity>(keyboard_system);
    registry.addSystem<sf::Shape *, position>(draw_system);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

    registry.addComponent(windowEntity, &window);

    while (window.isOpen())
    {

        registry.runSystems();
        auto const & positions = registry.getComponent<position>();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
        window.clear(sf::Color::Black);
    }
    return 0;
}
