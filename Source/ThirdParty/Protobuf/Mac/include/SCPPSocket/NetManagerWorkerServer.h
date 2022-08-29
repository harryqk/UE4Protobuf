//
// Created by harryqk on 8/8/22.
//

#ifndef SCPPSOCKET_NETMANAGERWORKERSERVER_H
#define SCPPSOCKET_NETMANAGERWORKERSERVER_H
#include "NetManagerWorker.h"
#include <list>
namespace scppsocket
{
    class NetManagerWorkerServer:public NetManagerWorker
    {
    public:
        NetManagerWorkerServer();
        virtual ~NetManagerWorkerServer() override;
        void SetOnBindDelegate(OnBindDelegate Delegate);
        void SetOnAcceptDelegate(OnAcceptDelegate Delegate);
        void SetOnRemoveClientDelegate(OnRemoveClientDelegate Delegate);
        void SetOnServerMessageReadDelegate(OnServerMessageReadDelegate Delegate);
        virtual void SendMessage(int FileDescriptor, const char* Msg, int Len) = 0;
        virtual void Broadcast(const char *Msg, int Len) = 0;
    protected:
        OnBindDelegate OnBind;
        OnAcceptDelegate OnAccept;
        OnRemoveClientDelegate OnRemoveClient;
        OnServerMessageReadDelegate OnServerMessageRead;


        std::list<Connection*> ConnectionsToClient;
        SCPPSocket* Local;
    public:
        SCPPSocket *GetLocal() const;

        void SetLocal(SCPPSocket *local);

    protected:
        int MaxConnection;

        char* LenBuf;
        char* ReadBuf;
    public:
        int GetMaxConnection() const;
        virtual void DoWork() override;
        void SetMaxConnection(int maxConnection);
        virtual void StopWork() override;
    };
}



#endif //SCPPSOCKET_NETMANAGERWORKERSERVER_H
