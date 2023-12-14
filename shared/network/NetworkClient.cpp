/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** Client.cpp
*/

#include "NetworkClient.hpp"

#include <utility>
#include "asio.hpp"

namespace network {
    NetworkClient::NetworkClient(int id, asio::ip::udp::endpoint &endpoint,
                                 std::function<void(const std::vector<char> &)> sendCallBack)
            : _id(id), _endpoint(endpoint), _buffer_for_packet(), _buffered_size(-1), _buffered_id(-1), _connected(false), _send_callback(std::move(sendCallBack))
    {

    }

    NetworkClient::~NetworkClient()
    {
    }

    std::vector<char> &NetworkClient::getBufferForPacket()
    {
        return _buffer_for_packet;
    }

    int NetworkClient::getBufferedSize() const
    {
        return _buffered_size;
    }

    void NetworkClient::setBufferedSize(int bufferedSize)
    {
        _buffered_size = bufferedSize;
    }

    short NetworkClient::getBufferedId() const
    {
        return _buffered_id;
    }

    void NetworkClient::setBufferedId(short bufferedId)
    {
        _buffered_id = bufferedId;
    }

    bool NetworkClient::isConnected() const
    {
        return _connected;
    }

    void NetworkClient::setConnected(bool connected)
    {
        _connected = connected;
    }

    void NetworkClient::send(std::vector<char> &data)
    {
//        std::lock_guard<std::mutex> lock(_mutex);

        _send_callback(data);
    }

}