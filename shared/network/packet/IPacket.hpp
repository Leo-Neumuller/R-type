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

    /*
     * IPacket
     * Interface of the packet
     */
    class IPacket {
        public:

            virtual ~IPacket() = default;
            /*
             * deserialize
             * Deserialize the packet
             */
            virtual void deserialize(std::vector<char> &data) = 0;

            /*
             * getSizeRequired
             * Get the size required
             */
            virtual int getSizeRequired() = 0;

            /*
             * handleData
             * Handle the data
             */
            virtual void handleData(int fromId) = 0;

            /*
             * setPacketCount
             * Set the packet count
             */
            virtual void setPacketCount(int packetCount) = 0;

            /*
             * getPacketCount
             * Get the packet count
             */
            virtual int getPacketCount() = 0;
    };

} // Server

#endif //R_TYPE_SERVER_IPACKET_HPP
