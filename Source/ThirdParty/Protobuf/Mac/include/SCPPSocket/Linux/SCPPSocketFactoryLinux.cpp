//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketFactoryLinux.h"
#include "SCPPSocketLinux.h"
#include "TCPClientNetManagerWorkerLinux.h"
#include "TCPServerNetManagerWorkerLinux.h"
#include <iostream>
namespace scppsocket
{
    SCPPSocket* SCPPSocketFactoryLinux::CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
    {
        SCPPSocketLinux* SocketLinux = new SCPPSocketLinux(AddressFamily, Type, Protocol);
        return SocketLinux;
    }

    sockaddr_in SCPPSocketFactoryLinux::CreateAddress(const char *Address, int Port)
    {
        struct sockaddr_in server_addr;
        //bzero(&server_addr,sizeof(server_addr)); //Init address
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(Port);
        inet_pton(AF_INET, Address, &server_addr.sin_addr);
        return server_addr;
    }

    NetManagerWorker *SCPPSocketFactoryLinux::CreateTCPClientNetMangerWorker(SCPPSocket* Local)
    {
        TCPClientNetManagerWorkerLinux* Mac = new TCPClientNetManagerWorkerLinux();
        Mac->Local = Local;
        //Mac->ConnectionToServer = ConnectionToServer;
        return Mac;
    }

    NetManagerWorker *SCPPSocketFactoryLinux::CreateTCPServerNetMangerWorker(SCPPSocket* Local)
    {
        TCPServerNetManagerWorkerLinux* Mac = new TCPServerNetManagerWorkerLinux();
        Mac->SetLocal(Local);
        return Mac;
    }

    SCPPSocketFactoryLinux::SCPPSocketFactoryLinux()
    {
        std::printf("construct SCPPSocketFactoryMac\n");
    }

    SCPPSocketFactoryLinux::~SCPPSocketFactoryLinux()
    {
        std::printf("destruct SCPPSocketFactoryMac\n");
    }


}