/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** IPacket.hpp
*/

#ifndef R_TYPE_SERVER_IPACKET_HPP
#define R_TYPE_SERVER_IPACKET_HPP

#include "EPacket.hpp"
#include <vector>
#include <functional>

namespace network {

    class IPacket {
        public:
            virtual ~IPacket() = default;
            virtual void deserialize(std::vector<char> &data) = 0;
            virtual int getSizeRequired() = 0;
            virtual void handleData(int fromId) = 0;
    };

} // Server

#endif //R_TYPE_SERVER_IPACKET_HPP
