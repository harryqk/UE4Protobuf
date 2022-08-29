//
// Created by harryqk on 7/19/22.
//

#ifndef SCPPSOCKET_MESSAGE_H
#define SCPPSOCKET_MESSAGE_H

namespace scppsocket
{
    class Message {
    public:
        Message(char* Data, int Len);
        ~Message();
        char* Data;
        int Len;
    };


}



#endif //SCPPSOCKET_MESSAGE_H
