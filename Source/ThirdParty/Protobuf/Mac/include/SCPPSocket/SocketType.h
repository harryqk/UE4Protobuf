//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_SOCKETTYPE_H
#define SCPPSOCKET_SOCKETTYPE_H
namespace scppsocket
{
    /** Indicates the socket protocol of socket being used, typically for BSD Sockets */
    enum class SocketAddressFamily : int
    {
        /** No protocol family specification. Typically defined as AF_UNSPEC */
        None,
        /** IPv4 and IPv6 respectively. */
        IPv4,
        IPv6
    };

    enum class SocketProtocol : int
    {
        TCP,
        UDP
    };

/** Indicates the type of socket being used (streaming or datagram) */
    enum SocketType
    {
        /** Not bound to a protocol yet */
        SOCKTYPE_Unknown,
        /** A UDP type socket */
        SOCKTYPE_Datagram,
        /** A TCP type socket */
        SOCKTYPE_Streaming
    };

/** Indicates the connection state of the socket */
    enum SocketConnectionState
    {
        NotConnected,
        Connected,
        /** Indicates that the end point refused the connection or couldn't be reached */
        ConnectionError
    };

    enum SocketBlockMode
    {

        Unknown,
        Block,
        NonBlock
    };
}
#endif //SCPPSOCKET_SOCKETTYPE_H
