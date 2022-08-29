//
// Created by WIN10 on 2022/8/1.
//

#ifndef SCPPSOCKET_TCPSERVERNETMANAGERWORKERWIN_H
#define SCPPSOCKET_TCPSERVERNETMANAGERWORKERWIN_H
#include "../NetManagerWorkerServer.h"
#include <list>
#include "../SocketUtil.h"
namespace scppsocket
{
    class TCPServerNetManagerWorkerWin:public NetManagerWorkerServer
    {
    private:
        void HandleAccept();
        void HandleRead();
        fd_set readfds;
        fd_set testfds;
    public:
        TCPServerNetManagerWorkerWin();
        virtual ~TCPServerNetManagerWorkerWin() override;
        virtual void DoWork() override;
        virtual void SendMessage(int FileDescriptor, const char* Msg, int Len) override;
        virtual void Broadcast(const char *Msg, int Len) override;
        virtual void StopWork() override;
    };

}


#endif //SCPPSOCKET_TCPSERVERNETMANAGERWORKERWIN_H
