//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_TCPCLIENTCONNECTION_H
#define SCPPSOCKET_TCPCLIENTCONNECTION_H
#include "Connection.h"

namespace scppsocket
{
    class TCPClientConnection: public Connection
    {
    public:
        void StartHeartBreak();
        void StopHeartBreak();
    };


}


#endif //SCPPSOCKET_TCPCLIENTCONNECTION_H
