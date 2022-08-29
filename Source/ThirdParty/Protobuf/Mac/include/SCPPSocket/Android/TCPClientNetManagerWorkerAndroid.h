//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_TCPCLIENTNETMANAGERWORKERANDROID_H
#define SCPPSOCKET_TCPCLIENTNETMANAGERWORKERANDROID_H

#include "../NetManagerWorkerClient.h"
namespace scppsocket
{

    class TCPClientNetManagerWorkerAndroid:public NetManagerWorkerClient
    {
    public:
        TCPClientNetManagerWorkerAndroid();
        virtual ~TCPClientNetManagerWorkerAndroid() override;
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



#endif //SCPPSOCKET_TCPCLIENTNETMANAGERWORKERANDROID_H
