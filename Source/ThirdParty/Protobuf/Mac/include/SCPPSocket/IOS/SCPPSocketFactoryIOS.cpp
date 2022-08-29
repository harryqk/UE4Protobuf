//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketFactoryIOS.h"
#include "SCPPSocketIOS.h"
#include "TCPClientNetManagerWorkerIOS.h"
#include "TCPServerNetManagerWorkerIOS.h"
#include <iostream>
namespace scppsocket
{
    SCPPSocket* SCPPSocketFactoryIOS::CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
    {
        SCPPSocketIOS* SocketIOS = new SCPPSocketIOS(AddressFamily, Type, Protocol);
        return SocketIOS;
    }

    sockaddr_in SCPPSocketFactoryIOS::CreateAddress(const char *Address, int Port)
    {
        struct sockaddr_in server_addr;
        bzero(&server_addr,sizeof(server_addr)); //Init address
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(Port);
        inet_pton(AF_INET, Address, &server_addr.sin_addr);
        return server_addr;
    }

    NetManagerWorker *SCPPSocketFactoryIOS::CreateTCPClientNetMangerWorker(SCPPSocket* Local)
    {
        TCPClientNetManagerWorkerIOS* IOS = new TCPClientNetManagerWorkerIOS();
        IOS->Local = Local;
        //IOS->ConnectionToServer = ConnectionToServer;
        return IOS;
    }

    NetManagerWorker *SCPPSocketFactoryIOS::CreateTCPServerNetMangerWorker(SCPPSocket* Local)
    {
        TCPServerNetManagerWorkerIOS* IOS = new TCPServerNetManagerWorkerIOS();
        IOS->SetLocal(Local);
        return IOS;
    }

    SCPPSocketFactoryIOS::SCPPSocketFactoryIOS()
    {
        std::printf("construct SCPPSocketFactoryIOS\n");
    }

    SCPPSocketFactoryIOS::~SCPPSocketFactoryIOS()
    {
        std::printf("destruct SCPPSocketFactoryIOS\n");
    }


}
