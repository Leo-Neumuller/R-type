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
    /**
     * NetworkClient
     * Constructor of NetworkClient
     * @param id: the id
     * @param endpoint: the endpoint
     * @param sendCallBack: the send data callback
     */
    NetworkClient::NetworkClient(int id, asio::ip::udp::endpoint &endpoint,
                                 std::function<void(const std::vector<char> &)> sendCallBack)
            : _id(id), _endpoint(endpoint), _buffer_for_packet(), _buffered_size(-1),
            _buffered_id(-1), _connected(false), _send_callback(std::move(sendCallBack)), _buffered_packet_count(-1), _packets()
    {

    }

    /**
     * ~NetworkClient
     * Destructor of NetworkClient
     */
    NetworkClient::~NetworkClient()
    {
    }

    /**
     * getBufferForPacket
     * Get the buffer for packet
     * @return: the buffer for packet
     */
    std::vector<char> &NetworkClient::getBufferForPacket()
    {
        return _buffer_for_packet;
    }

    /**
     * getBufferedSize
     * Get the buffered size
     * @return: the buffered size
     */
    int NetworkClient::getBufferedSize() const
    {
        return _buffered_size;
    }

    /**
     * setBufferedSize
     * Set the buffered size
     * @param bufferedSize: the buffered size
     */
    void NetworkClient::setBufferedSize(int bufferedSize)
    {
        _buffered_size = bufferedSize;
    }

    /**
     * getBufferedId
     * Get the buffered id
     * @return: the buffered id
     */
    short NetworkClient::getBufferedId() const
    {
        return _buffered_id;
    }

    /**
     * setBufferedId
     * Set the buffered id
     * @param bufferedId: the buffered id
     */
    void NetworkClient::setBufferedId(short bufferedId)
    {
        _buffered_id = bufferedId;
    }

    /**
     * isConnected
     * Check if the client is connected
     * @return: true if the client is connected, false otherwise
     */
    bool NetworkClient::isConnected() const
    {
        return _connected;
    }

    /**
     * setConnected
     * Set if the client is connected
     * @param connected: true if connected, false otherwise
     */
    void NetworkClient::setConnected(bool connected)
    {
        _connected = connected;
    }

    /**
     * send
     * Send data to the client through a callback
     * @param data: the data to send
     */
    void NetworkClient::send(std::vector<char> &data)
    {
        _send_callback(data);
    }

    /**
     * getBufferedPacketCount
     * Get the buffered packet count
     * @return: the buffered packet count
     */
    int NetworkClient::getBufferedPacketCount() const
    {
        return _buffered_packet_count;
    }

    /**
     * setBufferedPacketCount
     * Set the buffered packet count
     * @param bufferedPacketCount: the buffered packet count
     */
    void NetworkClient::setBufferedPacketCount(int bufferedPacketCount)
    {
        _buffered_packet_count = bufferedPacketCount;
    }

    /**
     * getPackets
     * Get the packets map
     * @return: the packets map
     */
    std::map<int, std::shared_ptr<IPacket *>> &NetworkClient::getPackets()
    {
        return _packets;
    }

}