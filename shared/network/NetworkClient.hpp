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
        protected:

        private:
            int _id;
            asio::ip::udp::endpoint &_endpoint;
            std::vector<char> _buffer_for_packet;
            int _buffered_size;
            short _buffered_id;
            bool _connected;
            std::function<void(const std::vector<char> &)> _send_callback;

    };

}

#endif //R_TYPE_SERVER_NETWORKCLIENT_HPP
