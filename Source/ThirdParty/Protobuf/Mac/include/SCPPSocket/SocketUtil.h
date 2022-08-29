//
// Created by harryqk on 7/22/22.
//

#ifndef SCPPSOCKET_SOCKETUTIL_H
#define SCPPSOCKET_SOCKETUTIL_H
#define byte unsigned char
namespace scppsocket
{
    class SocketUtil
    {
    public:
        static void IntToByte(int i,byte *bytes,int size = 4);
        static int BytesToInt(byte* bytes,int size = 4);
    };

}



#endif //SCPPSOCKET_SOCKETUTIL_H
