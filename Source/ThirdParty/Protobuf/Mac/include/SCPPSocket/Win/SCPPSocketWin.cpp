//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketWin.h"
#include <iostream>
namespace scppsocket
{
    SCPPSocketWin::SCPPSocketWin(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol) : SCPPSocket(AddressFamily, Type, Protocol)
    {
        std::printf("this is SCPPSocketWin Construct\n");

        //----------------------
        // Create a SOCKET for connecting to server
        FileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (FileDescriptor == INVALID_SOCKET) {
            wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        }
    }

    SCPPSocketWin::~SCPPSocketWin()
    {
        WSACleanup();
        std::printf("this is SCPPSocketWin Destruct\n");
    }

    int SCPPSocketWin::Bind(int Port)
    {
        std::printf("this is Win bind\n");

        struct sockaddr_in Address;
        memset(&Address, 0, sizeof(Address));
        Address.sin_family = AF_INET;  //
        Address.sin_addr.s_addr = INADDR_ANY;
        Address.sin_port = htons(Port);
        LocalAddress = Address;
        int ret = bind(FileDescriptor, (struct sockaddr*)&Address, sizeof(Address));
        if(ret == SOCKET_ERROR)
        {
            //printf("this is mac Bind fail, errno=%d\n", errno);
            perror("Win Bind fail");
        }
        else
        {
            printf("this is Win Bind success\n");
        }
        return ret;
    }

    int SCPPSocketWin::Listen(int MaxConnect)
    {
        printf("this is Win Listen\n");
        int ret = listen(FileDescriptor, MaxConnect);
        if(ret < 0)
        {
            //printf("this is mac Listen fail, errno=%d\n", errno);
            perror("Win Listen fail");

        }
        else
        {
            printf("this is Win Listen success\n");
        }

        return ret;
    }

    int SCPPSocketWin::Connect(sockaddr *Address)
    {
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("192.168.0.1");
        server_addr.sin_port = htons(1500);

        //----------------------
        // Connect to server.
        int ret = connect(FileDescriptor, Address, sizeof (sockaddr));
//        if (ret == SOCKET_ERROR) {
//            wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
//            ret = closesocket(FileDescriptor);
//            if (ret == SOCKET_ERROR)
//                wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
//            WSACleanup();
//            return 1;
//        }

        return ret;
    }

    SSocket SCPPSocketWin::Accept(sockaddr *Address)
    {
        SockLen_t Len = sizeof(struct  sockaddr);
        SSocket NewSock = accept(FileDescriptor, Address, &Len);
        if (NewSock == SOCKET_ERROR)
        {
            printf("Win Accept fail, errno=%d\n", errno);
            perror("Win Accept fail");
            WSACleanup();
            return 0;
        }
        else {
            std::printf("Win Accept Success\n");
        }
        return NewSock;
    }

    SockSSize_t SCPPSocketWin::Send(const char *Buf, SockSize_t Len, int Flag)
    {
        std::printf("this is Win Send\n");
        SockSSize_t Sent = send(FileDescriptor, Buf, Len, Flag);
        return Sent;
    }

    SockSSize_t SCPPSocketWin::Read(char *Buf, SockSize_t Len, int Flag)
    {
        std::printf("this is Win Recv\n");
        SockSSize_t Read = recv(FileDescriptor, Buf, Len, Flag);
        return Read;
    }

    int SCPPSocketWin::SetNonBlockMode(bool NonBlock)
    {
        int flags = 0;
        int iMode = 1; //
        if (NonBlock)
        {
            flags =  ioctlsocket(FileDescriptor, FIONBIO, (u_long FAR*)&iMode);
            if (flags == SOCKET_ERROR)
            {
                //printf("set sockfd nonblock -1, errno=%d\n", errno);
                perror("win SetNonBlockMode error");
                BlockMode = SocketBlockMode::Unknown;
                return BlockMode;
            }
            else
            {
                BlockMode = SocketBlockMode::NonBlock;
            }
        }
        else
        {
            iMode = 0;
            flags =  ioctlsocket((SOCKET)socket, FIONBIO, (u_long FAR*)&iMode);
            if (flags == SOCKET_ERROR)
            {
                //printf("set sockfd nonblock -1, errno=%d\n", errno);
                perror("win SetNonBlockMode error");
                BlockMode = SocketBlockMode::Unknown;
                return BlockMode;
            }
            else
            {
                BlockMode = SocketBlockMode::Block;
            }
        }

        return BlockMode;


    }

    SCPPSocketWin::SCPPSocketWin()
    {
        std::printf("SCPPSocketWin default construct\n");
    }

    bool SCPPSocketWin::Close()
    {
        int ret;
        try {
            ret = closesocket(FileDescriptor);
        }
        catch(std::exception e)
        {
            printf("Win close exception=%s\n", e.what());
        }
        if(ret == SOCKET_ERROR)
        {
            //printf("mac close errno=%d\n", errno);
            perror("Win close error");
            return false;
        } else
        {
            printf("Win close success\n");
            return true;
        }
    }

    bool SCPPSocketWin::ShutDown()
    {
        int ret;
        try {
            ret = shutdown(FileDescriptor, 2);
        }
        catch(std::exception e)
        {
            printf("Win shutdown exception=%s\n", e.what());
        }
        if(ret == SOCKET_ERROR)
        {
            //printf("mac shut down errno=%d\n", errno);
            perror("Win shut down error");
            return false;
        } else
        {
            printf("Win shut down success\n");
            return true;
        }
    }

    SCPPSocket *SCPPSocketWin::Clone(SSocket NewSocket, sockaddr_in NewPeerAddress)
    {
        SCPPSocketWin* Mac = new SCPPSocketWin(AddressFamily, Type, Protocol);
        Mac->SetPeerAddress(NewPeerAddress);
        Mac->SetFileDescriptor(NewSocket);
        return Mac;
    }

}
