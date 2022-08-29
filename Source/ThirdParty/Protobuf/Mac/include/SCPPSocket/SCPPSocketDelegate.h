//
// Created by harryqk on 8/7/22.
//

#ifndef SCPPSOCKET_SCPPSOCKETDELEGATE_H
#define SCPPSOCKET_SCPPSOCKETDELEGATE_H
//client
typedef void (*OnClientMessageReadDelegate)(const char* Message, int Len);
typedef void (*OnConnectDelegate)(bool Value);

//server
typedef void (*OnBindDelegate)(bool Value);
typedef void (*OnAcceptDelegate)(int FileDescriptor);
typedef void (*OnRemoveClientDelegate)(int FileDescriptor);
typedef void (*OnServerMessageReadDelegate)(int FileDescriptor, const char* Message, int Len);
//both
typedef void (*OnNetworkDisconnectDelegate)(const char* Error);
typedef void (*OnDebugPrintDelegate)(const char* Info);
#endif //SCPPSOCKET_SCPPSOCKETDELEGATE_H
