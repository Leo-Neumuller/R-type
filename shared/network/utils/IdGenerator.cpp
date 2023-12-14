/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** IdGenerator.cpp
*/

#include "IdGenerator.hpp"

namespace network {

    IdGenerator::IdGenerator() : _count(0), _id_map()
    {
    }

    IdGenerator::~IdGenerator()
    {
    }

    int IdGenerator::getId(const std::string &source)
    {

        if (_id_map.find(source) == _id_map.end())
            _id_map[source] = _count++;

        return _id_map[source];
    }


} // Server