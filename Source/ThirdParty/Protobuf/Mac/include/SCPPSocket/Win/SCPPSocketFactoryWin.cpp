//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketFactoryWin.h"
#include "SCPPSocketWin.h"

#include "TCPClientNetManagerWorkerWin.h"
#include "TCPServerNetManagerWorkerWin.h"

namespace scppsocket
{
    SCPPSocketFactoryWin::SCPPSocketFactoryWin()
    {
        std::printf("construct SCPPSocketFactoryWin\n");
    }

    SCPPSocketFactoryWin::~SCPPSocketFactoryWin()
    {
        std::printf("destruct SCPPSocketFactoryWin\n");
    }

    SCPPSocket* SCPPSocketFactoryWin::CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
    {
        SCPPSocketWin* SocketWin = new SCPPSocketWin(AddressFamily, Type, Protocol);
        return SocketWin;

    }

    sockaddr_in SCPPSocketFactoryWin::CreateAddress(const char *Address, int Port)
    {
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(Address);
        server_addr.sin_port = htons(Port);
        return server_addr;
    }

    NetManagerWorker *SCPPSocketFactoryWin::CreateTCPClientNetMangerWorker(SCPPSocket *Local)
    {
        TCPClientNetManagerWorkerWin* Win = new TCPClientNetManagerWorkerWin();
        Win->Local = Local;
        //Mac->ConnectionToServer = ConnectionToServer;
        return Win;
    }

    NetManagerWorker *SCPPSocketFactoryWin::CreateTCPServerNetMangerWorker(SCPPSocket *Local)
    {
        TCPServerNetManagerWorkerWin* Win = new TCPServerNetManagerWorkerWin();
        Win->SetLocal(Local);
        return Win;
    }

}