//
// Created by harryqk on 7/21/22.
//

#include "TCPServerNetManagerWorkerMac.h"
#include "../TCPConnection.h"
#include <iostream>
namespace scppsocket
{
    void TCPServerNetManagerWorkerMac::DoWork()
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
            printf("server waiting\n");

            //Block until certain fd readable or error return, FD_SETSIZE is max system fd value
            result = select(FD_SETSIZE, &testfds, (fd_set *) nullptr,(fd_set *)nullptr, (struct timeval *) nullptr);
            if(result < 1)
            {
                printf("mac server select return errno=%d\n", errno);
                perror("mac server select return error");
                FD_CLR(Local->GetFileDescriptor(), &readfds);
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


    void TCPServerNetManagerWorkerMac::HandleAccept()
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

    void TCPServerNetManagerWorkerMac::HandleRead()
    {
        int nread;

        std::list<Connection*>::iterator it = ConnectionsToClient.begin();
        while (it != ConnectionsToClient.end())
        {
            Connection* conn = *it;
            SSocket fd = conn->GetSSock()->GetFileDescriptor();
            if(FD_ISSET(fd,&testfds))
            {
                ioctl(fd, FIONREAD, &nread);

                //Client shutdown, close socket of that client, remove this connection
                if(nread ==0)
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
                    conn->Read(LenBuf, 4);
                    int len = SocketUtil::BytesToInt((byte *)LenBuf);
                    conn->Read(ReadBuf, len);
//                    char* msg = new char[len + 1];
//                    memcpy(msg, ReadBuf, len);
//                    msg[len] = '\0';
//                    std::cout << len << std::endl;
//                    std::cout << msg << std::endl;
//                    printf("server read  %s\n", msg);
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

    TCPServerNetManagerWorkerMac::TCPServerNetManagerWorkerMac()
    {
        std::printf("construct TCPServerNetManagerWorkerMac\n");
    }

    TCPServerNetManagerWorkerMac::~TCPServerNetManagerWorkerMac()
    {
        std::printf("destruct TCPServerNetManagerWorkerMac\n");
    }

    void TCPServerNetManagerWorkerMac::SendMessage(int FileDescriptor, const char* Msg, int Len)
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

    void TCPServerNetManagerWorkerMac::Broadcast(const char *Msg, int Len)
    {
        std::list<Connection*>::iterator p1;
        for(p1=ConnectionsToClient.begin();p1!=ConnectionsToClient.end();p1++)
        {
            Connection* Conn = (Connection*)*p1;
            Conn->Send(Msg, Len);
        }
    }

    void TCPServerNetManagerWorkerMac::StopWork()
    {
        delete[] LenBuf;
        LenBuf = nullptr;
        delete[] ReadBuf;
        ReadBuf = nullptr;
        std::list<Connection*>::iterator p1;
        for(p1=ConnectionsToClient.begin();p1!=ConnectionsToClient.end();p1++)
        {
            Connection* Conn = (Connection*)*p1;
            FD_CLR(Conn->GetSSock()->GetFileDescriptor(), &readfds);
            Conn->GetSSock()->ShutDown();
            Conn->GetSSock()->Close();
        }
        if(Local != nullptr)
        {
            FD_CLR(Local->GetFileDescriptor(), &readfds);
            Local->ShutDown();
            Local->Close();
        }
        std::printf("TCPServerNetManagerWorkerMac StopWork\n");
    }
}


