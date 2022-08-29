//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_SCPPSOCKETFACTORY_H
#define SCPPSOCKET_SCPPSOCKETFACTORY_H
//#include "SCPPSocket.h"
#include "NetManagerWorker.h"
#include <list>
namespace scppsocket
{
    class SCPPSocketFactory {
    public:
        SCPPSocketFactory();
        virtual ~SCPPSocketFactory();
        virtual SCPPSocket* CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol) = 0;
        virtual sockaddr_in CreateAddress(const char* Address, int Port) = 0;
        virtual NetManagerWorker* CreateTCPServerNetMangerWorker(SCPPSocket* Local) = 0;
        virtual NetManagerWorker* CreateTCPClientNetMangerWorker(SCPPSocket* Local) = 0;
    };
}




#endif //SCPPSOCKET_SCPPSOCKETFACTORY_H
