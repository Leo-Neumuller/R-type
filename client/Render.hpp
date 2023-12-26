/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Render.hpp
*/

#ifndef R_TYPE_CLIENT_RENDER_HPP
#define R_TYPE_CLIENT_RENDER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Registry.hpp"
#include <memory>
#include "Components.hpp"
#include "ClientComponents.hpp"
#include "Entity.hpp"
#include "src/Loader.hpp"

namespace client {

    class Render {
        public:
            Render(Registry &ecs);
            ~Render();

            void startRender();
            float render();
            bool isOpen();
            void drawSystem(Registry &ecs, SparseArray<components::Position> &pos, SparseArray<components::Drawable> &draw, SparseArray<components::Size> &size);
        protected:

        private:

            sf::RenderWindow _window;
            Registry &_ecs;
            sf::Clock _clock;
            Loader _texturesFonts;



    };

} // client

#endif //R_TYPE_CLIENT_RENDER_HPP
