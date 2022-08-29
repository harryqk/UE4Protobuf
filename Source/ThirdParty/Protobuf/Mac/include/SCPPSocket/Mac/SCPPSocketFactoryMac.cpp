//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketFactoryMac.h"
#include "SCPPSocketMac.h"
#include "TCPClientNetManagerWorkerMac.h"
#include "TCPServerNetManagerWorkerMac.h"
#include <iostream>
namespace scppsocket
{
    SCPPSocket* SCPPSocketFactoryMac::CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
    {
        SCPPSocketMac* SocketMac = new SCPPSocketMac(AddressFamily, Type, Protocol);
        return SocketMac;
    }

    sockaddr_in SCPPSocketFactoryMac::CreateAddress(const char *Address, int Port)
    {
        struct sockaddr_in server_addr;
        bzero(&server_addr,sizeof(server_addr)); //Init address
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(Port);
        inet_pton(AF_INET, Address, &server_addr.sin_addr);
        return server_addr;
    }

    NetManagerWorker *SCPPSocketFactoryMac::CreateTCPClientNetMangerWorker(SCPPSocket* Local)
    {
        TCPClientNetManagerWorkerMac* Mac = new TCPClientNetManagerWorkerMac();
        Mac->Local = Local;
        //Mac->ConnectionToServer = ConnectionToServer;
        return Mac;
    }

    NetManagerWorker *SCPPSocketFactoryMac::CreateTCPServerNetMangerWorker(SCPPSocket* Local)
    {
        TCPServerNetManagerWorkerMac* Mac = new TCPServerNetManagerWorkerMac();
        Mac->SetLocal(Local);
        return Mac;
    }

    SCPPSocketFactoryMac::SCPPSocketFactoryMac()
    {
        std::printf("construct SCPPSocketFactoryMac\n");
    }

    SCPPSocketFactoryMac::~SCPPSocketFactoryMac()
    {
        std::printf("destruct SCPPSocketFactoryMac\n");
    }


}