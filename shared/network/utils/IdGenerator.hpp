
/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** IdGenerator.hpp
*/

#ifndef R_TYPE_SERVER_IDGENERATOR_HPP
#define R_TYPE_SERVER_IDGENERATOR_HPP

#include <iostream>
#include <map>

namespace network {

    /*
     * IdGenerator
     * Class of the id generator
     */
    class IdGenerator {
        public:
            IdGenerator();
            ~IdGenerator();

            int getId(const std::string &source);
        protected:

        private:
            int _count;
            std::map<std::string, int> _id_map;

    };

} // Server

#endif //R_TYPE_SERVER_IDGENERATOR_HPP
