//
// Created by WIN10 on 2022/8/1.
//

#ifndef SCPPSOCKET_TCPCLIENTNETMANAGERWORKERWIN_H
#define SCPPSOCKET_TCPCLIENTNETMANAGERWORKERWIN_H
#include "../NetManagerWorkerClient.h"
namespace scppsocket
{
    class TCPClientNetManagerWorkerWin:public NetManagerWorkerClient
    {
    public:
        TCPClientNetManagerWorkerWin();
        virtual ~TCPClientNetManagerWorkerWin() override;
    private:
        int HandleConnect();
        void HandleRead();
        fd_set readfds;
        fd_set testfds;

    public:

        virtual void DoWork() override;
        virtual void SendMessage(const char *Msg, int Len) override;
        virtual void StopWork() override;
    };
}



#endif //SCPPSOCKET_TCPCLIENTNETMANAGERWORKERWIN_H
