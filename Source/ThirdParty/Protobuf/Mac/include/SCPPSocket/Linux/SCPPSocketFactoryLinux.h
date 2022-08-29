//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_SCPPSOCKETFACTORYLINUX_H
#define SCPPSOCKET_SCPPSOCKETFACTORYLINUX_H
#include "../SCPPSocketFactory.h"
namespace scppsocket
{
    class SCPPSocketFactoryLinux : public SCPPSocketFactory{
    public:
        SCPPSocketFactoryLinux();
        virtual ~SCPPSocketFactoryLinux() override;
        virtual SCPPSocket* CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol) override;
        virtual sockaddr_in CreateAddress(const char* Address, int Port) override;
        virtual NetManagerWorker* CreateTCPServerNetMangerWorker(SCPPSocket* Local) override;
        virtual NetManagerWorker* CreateTCPClientNetMangerWorker(SCPPSocket* Local) override;
    };

}



#endif //SCPPSOCKET_SCPPSOCKETFACTORYLINUX_H
