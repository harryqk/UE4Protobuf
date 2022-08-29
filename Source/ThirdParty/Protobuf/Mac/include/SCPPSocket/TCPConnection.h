//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_TCPCONNECTION_H
#define SCPPSOCKET_TCPCONNECTION_H
#include "Connection.h"
namespace scppsocket
{
    class TCPConnection: public Connection
    {
        public:
        explicit TCPConnection(SCPPSocket* sSock);
        virtual ~TCPConnection() override;
        virtual SockSSize_t Send(const char*buf, SockSize_t Len) override;
        //game tcp do not need but stream media udp may need
        virtual void PushSendMessage(char* buf, SockSize_t Len) override;
        //game tcp do not need
        virtual bool SendAll() override;
        virtual SockSSize_t Read(char* buf, SockSize_t Len) override;
        virtual void PushReadMessage(char* buf, SockSize_t Len) override;
        virtual Message* PopReadMessage() override;
    };

}



#endif //SCPPSOCKET_TCPCONNECTION_H
