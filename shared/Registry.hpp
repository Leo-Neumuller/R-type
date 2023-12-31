/*
** EPITECH PROJECT, 2023
** bs_rtype
** File description:
** Registry.hpp
*/

#ifndef BS_RTYPE_REGISTRY_HPP
#define BS_RTYPE_REGISTRY_HPP

#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "SparseArray.hpp"
#include <any>
#include <map>
#include <algorithm>
#include <functional>
class Registry {
    public:
        using entity_t = size_t;

        template <class Component>
        SparseArray <Component> &registerComponent()
        {
            std::type_index type = typeid(Component);
            if (_components_arrays.find(type) == _components_arrays.end()) {
                _components_arrays[type] = SparseArray<Component>();
            }
            return std::any_cast<SparseArray<Component> &>(_components_arrays[type]);
        }

        template <class Component>
        SparseArray <Component> &getComponent()
        {
            std::type_index type = typeid(Component);
            if (_components_arrays.find(type) == _components_arrays.end()) {
                throw std::runtime_error("Component not found");
            }
            return std::any_cast<SparseArray<Component> &>(_components_arrays[type]);
        }

        entity_t spawnEntity()
        {
            _entities.push_back(_entities.size());
            return _entities.size() - 1;
        }

        entity_t getEntityFromIndex(size_t index)
        {
            return _entities[index];
        }

        std::vector<entity_t> getEntities() const
        {
            return _entities;
        }

        void killEntity(entity_t const &entity)
        {
            _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
            if (_free_entities.find(entity) != _free_entities.end()) {
                for (auto &func : _free_entities[entity]) {
                    func();
                }
                _free_entities.erase(entity);
            }
        }

        template <typename Component>
        typename SparseArray<Component>::reference_type addComponent(entity_t const &entity, Component &&component)
        {
            auto &array = getComponent<Component>();

            if (std::find(_entities.begin(), _entities.end(), entity) == _entities.end())
                throw std::runtime_error("Entity does not exist");

            if (_free_entities.find(entity) == _free_entities.end())
                _free_entities.emplace(entity, std::vector<std::function<void()>>());
            _free_entities[entity].push_back([entity, &array]() {
                array.erase(entity);
            });
            return array.insert_at(entity, std::forward<Component>(component));;
        }

        template<typename Component, typename... Params>
        typename SparseArray<Component>::reference_type emplaceComponent(entity_t const &entity, Params &&... params)
        {
            auto &array = getComponent<Component>();

            if (std::find(_entities.begin(), _entities.end(), entity) == _entities.end())
                throw std::runtime_error("Entity does not exist");
            array.emplace_at(entity, std::forward<Params>(params)...);

            if (_free_entities.find(entity) == _free_entities.end())
                _free_entities.emplace(entity, std::vector<std::function<void()>>());
            _free_entities[entity].push_back([entity, &array]() {
                array.erase(entity);
            });
            return array[entity];
        }

        template <class... Components, typename Function>
        void addSystem(Function &&function) {
            std::function<void(Registry &)> system = [function, this](Registry &registry) {
                function(registry, getComponent<Components>()...);
            };
            registerComponent<std::function<void(Registry &)>>().push_back(system);
        }

        template <class... Components, typename Function>
        void addSystem(Function &&function, float &deltaTime) {
            std::function<void(Registry &)> system = [function, this, &deltaTime](Registry &registry) {
                function(registry, deltaTime, getComponent<Components>()...);
            };
            registerComponent<std::function<void(Registry &)>>().push_back(system);
        }


        void runSystems()
        {
            auto &systems = getComponent<std::function<void(Registry &)>>();

            for (auto & system : systems) {
                system.value()(*this);
            }
        }

        template<typename Component>
        void removeComponent(entity_t const &entity)
        {
            auto &array = getComponent<Component>();
            array.erase(entity);
        }

        template<typename Component>
        bool hasComponent(entity_t &entity)
        {
            auto &array = getComponent<Component>();

            return array.has_index(entity);
        }


    protected:

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::map<entity_t , std::vector<std::function<void()>>> _free_entities;
        std::vector<entity_t> _entities;

};


#endif //BS_RTYPE_REGISTRY_HPP
