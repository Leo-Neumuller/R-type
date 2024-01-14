/*
** EPITECH PROJECT, 2023
** bs_rtype
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

/**
 * Entity
 * Constructor of Entity
 * @param value: the value
 */
Entity::Entity(size_t value) : _size(value)
{
}

/**
 * operator size_t
 * Operator for size_t
 * @return: the size
 */
Entity::operator size_t() const
{
    return _size;
}
