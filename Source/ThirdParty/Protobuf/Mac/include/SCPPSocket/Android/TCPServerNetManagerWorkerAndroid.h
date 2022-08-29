//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_TCPSERVERNETMANAGERWORKERANDROID_H
#define SCPPSOCKET_TCPSERVERNETMANAGERWORKERANDROID_H
#include "../NetManagerWorkerServer.h"
#include <list>
#include "../SocketUtil.h"
namespace scppsocket
{

    class TCPServerNetManagerWorkerAndroid:public NetManagerWorkerServer
    {

    public:


    private:

        void HandleAccept();
        void HandleRead();
        fd_set readfds;
        fd_set testfds;

    public:
        TCPServerNetManagerWorkerAndroid();
        virtual ~TCPServerNetManagerWorkerAndroid() override;
        virtual void DoWork() override;
        virtual void SendMessage(int FileDescriptor, const char* Msg, int Len) override;
        virtual void Broadcast(const char *Msg, int Len) override;
        virtual void StopWork() override;
    };

}


#endif //SCPPSOCKET_TCPSERVERNETMANAGERWORKERANDROID_H
