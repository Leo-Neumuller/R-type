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

namespace Server {

    template<EPacketHandleType HandleType, typename Func, typename... Args>
    class IPacket {
        public:
            virtual ~IPacket() = default;
            virtual void serialize(Args...) = 0;
            virtual Func deserialize(std::vector<char> data) = 0;
            virtual EPacketHandleType getHandleType() = 0;
    };

} // Server

#endif //R_TYPE_SERVER_IPACKET_HPP
