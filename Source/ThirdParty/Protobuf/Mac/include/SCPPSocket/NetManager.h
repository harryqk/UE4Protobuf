//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_NETMANAGER_H
#define SCPPSOCKET_NETMANAGER_H
#include "NetManagerWorkerClient.h"
#include "NetManagerWorkerServer.h"
#include <list>
#include <thread>
#include "SCPPSocketDelegate.h"
namespace scppsocket
{
    class NetManager {
    public:

        bool StartTCPServer(int Port, int MaxConnection);
        void StopTCPCServer();

        void StartTCPClient(const char* Address, int Port);
        void StopTCPClient();
        void TCPClientSendMessage(const char* Msg, int Len);
        void TCPServerBroadcast(const char* Msg, int Len);
        void TCPServerSendMessage(int FileDescriptor, const char* Msg, int Len);
        void Clear();
        NetManager();
        ~NetManager();
        void SetOnClientMessageRead(OnClientMessageReadDelegate Delegate);
        void SetOnServerMessageRead(OnServerMessageReadDelegate Delegate);
        void SetOnDebugPrintDelegate(OnDebugPrintDelegate Delegate);
    private:

        NetManagerWorker* ClientWorker = nullptr;
        NetManagerWorker* ServerWorker = nullptr;
        SCPPSocket* Local;
        //std::list<Connection*> ConnectionsToClient;
        //Connection* ConnectionToServer;
        void Init();
        void Cleanup();
        //client

        OnClientMessageReadDelegate OnClientMessageRead;



        OnConnectDelegate OnConnect;
        //server

        OnBindDelegate OnBind;
        OnAcceptDelegate OnAccept;
        OnRemoveClientDelegate OnRemoveClient;
        OnServerMessageReadDelegate OnServerMessageRead;
        //both
        OnNetworkDisconnectDelegate OnNetworkDisconnect;
        OnDebugPrintDelegate OnDebugPrint;



    };

}


#endif //SCPPSOCKET_NETMANAGER_H
