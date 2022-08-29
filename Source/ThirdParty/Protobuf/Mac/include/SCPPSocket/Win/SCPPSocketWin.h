//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_SCPPSOCKETWIN_H
#define SCPPSOCKET_SCPPSOCKETWIN_H
#include "../SCPPSocket.h"
namespace scppsocket
{
    class SCPPSocketWin :public SCPPSocket{
    public:
        SCPPSocketWin(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol);
        SCPPSocketWin();
        virtual ~SCPPSocketWin();
        virtual int Bind(int Port) override;
        virtual int Listen(int MaxConnect) override;
        virtual int Connect(sockaddr* Address) override;
        virtual SSocket Accept(sockaddr* Address) override;
        virtual SockSSize_t Send(const char* Buf, SockSize_t Len, int Flag) override;
        virtual SockSSize_t Read(char* Buf, SockSize_t Len, int Flag) override;
        virtual int SetNonBlockMode(bool NonBlock) override;
        virtual bool Close() override;
        virtual bool ShutDown() override;
        virtual SCPPSocket* Clone(SSocket NewSocket, sockaddr_in NewPeerAddress) override;
    };


}



#endif //SCPPSOCKET_SCPPSOCKETWIN_H
