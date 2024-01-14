/*
** EPITECH PROJECT, 2023
** r-type_server
** File description:
** EPacket.hpp
*/

#ifndef R_TYPE_SERVER_EPACKET_HPP
#define R_TYPE_SERVER_EPACKET_HPP

/**
 * EPacketResponse
 * Enum of the packet response
 */
enum EPacketResponse {
    OK,
    KO,
    UNKNOWN
};

/**
 * EPacketType
 * Enum of the packet type
 */
enum EPacketClient {
    DEBUG_PACKET_CLIENT,
    CLIENT_HELLO,
    CLIENT_SEND_POS_VEL,
    CLIENT_DISCONNECT
};

/**
 * EPacketServer
 * Enum of the packet type
 */
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
