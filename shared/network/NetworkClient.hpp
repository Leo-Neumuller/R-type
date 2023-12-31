/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Client.hpp
*/

#ifndef R_TYPE_SERVER_NETWORKCLIENT_HPP
#define R_TYPE_SERVER_NETWORKCLIENT_HPP

#include <iostream>
#include "asio.hpp"
#include <mutex>
#include <functional>
#include <IPacket.hpp>
#include <map>

namespace network {
    class NetworkClient {
        public:
            explicit NetworkClient(int id, asio::ip::udp::endpoint &endpoint,
                                   std::function<void(const std::vector<char> &)> sendCallBack);
            ~NetworkClient();

            void send(std::vector<char> &data);
            std::vector<char> &getBufferForPacket();
            int getBufferedSize() const;
            void setBufferedSize(int bufferedSize);
            short getBufferedId() const;
            void setBufferedId(short bufferedId);
            bool isConnected() const;
            void setConnected(bool connected);
            int getBufferedPacketCount() const;
            void setBufferedPacketCount(int bufferedPacketCount);
            std::map<int, std::shared_ptr<IPacket *>> &getPackets();
        protected:

        private:
            int _id;
            asio::ip::udp::endpoint &_endpoint;
            std::vector<char> _buffer_for_packet;
            int _buffered_size;
            short _buffered_id;
            int _buffered_packet_count;
            bool _connected;
            std::function<void(const std::vector<char> &)> _send_callback;
            std::map<int, std::shared_ptr<IPacket *>> _packets;

    };

}

#endif //R_TYPE_SERVER_NETWORKCLIENT_HPP
