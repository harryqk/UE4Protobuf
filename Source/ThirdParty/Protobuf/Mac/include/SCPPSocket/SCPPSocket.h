//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_SCPPSOCKET_H
#define SCPPSOCKET_SCPPSOCKET_H
#include "SocketType.h"
#ifdef _WIN32

#include <winsock2.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
typedef SOCKET SSocket;
typedef int SockLen_t;
typedef int SockSize_t;
typedef int SockSSize_t;
#elif __APPLE__


#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <sys/select.h>
#include <sys/ioctl.h>
#include<unistd.h>
typedef socklen_t SockLen_t;
typedef int SSocket;
typedef size_t SockSize_t;
typedef ssize_t SockSSize_t;

#elif __ANDROID__
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
typedef socklen_t SockLen_t;
typedef int SSocket;
typedef size_t SockSize_t;
typedef ssize_t SockSSize_t;
#elif __linux__
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
typedef socklen_t SockLen_t;
typedef int SSocket;
typedef size_t SockSize_t;
typedef ssize_t SockSSize_t;
#endif
#define SOCKET_ERROR (-1)
namespace scppsocket
{

    class SCPPSocket {
    public:
        SCPPSocket();
        SCPPSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol);
        virtual ~SCPPSocket();
        virtual int Bind(int Port) = 0;
        virtual int Listen(int MaxConnect) = 0;
        //Address is server address
        virtual int Connect(sockaddr* Address) = 0;
        //Address is return address of client
        virtual SSocket Accept(sockaddr* Address) = 0;
        virtual SockSSize_t Send(const char* Buf, SockSize_t Len, int Flag) = 0;
        virtual SockSSize_t Read(char* Buf, SockSize_t Len, int Flag) = 0;
        SocketConnectionState GetConnectionState();
        virtual int SetNonBlockMode(bool NonBlock) = 0;
        virtual SCPPSocket* Clone(SSocket NewSocket, sockaddr_in NewPeerAddress) = 0;
        virtual bool Close() = 0;
        virtual bool ShutDown() = 0;
    protected:
        SSocket FileDescriptor;
    public:
        SSocket GetFileDescriptor() const;

        void SetFileDescriptor(SSocket fileDescriptor);

    protected:
        SocketAddressFamily AddressFamily;
        SocketType Type;
        SocketProtocol Protocol;
        sockaddr_in LocalAddress;
        sockaddr_in PeerAddress;
    public:
        const sockaddr_in &GetLocalAddress() const;

        void SetLocalAddress(const sockaddr_in &localAddress);

        const sockaddr_in &GetPeerAddress() const;

        void SetPeerAddress(const sockaddr_in &peerAddress);


    protected:
        SocketBlockMode BlockMode;
    public:
        SocketBlockMode GetBlockMode() const;


    public:

        void SetConnectionState(SocketConnectionState connectionState);

    protected:
        SocketConnectionState ConnectionState;
    };
}



#endif //SCPPSOCKET_SCPPSOCKET_H
