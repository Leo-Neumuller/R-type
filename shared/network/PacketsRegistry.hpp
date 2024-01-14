/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** PacketsRegistry.hpp
*/

#ifndef R_TYPE_SERVER_PACKETSREGISTRY_HPP
#define R_TYPE_SERVER_PACKETSREGISTRY_HPP

#include <iostream>
#include <map>
#include <any>
#include <memory>
#include "EPacket.hpp"
#include "IPacket.hpp"
#include "GenericPacket.hpp"


namespace network {

    /**
     * PacketsRegistry
     * Class of the packets registry
     */
    class PacketsRegistry {
        public:

            /**
             * Constructor
             */
            PacketsRegistry() : _packets_client(), _packets_server()
            {
            }

            /**
             * Destructor
             */
            ~PacketsRegistry() = default;

            /**
             * registerPacketClient
             * Register a packet that comes from the client
             * @param func: the function to call when the packet is received
             * @param packet: the packet to register
             */
            template<typename... Args, typename Func>
            void registerPacketClient(Func func, EPacketClient packet) {
                _packets_client.emplace(packet, [func]() { return new GenericPacket<Func , Args...>(func); });
            }

            /**
             * registerPacketClient
             * Register a packet that comes from the client
             * @param packet: the packet to register
             * @param func: the function to call when the packet is received
             */
            void registerPacketClient(EPacketClient packet, const std::function<void(int)>& func) {
                _packets_client.emplace(packet, [func]() { return new GenericPacket<std::function<void(int)>>(func); });
            }

            /**
             * registerPacketServer
             * Register a packet that comes from the server
             * @param func: the function to call when the packet is received
             * @param packet: the packet to register
             */
            template<typename... Args, typename Func>
            void registerPacketServer(Func func, EPacketServer packet) {
                _packets_server.emplace(packet, [func]() { return new GenericPacket<Func , Args...>(func); });
            }

            /**
             * registerPacketServer
             * Register a packet that comes from the server
             * @param packet: the packet to register
             * @param func: the function to call when the packet is received
             */
            void registerPacketServer(EPacketServer packet, const std::function<void(int)>& func) {
                _packets_server.emplace(packet, [func]() { return new GenericPacket<std::function<void(int)>>(func); });
            }

            /**
             * getPacket
             * Get a packet
             * @param packet: the packet to get
             * @return: the packet
             */
            std::shared_ptr<IPacket *>getPacket(EPacketClient packet) {
                if (_packets_client.find(packet) == _packets_client.end())
                    throw std::runtime_error("Packet not found");
                return (std::make_shared<IPacket *>(_packets_client[packet]()));
            }

            /**
             * getPacket
             * Get a packet
             * @param packet: the packet to get
             * @return: the packet
             */
            std::shared_ptr<IPacket *>getPacket(EPacketServer packet) {
                if (_packets_server.find(packet) == _packets_server.end())
                    throw std::runtime_error("Packet not found");
                return (std::make_shared<IPacket *>(_packets_server[packet]()));
            }

            /**
             * getPacketClient
             * Get a packet that comes from the client
             * @param packet: the packet to get
             * @return: the packet
             */
            std::shared_ptr<IPacket *>getPacketClient(EPacketClient packet) {
                return (std::make_shared<IPacket *>(_packets_client[packet]()));
            }

            /**
             * getPacketServer
             * Get a packet that comes from the server
             * @param packet: the packet to get
             * @return: the packet
             */
            std::shared_ptr<IPacket *>getPacketServer(EPacketServer packet) {
                return (std::make_shared<IPacket *>(_packets_server[packet]()));
            }
        protected:

        private:
            std::map<EPacketClient, std::function<IPacket *()>> _packets_client;
            std::map<EPacketServer, std::function<IPacket *()>> _packets_server;


    };

} // Server

#endif //R_TYPE_SERVER_PACKETSREGISTRY_HPP
