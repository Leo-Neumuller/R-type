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
#include <vector>
#include <any>
#include <cstring>
#include <typeindex>
#include <memory>
#include <experimental/type_traits>
#include <type_traits>

namespace network {

    /**
     * GenericPacket
     * Class that create a packet based of its type and able to serialize and deserialize
     */
    template<typename Func, typename... Args>
    class GenericPacket : public IPacket {
        public:
            /**
             * Constructor
             * @param func: function to execute when the packet is received
             */
            explicit GenericPacket(Func func) : _size(0), _func(func), _packet_count(-1) {
                _nb_params = sizeof...(Args);
                (addParamSize<Args>(), ...);
            };
            /**
             * Destructor
             */
            ~GenericPacket() override = default;

            /**
             * deserialize
             * Deserialize the packet
             * @param data: the data to deserialize
             */
            void deserialize(std::vector<char> &data) override {
                unpackParams<Args...>(data);
                data.clear();
            };

            /**
             * serialize
             * Serialize the packet
             * @param args: the arguments to serialize
             */
            std::shared_ptr<std::vector<char>> serialize(Args... args)
            {
                std::shared_ptr<std::vector<char>> data = std::make_shared<std::vector<char>>();

                if (sizeof...(Args) == 0)
                    return data;
                (appendToData<Args>(args, *data), ...);

                return data;
            }

            /**
             * getSizeRequired
             * Get the size required for the packet
             * @return the size required
             */
            int getSizeRequired() override
            {
                return _size;
            }

            /**
             * handleData
             * Handle the data
             * @param fromId: the id of the client
             */
            void handleData(int fromId) override
            {
                _fromId = fromId;
                execFuncWithData<Args...>();
            }

            /**
             * setPacketCount
             * Set the packet count
             * @param packetCount: the packet count
             */
            void setPacketCount(int packetCount) override
            {
                _packet_count = packetCount;
            }

            /**
             * getPacketCount
             * Get the packet count
             * @return the packet count
             */
            int getPacketCount() override
            {
                return _packet_count;
            }

        protected:

        private:

            /**
             * has_iterator
             * Check if the type has an iterator
             */
            template <typename T, typename = void>
            struct has_iterator : std::false_type {};

            /**
             * has_iterator
             * Check if the type has an iterator
             */
            template <typename T>
            struct has_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

            /**
             * appendToData
             * Append data to the packet
             * @param arg: the argument to append
             * @param data: the data to append to
             */
            template<class Arg>
            typename std::enable_if<!has_iterator<Arg>::value>::type
            appendToData(Arg arg, std::vector<char> &data) {
                data.resize(data.size() + sizeof(Arg));
                std::memcpy(data.data() + data.size() - sizeof(Arg), &arg, sizeof(Arg));
            }

            /**
             * appendToData
             * Append data to the packet
             * @param arg: the argument to append
             * @param data: the data to append to
             */
            template<class Arg>
            typename std::enable_if<has_iterator<Arg>::value>::type
            appendToData(Arg arg, std::vector<char> &data) {
                int size = static_cast<int>(arg.size());

                data.resize(data.size() + sizeof(int));
                std::memcpy(data.data() + data.size() - sizeof(int), &size, sizeof(int));
                data.resize(data.size() + size);
                std::memcpy(data.data() + data.size() - size, arg.data(), size);
            }

            /**
             * getParam
             * Get the parameter
             * @tparam Arg: the type of the parameter
             * @return the parameter
             */
            template<class Arg>
            Arg getParam() {
                for (auto &param : _params) {
                    if (param.first == std::type_index(typeid(Arg))) {
                        return std::any_cast<Arg>(param.second);
                    }
                }
                throw std::runtime_error("Param not found");
            }

            /**
             * execFuncWithData
             * Execute the function with the associated data
             */
            template <typename... Arg>
            void execFuncWithData() {
                std::function<void()> func = [this]() {
                    _func(_fromId, getParam<Arg>()...);
                };
                func();
            }

            /**
             * addParamSize
             * Add the size of the parameter
             */
            template <typename Arg>
            void addParamSize() {
                _size += sizeof(Arg);
            }

            /**
             * unpackParam
             * Unpack the parameter
             * @tparam Arg: the type of the parameter
             * @param data: the data to unpack
             * @return the parameter
             */
            template <typename Arg>
            typename std::enable_if<!has_iterator<Arg>::value>::type
            unpackParam(std::vector<char> &data) {
                Arg param;
                int size = sizeof(Arg);

                std::memcpy(&param, data.data(), size);
                data.erase(data.begin(), data.begin() + size);
                _params.insert(_params.begin(), std::make_pair(std::type_index(typeid(Arg)), param));
            };

            /**
             * unpackParam
             * Unpack the parameter
             * @tparam Arg: the type of the parameter
             * @param data: the data to unpack
             * @return the parameter
             */
            template <typename Arg>
            typename std::enable_if<has_iterator<Arg>::value>::type
            unpackParam(std::vector<char> &data) {
                Arg param;
                int size = 0;

                std::memcpy(&size, data.data(), sizeof(int));
                data.erase(data.begin(), data.begin() + sizeof(int));

                param.resize(size);

                std::memcpy(param.data(), data.data(), size);
                data.erase(data.begin(), data.begin() + size);

                _params.insert(_params.begin(), std::make_pair(std::type_index(typeid(Arg)), param));
            };

            /**
             * unpackParams
             * Unpack the parameters
             * @tparam Arg: the type of the parameters
             * @param data: the data to unpack
             */
            template <typename... Arg>
            void unpackParams(std::vector<char> &data) {
                (unpackParam<Arg>(data), ...);
            };

            int _nb_params;
            std::vector<std::pair<std::type_index, std::any>> _params;
            int _size;
            Func _func;
            int _fromId;
            int _packet_count;

    };

} // Server

#endif //R_TYPE_SERVER_GENERICPACKET_HPP
