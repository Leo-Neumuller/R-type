/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** NetworkHandler.hpp
*/

#ifndef R_TYPE_SERVER_NETWORKHANDLER_HPP
#define R_TYPE_SERVER_NETWORKHANDLER_HPP

#include <iostream>
#include <array>
#include "IdGenerator.hpp"
#include "NetworkClient.hpp"
#include "asio.hpp"
#include <mutex>
#include <stack>
#include <condition_variable>
#include "PacketsRegistry.hpp"

namespace network{

    /**
     * NetworkHandler
     * Class to handle the network
     */
    template<typename FromType>
    class NetworkHandler {
        public:
            /**
             * Constructor
             * @param _clients: the clients
             * @param packets_registry: the packets registry
             */
            NetworkHandler(std::map<int, NetworkClient> &_clients, PacketsRegistry &packets_registry) : _id_generator(), _clients(_clients), _network_mutex(), _packet_mutex(), _packet_stack(),
                                                                                                                        _packet_condition_variable(), _packets_registry(packets_registry), _send_packet_count(0)
            {
            }

            /**
             * Destructor
             */
            ~NetworkHandler()
            {
            }

            /**
             * handleReceive
             * Handle the receive
             * @param data: the data
             * @param bytes_transferred: the bytes transferred
             * @param endpoint: the endpoint
             * @param socket: the socket
             */
            void handleReceive(std::array<char, 1024> &data, std::size_t &bytes_transferred,
                                               asio::ip::udp::endpoint &endpoint, asio::ip::udp::socket &socket)
            {
                std::lock_guard<std::mutex> lock(_network_mutex);
                int id = _id_generator.getId(endpoint.address().to_string() + std::to_string(endpoint.port()));

                if (_clients.find(id) == _clients.end()) {
                    asio::ip::basic_endpoint<asio::ip::udp> duplicateEndpoint(endpoint);
                    _clients.emplace(id, NetworkClient(id, endpoint, [&socket, duplicateEndpoint, this] (const std::vector<char> &data) { socket.async_send_to(asio::buffer(data, 1024), duplicateEndpoint, std::bind(
                            &NetworkHandler::handler, this, std::placeholders::_1, std::placeholders::_2)); }));
                }
                std::vector<char> packet(data.begin(), data.begin() + bytes_transferred);

                {
                    std::lock_guard<std::mutex> lock2(_packet_mutex);
                    _packet_stack.emplace(id, packet);
                    _packet_condition_variable.notify_one();
                }
            }

            /**
             * threatPacket
             * Threat the packet
             */
            void threatPacket()
            {
                std::lock_guard<std::mutex> lock(_packet_mutex);
                if (_packet_stack.empty())
                    return;

                int cliend_id = _packet_stack.top().first;
                int size = _clients.at(cliend_id).getBufferedSize();
                short packet_id = _clients.at(cliend_id).getBufferedId();
                int packet_count = _clients.at(cliend_id).getBufferedPacketCount();

                _clients.at(cliend_id).getBufferForPacket().insert(
                        _clients.at(cliend_id).getBufferForPacket().end(),
                        _packet_stack.top().second.begin(), _packet_stack.top().second.end());
                _packet_stack.pop();
                if (packet_id != -1 && size != -1 && packet_count != -1) {
                    _threadDataPacket(size, packet_id, cliend_id, packet_count);
                    packet_id = -1;
                    size = -1;
                    packet_count = -1;
                }
                while (_clients.at(cliend_id).getBufferForPacket().size() >= sizeof(int) + sizeof(short) + sizeof(int)) {
                    std::memcpy(&size, _clients.at(cliend_id).getBufferForPacket().data(), sizeof(int));
                    _clients.at(cliend_id).getBufferForPacket().erase(_clients.at(cliend_id).getBufferForPacket().begin(),
                                                                      _clients.at(cliend_id).getBufferForPacket().begin() +
                                                                      sizeof(int));
                    std::memcpy(&packet_id, _clients.at(cliend_id).getBufferForPacket().data(), sizeof(short));
                    _clients.at(cliend_id).getBufferForPacket().erase(_clients.at(cliend_id).getBufferForPacket().begin(),
                                                                      _clients.at(cliend_id).getBufferForPacket().begin() +
                                                                      sizeof(short));
                    std::memcpy(&packet_count, _clients.at(cliend_id).getBufferForPacket().data(), sizeof(int));
                    _clients.at(cliend_id).getBufferForPacket().erase(_clients.at(cliend_id).getBufferForPacket().begin(),
                                                                      _clients.at(cliend_id).getBufferForPacket().begin() +
                                                                      sizeof(int));
                    if (_clients.at(cliend_id).getBufferForPacket().size() < size) {
                        _clients.at(cliend_id).setBufferedSize(size);
                        _clients.at(cliend_id).setBufferedId(packet_id);
                        _clients.at(cliend_id).setBufferedPacketCount(packet_count);
                        return;
                    }
                    if (size < 0 || packet_id < 0 || packet_count < 0) {
                        _clients.at(cliend_id).getBufferForPacket().clear();
                        return;
                    }
                    std::cout << "Packet received from client " << cliend_id << std::endl;
                    std::cout << "packet id: " << packet_id << std::endl;
                    std::cout << "size: " << size << std::endl;
                    std::cout << "count: " << packet_count << std::endl;
                    _threadDataPacket(size, packet_id, cliend_id, packet_count);
                }
            }

            /**
             * isPacketQueueEmpty
             * Check if the packet queue is empty
             * @return true if the packet queue is empty, false otherwise
             */
            bool isPacketQueueEmpty()
            {
                std::unique_lock<std::mutex> lock(_network_mutex);
                return _packet_stack.empty();
            }

            /**
             * serializeSendPacket
             * Serialize and send a packet
             * @param client_id: the client id
             * @param packet_id: the packet id
             * @param args: the arguments
             */
            template<typename Type, typename... Args, typename TypePacket>
            void serializeSendPacket(int client_id, TypePacket packet_id, Args... args) {
                auto cast = dynamic_cast<Type *>(*_packets_registry.getPacket(packet_id));
                std::shared_ptr<std::vector<char>> data = cast->serialize(args...);
                int size = static_cast<int>(data->size());

                _send_packet_count++;

                data->insert(data->begin(), (char *)&_send_packet_count, (char *)&_send_packet_count + sizeof(int));
                data->insert(data->begin(), (char *)&packet_id, (char *)&packet_id + sizeof(short ));
                data->insert(data->begin(), (char *)&size, (char *)&size + sizeof(int));


                _clients.at(client_id).send(*data);
            }

            /**
             * serializePacket
             * Serialize a packet
             * @param packet_id: the packet id
             * @param args: the arguments
             * @return the serialized packet
             */
            template<typename Type, typename... Args, typename TypePacket>
            std::shared_ptr<std::vector<char>> serializePacket(TypePacket packet_id, Args... args) {
                auto cast = dynamic_cast<Type *>(*_packets_registry.getPacket(packet_id));
                std::shared_ptr<std::vector<char>> data = cast->serialize(args...);
                int size = static_cast<int>(data->size());

                _send_packet_count++;

                data->insert(data->begin(), (char *)&_send_packet_count, (char *)&_send_packet_count + sizeof(int));
                data->insert(data->begin(), (char *)&packet_id, (char *)&packet_id + sizeof(short ));
                data->insert(data->begin(), (char *)&size, (char *)&size + sizeof(int));

                return data;
            }

            /**
             * runPackets
             * Run the packets
             */
            void runPackets()
            {
                for (auto &client : _clients) {
                    for (auto &packet : client.second.getPackets()) {
                        if (packet.second == nullptr)
                            continue;
                        (*packet.second)->handleData(client.first);
                    }

                    client.second.getPackets().clear();
                }
            }

        protected:

        private:
            /**
             * _threadDataPacket
             * Thread the data packet
             * @param size: the size
             * @param packet_id: the packet id
             * @param client_id: the client id
             * @param packet_count: the packet count
             */
            void _threadDataPacket(int size, short packet_id, int client_id, int packet_count)
            {
                if (size < 0 || packet_id < 0 || packet_count < 0) {
                    _clients.at(client_id).getBufferForPacket().clear();
                    return;
                }
                if (_clients.at(client_id).getBufferForPacket().size() < size) {
                    _clients.at(client_id).setBufferedSize(size);
                    _clients.at(client_id).setBufferedId(packet_id);
                    _clients.at(client_id).setBufferedPacketCount(packet_count);
                    return;
                }
                std::shared_ptr<IPacket *> packet = _packets_registry.getPacket(static_cast<FromType>(packet_id));

                if (packet == nullptr) {
                    _clients.at(client_id).getBufferForPacket().clear();
                    return;
                }
                (*packet)->deserialize(_clients.at(client_id).getBufferForPacket());
                _clients.at(client_id).getPackets().emplace(packet_count, packet);
            }

            /**
             * handler
             * fake dummy handler
             */
            void handler(std::any data...)
            {

            }

            IdGenerator _id_generator;
            std::map<int, NetworkClient> &_clients;
            std::mutex _network_mutex;
            std::mutex _packet_mutex;
            std::stack<std::pair<int, std::vector<char>>> _packet_stack;
            std::condition_variable _packet_condition_variable;
            PacketsRegistry &_packets_registry;
            int _send_packet_count;

    };

}
#endif //R_TYPE_SERVER_NETWORKHANDLER_HPP
