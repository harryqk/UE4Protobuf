//
// Created by WIN10 on 2022/8/1.
//

#include "TCPClientNetManagerWorkerWin.h"
#include "../SocketUtil.h"
#include "../TCPConnection.h"
#include <iostream>
namespace scppsocket
{

    void TCPClientNetManagerWorkerWin::DoWork()
    {
        int nread;
        int fd = Local->GetFileDescriptor();
        int ret = HandleConnect();
        int result;
        if(ret == SOCKET_ERROR)
        {
            Local->Close();
            WSACleanup();
            return;
        }
        FD_ZERO(&readfds);
        //Add client fd to set
        FD_SET(fd, &readfds);
        while(IsWorking)
        {
            //Copy readfds to testfds, select will modify testfds
            testfds = readfds;
            printf("client waiting\n");
            fflush(stdout);
            //std::cout << "client waiting\n";

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
                FD_CLR(Local->GetFileDescriptor(), &readfds);
                Local->Close();
                WSACleanup();
                break;
            }

            if(FD_ISSET(fd, &testfds))
            {

                int ret =Local->Read(LenBuf,4,0);

                if(ret==SOCKET_ERROR)
                {
                    int err =WSAGetLastError();
                    if(err==WSAEWOULDBLOCK)
                    {
                        continue;
                    }
                    else if(err==WSAETIMEDOUT)//timeout
                    {
                        FD_CLR(Local->GetFileDescriptor(), &readfds);
                        Local->Close();
                        printf("timeout client close socket on fd %d\n", fd);
                        WSACleanup();
                        break;
                    }
                    else if(err==WSAENETDOWN)//disconnect
                    {
                        FD_CLR(Local->GetFileDescriptor(), &readfds);
                        Local->Close();
                        printf("disconnect client close socket on fd %d\n", fd);
                        WSACleanup();
                        break;
                    }
                    else
                    {
                        FD_CLR(Local->GetFileDescriptor(), &readfds);
                        Local->Close();
                        printf("error client close socket on fd %d\n", fd);
                        WSACleanup();
                        break;
                    }
                }
                else if(ret == 0)
                {
                    FD_CLR(Local->GetFileDescriptor(), &readfds);
                    Local->Close();
                    printf("client close socket on fd %d\n", fd);
                    WSACleanup();
                    break;
                }
                else
                {
                    //ConnectionToServer->Read(LenBuf, 4);
                    int len = SocketUtil::BytesToInt((byte *)LenBuf);
                    ConnectionToServer->Read(ReadBuf, len);
//                    char* msg = new char[len];
//                    memcpy(msg, ReadBuf, len);
//                    printf("client read  %d\n", len);
//                    printf("client read  %s\n", msg);
                    if(OnClientMessageRead != nullptr)
                    {
                        OnClientMessageRead(ReadBuf, len);
                    }
                }
            }
        }
        printf("client do work finish\n");
    }

    void TCPClientNetManagerWorkerWin::SendMessage(const char *Msg, int Len)
    {
        ConnectionToServer->Send(Msg, Len);
    }

    TCPClientNetManagerWorkerWin::TCPClientNetManagerWorkerWin()
    {
        std::printf("construct TCPClientNetManagerWorkerWin\n");
    }

    TCPClientNetManagerWorkerWin::~TCPClientNetManagerWorkerWin()
    {
        std::printf("destruct TCPClientNetManagerWorkerWin\n");
    }


    void TCPClientNetManagerWorkerWin::HandleRead()
    {

    }

    int TCPClientNetManagerWorkerWin::HandleConnect()
    {
        int client_fd;
        int result = SOCKET_ERROR;
        client_fd = Local->GetFileDescriptor();

        result = Local->Connect((sockaddr*)&Local->GetPeerAddress());

        if(result!=0)
        {
            int err =WSAGetLastError();
            if(err==WSAEWOULDBLOCK)
            {
                printf("client connect WSAEWOULDBLOCK ignore\n");
                struct timeval tm = {2, 0};
                fd_set wset,rset;
                FD_ZERO(&wset);
                FD_ZERO(&rset);
                FD_SET(client_fd,&wset);
                FD_SET(client_fd,&rset);
                long t1 = time(nullptr);
                int res = select(client_fd+1,&rset,&wset,nullptr,&tm);
                long t2 = time(nullptr);
                printf("interval time: %ld\n", t2 - t1);
                if(res < 0)
                {
                    printf("network error in connect\n");
                    Local->Close();
                    WSACleanup();
                }
                else if(res == 0)
                {
                    printf("connect time out\n");
                    Local->Close();
                    WSACleanup();
                }
                else if (1 == res)
                {
                    if(FD_ISSET(client_fd,&wset))
                    {
                        Connection* Conn = new TCPConnection(Local);
                        ConnectionToServer = Conn;
                        printf("connect succeed.\n");
                        //Local->SetFileDescriptor(result);
                        result = 0;
                    }
                    else
                    {
                        printf("other error when select:%s\n",strerror(errno));
                        Local->Close();
                        WSACleanup();
                    }
                }
            }
            else if(err==WSAETIMEDOUT)//timeout
            {
                Local->Close();
                WSACleanup();
                printf("timeout client close socket on fd %d\n", client_fd);

            }
            else if(err==WSAENETDOWN)//disconnect
            {
                Local->Close();
                WSACleanup();
                printf("disconnect client close socket on fd %d\n", client_fd);
            }
            else
            {
                Local->Close();
                WSACleanup();
                printf("error client close socket on fd %d\n", client_fd);
            }
        }
        return result;

    }

    void TCPClientNetManagerWorkerWin::StopWork()
    {

        if(ConnectionToServer != nullptr && ConnectionToServer->GetSSock() != nullptr)
        {
            FD_CLR(ConnectionToServer->GetSSock()->GetFileDescriptor(), &readfds);
            ConnectionToServer->GetSSock()->ShutDown();
            ConnectionToServer->GetSSock()->Close();
        }
        std::printf("TCPClientNetManagerWorkerWin StopWork\n");
    }
}