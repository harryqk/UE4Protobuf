//
// Created by WIN10 on 2022/8/1.
//

#include "TCPServerNetManagerWorkerWin.h"
#include "../TCPConnection.h"
namespace scppsocket
{
    void TCPServerNetManagerWorkerWin::DoWork()
    {
        int server_sockfd;
        int result;
        server_sockfd = Local->GetFileDescriptor();
        FD_ZERO(&readfds);
        //Add server fd to set
        FD_SET(server_sockfd, &readfds);
        while(IsWorking)
        {
            //Copy readfds to testfds, select will modify testfds
            testfds = readfds;
            std::printf("server waiting\n");
            fflush(stdout);
            //Block until certain fd readable or error return, FD_SETSIZE is max system fd value
            result = select(FD_SETSIZE, &testfds, (fd_set *) nullptr,(fd_set *)nullptr, (struct timeval *) nullptr);
            if(result < 1)
            {
                int err =WSAGetLastError();
                if(err = WSANOTINITIALISED)
                {
                    printf("select WSANOTINITIALISED\n");
                }
                else if(err == WSAEFAULT)
                {
                    printf("select WSAEFAULT\n");
                }
                else if(err == WSAENETDOWN)
                {
                    printf("select WSAENETDOWN\n");
                }
                else if(err == WSAEINVAL)
                {
                    printf("select WSAEINVAL\n");
                }
                else if(err == WSAEINTR)
                {
                    printf("select WSAEINTR\n");
                }
                else if(err =WSAEINPROGRESS)
                {
                    printf("select WSAEINPROGRESS\n");
                }
                else if(err = WSAENOTSOCK)
                {
                    printf("select WSAENOTSOCK\n");
                }
                else
                {
                    printf("select fail\n");
                }
                Local->Close();
                break;
            }

            if(FD_ISSET(server_sockfd, &testfds))
            {
                HandleAccept();
            }
            else
            {
                HandleRead();
            }
        }
        printf("server do work finish\n");
    }


    void TCPServerNetManagerWorkerWin::HandleAccept()
    {
        int client_sockfd;
        struct sockaddr_in client_address;
        client_sockfd = Local->Accept((struct sockaddr *)&client_address);

        SCPPSocket* NewSock = Local->Clone(client_sockfd, client_address);
        Connection* Conn = new TCPConnection(NewSock);
        ConnectionsToClient.push_back(Conn);
        FD_SET(client_sockfd, &readfds);
        printf("adding client on fd %d\n", client_sockfd);
    }

    void TCPServerNetManagerWorkerWin::HandleRead()
    {
        int nread;

        std::list<Connection*>::iterator it = ConnectionsToClient.begin();
        while (it != ConnectionsToClient.end())
        {
            Connection* conn = *it;
            SSocket fd = conn->GetSSock()->GetFileDescriptor();
            if(FD_ISSET(fd,&testfds))
            {
                int ret =conn->Read(LenBuf,4);

                if(ret==SOCKET_ERROR)
                {
                    int err =WSAGetLastError();
                    if(err==WSAEWOULDBLOCK)
                    {
                        continue;
                    }
                    else if(err==WSAETIMEDOUT)//timeout
                    {
                        printf("timeout removing client on fd %d\n", fd);
                    }
                    else if(err==WSAENETDOWN)//disconnect
                    {
                        printf("The network subsystem has failed removing client on fd %d\n", fd);
                    }
                    else if(err == WSAESHUTDOWN)
                    {
                        printf("The socket has been shut down removing client on fd %d\n", fd);
                    }
                    else if(err == WSAECONNRESET)
                    {
                        printf("The socket has been reset by peer removing client on fd %d\n", fd);
                    }
                    else
                    {
                        printf("error happen removing client on fd %d\n", fd);
                    }
                    conn->GetSSock()->Close();
                    FD_CLR(fd, &readfds);
                    ConnectionsToClient.erase(it++);
                    delete conn;
                    conn = nullptr;
                }
                else if(ret == 0)
                {
                    conn->GetSSock()->Close();
                    //Clear select readfds of this client
                    FD_CLR(fd, &readfds);
                    printf("removing client on fd %d\n", fd);
                    ConnectionsToClient.erase(it++);
                    delete conn;
                    conn = nullptr;
                }
                else
                {
                    //ConnectionToServer->Read(LenBuf, 4);
                    int len = SocketUtil::BytesToInt((byte *)LenBuf);
                    conn->Read(ReadBuf, len);
//                    char* msg = new char[len + 1];
//                    memcpy(msg, ReadBuf, len);
//                    msg[len] = '\0';
//                    printf("client read  %d\n", len);
//                    printf("client read  %s\n", msg);
//                    delete[] msg;
                    if(OnServerMessageRead != nullptr)
                    {
                        OnServerMessageRead(conn->GetSSock()->GetFileDescriptor(), ReadBuf, len);
                    }
                    it++;
                }
            } else
            {
                it++;
            }
        }
    }

    TCPServerNetManagerWorkerWin::TCPServerNetManagerWorkerWin()
    {

        std::printf("construct TCPServerNetManagerWorkerWin\n");
    }

    TCPServerNetManagerWorkerWin::~TCPServerNetManagerWorkerWin()
    {
        std::printf("destruct TCPServerNetManagerWorkerWin\n");
    }


    void TCPServerNetManagerWorkerWin::StopWork()
    {
        delete LenBuf;
        LenBuf = nullptr;
        delete ReadBuf;
        ReadBuf = nullptr;
        std::list<Connection*>::iterator p1;
        for(p1=ConnectionsToClient.begin();p1!=ConnectionsToClient.end();p1++)
        {
            Connection* Conn = (Connection*)*p1;
            FD_CLR(Conn->GetSSock()->GetFileDescriptor(), &readfds);
            //Conn->GetSSock()->ShutDown();
            Conn->GetSSock()->Close();
        }
        if(Local != nullptr)
        {
            FD_CLR(Local->GetFileDescriptor(), &readfds);
            Local->ShutDown();
            Local->Close();
        }
        std::printf("TCPServerNetManagerWorkerWin StopWork\n");
    }

    void TCPServerNetManagerWorkerWin::SendMessage(int FileDescriptor, const char* Msg, int Len)
    {
        std::list<Connection*>::iterator p1;
        for(p1=ConnectionsToClient.begin();p1!=ConnectionsToClient.end();p1++)
        {
            Connection* Conn = (Connection*)*p1;
            if(Conn->GetSSock()->GetFileDescriptor() == FileDescriptor)
            {
                Conn->Send(Msg, Len);
                break;
            }
        }
    }

    void TCPServerNetManagerWorkerWin::Broadcast(const char *Msg, int Len)
    {
        std::list<Connection*>::iterator p1;
        for(p1=ConnectionsToClient.begin();p1!=ConnectionsToClient.end();p1++)
        {
            Connection* Conn = (Connection*)*p1;
            Conn->Send(Msg, Len);
        }
    }
}