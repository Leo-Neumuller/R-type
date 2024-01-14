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
/**
 * Registry
 * Class of the registry for the ecs
 */
class Registry {
    public:
        using entity_t = size_t;

        /**
         * registerComponent
         * Register a component
         * @return: the component
         */
        template <class Component>
        SparseArray <Component> &registerComponent()
        {
            std::type_index type = typeid(Component);
            if (_components_arrays.find(type) == _components_arrays.end()) {
                _components_arrays[type] = SparseArray<Component>();
            }
            return std::any_cast<SparseArray<Component> &>(_components_arrays[type]);
        }

        /**
         * getComponent
         * Get a component
         * @return: the component
         */
        template <class Component>
        SparseArray <Component> &getComponent()
        {
            std::type_index type = typeid(Component);
            if (_components_arrays.find(type) == _components_arrays.end()) {
                throw std::runtime_error("Component not found");
            }
            return std::any_cast<SparseArray<Component> &>(_components_arrays[type]);
        }

        /**
         * spawnEntity
         * Spawn an entity
         * @return: the entity
         */
        entity_t spawnEntity()
        {
            _entities.push_back(_entities.size());
            return _entities.size() - 1;
        }

        /**
         * getEntityFromIndex
         * Get an entity from an index
         * @param index: the index
         * @return: the entity
         */
        entity_t getEntityFromIndex(size_t index)
        {
            return _entities[index];
        }

        /**
         * getEntities
         * Get all the entities
         * @return: the entities
         */
        std::vector<entity_t> getEntities() const
        {
            return _entities;
        }

        /**
         * killEntity
         * Kill an entity
         * @param entity: the entity
         */
        void killEntity(entity_t const &entity)
        {
            if (_free_entities.find(entity) != _free_entities.end()) {
                for (auto &func : _free_entities[entity]) {
                    func();
                }
                _free_entities.erase(entity);
            }
        }

        /**
         * addComponent
         * Add a component
         * @param entity: the entity
         * @param component: the component
         * @return: the component
         */
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

        /**
         * emplaceComponent
         * Emplace a component
         * @param entity: the entity
         * @param params: the params
         * @return: the component
         */
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

        /**
         * addSystem
         * Add a system
         * @param function: the function
         */
        template <class... Components, typename Function>
        void addSystem(Function &&function) {
            std::function<void(Registry &)> system = [function, this](Registry &registry) {
                function(registry, getComponent<Components>()...);
            };
            registerComponent<std::function<void(Registry &)>>().push_back(system);
        }

        /**
         * addSystem
         * Add a system
         * @param function: the function
         * @param deltaTime: the delta time
         */
        template <class... Components, typename Function>
        void addSystem(Function &&function, float &deltaTime) {
            std::function<void(Registry &)> system = [function, this, &deltaTime](Registry &registry) {
                function(registry, deltaTime, getComponent<Components>()...);
            };
            registerComponent<std::function<void(Registry &)>>().push_back(system);
        }


        /**
         * runSystems
         * Run the systems
         */
        void runSystems()
        {
            auto &systems = getComponent<std::function<void(Registry &)>>();

            for (auto & system : systems) {
                system.value()(*this);
            }
        }

        /**
         * removeComponent
         * Remove a component
         * @param entity: the entity
         */
        template<typename Component>
        void removeComponent(entity_t const &entity)
        {
            auto &array = getComponent<Component>();
            array.erase(entity);
        }

        /**
         * hasComponent
         * Check if the entity has a component
         * @param entity: the entity
         * @return: true or false
         */
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
