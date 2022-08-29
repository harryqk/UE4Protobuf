//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketFactoryAndroid.h"
#include "SCPPSocketAndroid.h"
#include "TCPClientNetManagerWorkerAndroid.h"
#include "TCPServerNetManagerWorkerAndroid.h"
#include <iostream>
namespace scppsocket
{
    SCPPSocket* SCPPSocketFactoryAndroid::CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
    {
        SCPPSocketAndroid* SocketAndroid = new SCPPSocketAndroid(AddressFamily, Type, Protocol);
        return SocketAndroid;
    }

    sockaddr_in SCPPSocketFactoryAndroid::CreateAddress(const char *Address, int Port)
    {
        struct sockaddr_in server_addr;
        //bzero(&server_addr,sizeof(server_addr)); //Init address
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(Port);
        inet_pton(AF_INET, Address, &server_addr.sin_addr);
        return server_addr;
    }

    NetManagerWorker *SCPPSocketFactoryAndroid::CreateTCPClientNetMangerWorker(SCPPSocket* Local)
    {
        TCPClientNetManagerWorkerAndroid* Mac = new TCPClientNetManagerWorkerAndroid();
        Mac->Local = Local;
        //Mac->ConnectionToServer = ConnectionToServer;
        return Mac;
    }

    NetManagerWorker *SCPPSocketFactoryAndroid::CreateTCPServerNetMangerWorker(SCPPSocket* Local)
    {
        TCPServerNetManagerWorkerAndroid* Mac = new TCPServerNetManagerWorkerAndroid();
        Mac->SetLocal(Local);
        return Mac;
    }

    SCPPSocketFactoryAndroid::SCPPSocketFactoryAndroid()
    {
        std::printf("construct SCPPSocketFactoryMac\n");
    }

    SCPPSocketFactoryAndroid::~SCPPSocketFactoryAndroid()
    {
        std::printf("destruct SCPPSocketFactoryMac\n");
    }


}