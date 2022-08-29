//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_SCPPSOCKETFACTORYMAC_H
#define SCPPSOCKET_SCPPSOCKETFACTORYMAC_H
#include "../SCPPSocketFactory.h"
namespace scppsocket
{
    class SCPPSocketFactoryMac : public SCPPSocketFactory{
    public:
        SCPPSocketFactoryMac();
        virtual ~SCPPSocketFactoryMac() override;
        virtual SCPPSocket* CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol) override;
        virtual sockaddr_in CreateAddress(const char* Address, int Port) override;
        virtual NetManagerWorker* CreateTCPServerNetMangerWorker(SCPPSocket* Local) override;
        virtual NetManagerWorker* CreateTCPClientNetMangerWorker(SCPPSocket* Local) override;
    };

}



#endif //SCPPSOCKET_SCPPSOCKETFACTORYMAC_H
