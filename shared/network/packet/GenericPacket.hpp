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

    template<typename Func, typename... Args>
    class GenericPacket : public IPacket {
        public:
            explicit GenericPacket(Func func) : _size(0), _func(func) {
                _nb_params = sizeof...(Args);
                (addParamSize<Args>(), ...);
            };
            ~GenericPacket() override = default;

            void deserialize(std::vector<char> &data) override {
                unpackParams<Args...>(data);
                data.clear();
            };

            std::shared_ptr<std::vector<char>> serialize(Args... args)
            {
                std::shared_ptr<std::vector<char>> data = std::make_shared<std::vector<char>>();

                if (sizeof...(Args) == 0)
                    return data;
                (appendToData<Args>(args, *data), ...);

                return data;
            }

            int getSizeRequired() override
            {
                return _size;
            }

            void handleData(int fromId) override
            {
                _fromId = fromId;
                execFuncWithData<Args...>();
            }

        protected:

        private:

            template <typename T, typename = void>
            struct has_iterator : std::false_type {};

            template <typename T>
            struct has_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

            template<class Arg>
            typename std::enable_if<!has_iterator<Arg>::value>::type
            appendToData(Arg arg, std::vector<char> &data) {
                data.resize(data.size() + sizeof(Arg));
                std::memcpy(data.data() + data.size() - sizeof(Arg), &arg, sizeof(Arg));
            }

            template<class Arg>
            typename std::enable_if<has_iterator<Arg>::value>::type
            appendToData(Arg arg, std::vector<char> &data) {
                int size = static_cast<int>(arg.size());

                data.resize(data.size() + sizeof(int));
                std::memcpy(data.data() + data.size() - sizeof(int), &size, sizeof(int));
                data.resize(data.size() + size);
                std::memcpy(data.data() + data.size() - size, arg.data(), size);
            }

            template<class Arg>
            Arg getParam() {
                for (auto &param : _params) {
                    if (param.first == std::type_index(typeid(Arg))) {
                        return std::any_cast<Arg>(param.second);
                    }
                }
                throw std::runtime_error("Param not found");
            }

            template <typename... Arg>
            void execFuncWithData() {
                std::function<void()> func = [this]() {
                    _func(_fromId, getParam<Arg>()...);
                };
                func();
            }

            template <typename Arg>
            void addParamSize() {
                _size += sizeof(Arg);
            }

            template <typename Arg>
            typename std::enable_if<!has_iterator<Arg>::value>::type
            unpackParam(std::vector<char> &data) {
                Arg param;
                int size = sizeof(Arg);

                std::memcpy(&param, data.data(), size);
                data.erase(data.begin(), data.begin() + size);
                _params.insert(_params.begin(), std::make_pair(std::type_index(typeid(Arg)), param));
            };

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



            template <typename... Arg>
            void unpackParams(std::vector<char> &data) {
                (unpackParam<Arg>(data), ...);
            };

            int _nb_params;
            std::vector<std::pair<std::type_index, std::any>> _params;
            int _size;
            Func _func;
            int _fromId;

    };

} // Server

#endif //R_TYPE_SERVER_GENERICPACKET_HPP
