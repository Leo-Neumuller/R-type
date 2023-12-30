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

    template<typename FromType>
    class NetworkHandler {
        public:
            NetworkHandler(std::map<int, NetworkClient> &_clients, PacketsRegistry &packets_registry) : _id_generator(), _clients(_clients), _network_mutex(), _packet_mutex(), _packet_stack(),
                                                                                                                        _packet_condition_variable(), _packets_registry(packets_registry)
            {
            }

            ~NetworkHandler()
            {
            }

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

            void threatPacket()
            {
                std::lock_guard<std::mutex> lock(_packet_mutex);
                if (_packet_stack.empty())
                    return;

                int cliend_id = _packet_stack.top().first;
                int size = _clients.at(cliend_id).getBufferedSize();
                short packet_id = _clients.at(cliend_id).getBufferedId();

                _clients.at(cliend_id).getBufferForPacket().insert(
                        _clients.at(cliend_id).getBufferForPacket().end(),
                        _packet_stack.top().second.begin(), _packet_stack.top().second.end());
                _packet_stack.pop();
                if (packet_id != -1 && size != -1) {
                    _threadDataPacket(size, packet_id, cliend_id);
                    packet_id = -1;
                    size = -1;
                }
                while (_clients.at(cliend_id).getBufferForPacket().size() >= sizeof(int) + sizeof(short)) {
                    std::memcpy(&size, _clients.at(cliend_id).getBufferForPacket().data(), sizeof(int));
                    _clients.at(cliend_id).getBufferForPacket().erase(_clients.at(cliend_id).getBufferForPacket().begin(),
                                                                      _clients.at(cliend_id).getBufferForPacket().begin() +
                                                                      sizeof(int));
                    std::memcpy(&packet_id, _clients.at(cliend_id).getBufferForPacket().data(), sizeof(short));
                    _clients.at(cliend_id).getBufferForPacket().erase(_clients.at(cliend_id).getBufferForPacket().begin(),
                                                                      _clients.at(cliend_id).getBufferForPacket().begin() +
                                                                      sizeof(short));
                    if (_clients.at(cliend_id).getBufferForPacket().size() < size) {
                        _clients.at(cliend_id).setBufferedSize(size);
                        _clients.at(cliend_id).setBufferedId(packet_id);
                        return;
                    }
                    if (size < 0 || packet_id < 0) {
                        _clients.at(cliend_id).getBufferForPacket().clear();
                        return;
                    }
                    std::cout << "Packet received from client " << cliend_id << std::endl;
                    std::cout << "packet id: " << packet_id << std::endl;
                    std::cout << "size: " << size << std::endl;
                    _threadDataPacket(size, packet_id, cliend_id);
                }
            }

            bool isPacketQueueEmpty()
            {
                std::unique_lock<std::mutex> lock(_network_mutex);
                return _packet_stack.empty();
            }

            template<typename Type, typename... Args, typename TypePacket>
            void serializeSendPacket(int client_id, TypePacket packet_id, Args... args) {
                auto cast = dynamic_cast<Type *>(*_packets_registry.getPacket(packet_id));
                std::shared_ptr<std::vector<char>> data = cast->serialize(args...);
                int size = static_cast<int>(data->size());

                data->insert(data->begin(), (char *)&packet_id, (char *)&packet_id + sizeof(short ));
                data->insert(data->begin(), (char *)&size, (char *)&size + sizeof(int));

                _clients.at(client_id).send(*data);
            }

            template<typename Type, typename... Args, typename TypePacket>
            std::shared_ptr<std::vector<char>> serializePacket(TypePacket packet_id, Args... args) {
                auto cast = dynamic_cast<Type *>(*_packets_registry.getPacket(packet_id));
                std::shared_ptr<std::vector<char>> data = cast->serialize(args...);
                int size = data->size();

                data->insert(data->begin(), (char *)&packet_id, (char *)&packet_id + sizeof(short ));
                data->insert(data->begin(), (char *)&size, (char *)&size + sizeof(int));

                return data;
            }

        protected:

        private:
            void _threadDataPacket(int size, short packet_id, int client_id)
            {
                if (size < 0 || packet_id < 0) {
                    _clients.at(client_id).getBufferForPacket().clear();
                    return;
                }
                if (_clients.at(client_id).getBufferForPacket().size() < size) {
                    _clients.at(client_id).setBufferedSize(size);
                    _clients.at(client_id).setBufferedId(packet_id);
                    return;
                }
                std::unique_ptr<IPacket *> packet = _packets_registry.getPacket(static_cast<FromType>(packet_id));

                if (packet == nullptr) {
                    _clients.at(client_id).getBufferForPacket().clear();
                    return;
                }
//                if ((*packet)->getSizeRequired() > _clients.at(client_id).getBufferForPacket().size()) {
//                    _clients.at(client_id).setBufferedSize((*packet)->getSizeRequired());
//                    _clients.at(client_id).setBufferedId(packet_id);
//                    return;
//                }
                (*packet)->deserialize(_clients.at(client_id).getBufferForPacket());
                (*packet)->handleData(client_id);
            }

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

    };

}
#endif //R_TYPE_SERVER_NETWORKHANDLER_HPP
