//
// Created by harryqk on 8/8/22.
//

#ifndef SCPPSOCKET_NETMANAGERWORKERCLIENT_H
#define SCPPSOCKET_NETMANAGERWORKERCLIENT_H
#include "NetManagerWorker.h"
namespace scppsocket
{
    class NetManagerWorkerClient:public NetManagerWorker
    {
    public:
        NetManagerWorkerClient();
        virtual ~NetManagerWorkerClient() override;
        void SetOnClientMessageReadDelegate(OnClientMessageReadDelegate Delegate);
        void SetOnConnectDelegate(OnConnectDelegate Delegate);

    protected:
        OnClientMessageReadDelegate OnClientMessageRead;

        OnConnectDelegate OnConnect;

    protected:

        char* LenBuf;
        char* ReadBuf;
    public:
        Connection *ConnectionToServer;
        SCPPSocket* Local;
        virtual void DoWork() override;
        virtual void SendMessage(const char *Msg, int Len) = 0;
        virtual void StopWork() override;
    };
}



#endif //SCPPSOCKET_NETMANAGERWORKERCLIENT_H
