/*
** EPITECH PROJECT, 2023
** bs_rtype
** File description:
** Entity.hpp
*/

#ifndef BS_RTYPE_ENTITY_HPP
#define BS_RTYPE_ENTITY_HPP

#include <iostream>


class Entity {
    public:
        explicit Entity(size_t value);

        operator size_t() const;

    protected:

    private:
        size_t _size;

};


#endif //BS_RTYPE_ENTITY_HPP
