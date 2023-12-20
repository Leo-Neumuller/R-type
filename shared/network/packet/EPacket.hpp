/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** EPacket.hpp
*/

#ifndef R_TYPE_SERVER_EPACKET_HPP
#define R_TYPE_SERVER_EPACKET_HPP

enum EPacketResponse {
    OK,
    KO,
    UNKNOWN
};

enum EPacketClient {
    DEBUG_PACKET_CLIENT,
    CLIENT_HELLO,
    CLIENT_DISCONNECT
};

enum EPacketServer {
    DEBUG_PACKET_SERVER,
    SERVER_HELLO,
    NOTIFY_NEW_CLIENT,
    CLIENT_BASE_INFO,
    FORCE_SET_POS_VEL,
    SEND_POS_VEL,
    SERVER_DISCONNECT
};

#endif //R_TYPE_SERVER_EPACKET_HPP