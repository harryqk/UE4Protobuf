//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_TCPSERVERNETMANAGERWORKERMAC_H
#define SCPPSOCKET_TCPSERVERNETMANAGERWORKERMAC_H
#include "../NetManagerWorkerServer.h"
#include <list>
#include "../SocketUtil.h"
namespace scppsocket
{

    class TCPServerNetManagerWorkerMac:public NetManagerWorkerServer
    {

    public:


    private:

        void HandleAccept();
        void HandleRead();
        fd_set readfds;
        fd_set testfds;

    public:
        TCPServerNetManagerWorkerMac();
        virtual ~TCPServerNetManagerWorkerMac() override;
        virtual void DoWork() override;
        virtual void SendMessage(int FileDescriptor, const char* Msg, int Len) override;
        virtual void Broadcast(const char *Msg, int Len) override;
        virtual void StopWork() override;
    };

}


#endif //SCPPSOCKET_TCPSERVERNETMANAGERWORKERMAC_H
