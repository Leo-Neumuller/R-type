/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** GenericPacket.hpp
*/

#ifndef R_TYPE_SERVER_GENERICPACKET_HPP
#define R_TYPE_SERVER_GENERICPACKET_HPP

#include <iostream>
#include "IPacket.hpp"

namespace Server {

    template<EPacketHandleType HandleType, typename Func, typename... Args>
    class GenericPacket : public IPacket<HandleType, Func, Args...> {
        public:
            GenericPacket() = default;
            ~GenericPacket() = default;

            void serialize(Args...) override {
                std::cout << "GenericPacket::serialize()" << std::endl;
            };

            Func deserialize(std::vector<char> data) override {
                std::cout << "GenericPacket::deserialize()" << std::endl;
            };

            EPacketHandleType getHandleType() override {
                std::cout << "GenericPacket::getHandleType()" << std::endl;
                return HandleType;
            };

        protected:

        private:

    };

} // Server

#endif //R_TYPE_SERVER_GENERICPACKET_HPP
