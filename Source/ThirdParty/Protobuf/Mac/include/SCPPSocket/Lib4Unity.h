#ifndef SCPPSOCKET_LIB4UNITY_H
#define SCPPSOCKET_LIB4UNITY_H
#include "NetManager.h"
#if UNITY_WSA
#define EXPORT_API __declspec(dllexport) __stdcall
#elif UNITY_WIN
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

namespace scppsocket
{
    extern "C"
    {
        extern "C" EXPORT_API NetManager* GetMgr();

        extern "C" EXPORT_API void StartClient(NetManager* Mgr, const char* Address, int Port);


        extern "C" EXPORT_API void StartServer(NetManager* Mgr, int Port, int MaxConnection);


        extern "C" EXPORT_API void StopClient(NetManager* Mgr);


        extern "C" EXPORT_API void StopServer(NetManager* Mgr);

        extern "C" EXPORT_API void TCPClientSendMessage(NetManager* Mgr, const char* Msg, int Len);
    }
    void hello();

    int Accept();

}


#endif //SCPPSOCKET_LIB4UNITY_H
