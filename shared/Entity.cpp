/*
** EPITECH PROJECT, 2023
** bs_rtype
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

Entity::Entity(size_t value) : _size(value)
{
}

Entity::operator size_t() const
{
    return _size;
}
