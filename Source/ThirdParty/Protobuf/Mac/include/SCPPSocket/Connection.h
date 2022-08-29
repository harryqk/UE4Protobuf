//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_CONNECTION_H
#define SCPPSOCKET_CONNECTION_H
#include "SCPPSocket.h"
#include "Message.h"
#include <queue>
#include <mutex>
namespace scppsocket
{
    class Connection {
    protected:
        SCPPSocket* SSock;
    public:
        SCPPSocket *GetSSock() const;

    public:
        explicit Connection(SCPPSocket* sSock);
        virtual ~Connection();

    protected:
        std::queue<Message*> SendMessage;
        std::queue<Message*> ReadMessage;
        std::mutex MutexSend;
        std::mutex MutexRead;
    public:
        virtual SockSSize_t Send(const char*buf, SockSize_t Len) = 0;
        virtual void PushSendMessage(char* buf, SockSize_t Len) = 0;
        virtual bool SendAll() = 0;
        virtual SockSSize_t Read(char* buf, SockSize_t Len) = 0;
        virtual void PushReadMessage(char* buf, SockSize_t Len) = 0;
        virtual Message* PopReadMessage() = 0;

    };

}


#endif //SCPPSOCKET_CONNECTION_H
