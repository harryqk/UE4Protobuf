//
// Created by harryqk on 7/21/22.
//

#include "TCPClientNetManagerWorkerIOS.h"
#include "../SocketUtil.h"
#include <sys/select.h>
#include "../TCPConnection.h"
namespace scppsocket
{

    void TCPClientNetManagerWorkerIOS::DoWork()
    {
        int nread;
        int fd = Local->GetFileDescriptor();
        int ret = HandleConnect();
        int result;
        if(ret == SOCKET_ERROR)
        {
            Local->Close();
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

            //Block until certain fd readable or error return, FD_SETSIZE is max system fd value
            result = select(FD_SETSIZE, &testfds, (fd_set *) nullptr,(fd_set *)nullptr, (struct timeval *) nullptr);


            if(result < 1)
            {
                printf("IOS client select return errno=%d\n", errno);
                perror("IOS client select return error");
                FD_CLR(Local->GetFileDescriptor(), &readfds);
                Local->Close();
                printf("client close socket on fd %d\n", fd);
                break;
            }

            if(FD_ISSET(fd, &testfds))
            {
                ioctl(fd, FIONREAD, &nread);

                //Server shutdown, close client
                if(nread == 0)
                {
                    FD_CLR(Local->GetFileDescriptor(), &readfds);
                    Local->Close();
                    printf("client close socket on fd %d\n", fd);
                    break;
                    //close(fd);
                    //FD_CLR(fd, &readfds);
                    //printf("removing client on fd %d\n", fd);
                }
                else
                {
                    ConnectionToServer->Read(LenBuf, 4);
                    int len = SocketUtil::BytesToInt((byte *)LenBuf);
                    ConnectionToServer->Read(ReadBuf, len);
//                    char* msg = new char[len];
//                    memcpy(msg, ReadBuf, len);
//                    printf("client read  %d\n", len);
//                    printf("client read  %s\n", msg);
//                    delete[] msg;
                    if(OnClientMessageRead != nullptr)
                    {
                        OnClientMessageRead(ReadBuf, len);
                    }

                }
            }
        }
        printf("client do work finish\n");
    }

    void TCPClientNetManagerWorkerIOS::SendMessage(const char *Msg, int Len)
    {
        ConnectionToServer->Send(Msg, Len);
    }

    TCPClientNetManagerWorkerIOS::TCPClientNetManagerWorkerIOS()
    {
//        LenBuf = new char[4];
//        ReadBuf = new char[1024];
        std::printf("construct TCPClientNetManagerWorkerIOS\n");
    }

    TCPClientNetManagerWorkerIOS::~TCPClientNetManagerWorkerIOS()
    {
//        delete[] ReadBuf;
//        ReadBuf = nullptr;
//        delete[] LenBuf;
//        LenBuf = nullptr;
//        if(ConnectionToServer != nullptr)
//        {
//            delete ConnectionToServer;
//            ConnectionToServer = nullptr;
//        }


        std::printf("destruct TCPClientNetManagerWorkerIOS\n");
    }


    void TCPClientNetManagerWorkerIOS::HandleRead()
    {

    }

    int TCPClientNetManagerWorkerIOS::HandleConnect()
    {
        int client_fd;
        int result;
        int ret = SOCKET_ERROR;
        client_fd = Local->GetFileDescriptor();

        result = Local->Connect((sockaddr*)&Local->GetPeerAddress());
        if (result != 0 )
        {
            if(errno != EINPROGRESS)
                printf("connect error :%s\n",strerror(errno));
            else
            {
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
                }
                else if(res == 0)
                {
                    printf("connect time out\n");
                }
                else
                {
                    if(FD_ISSET(client_fd,&wset))
                    {

                        int OptError;
                        socklen_t OptLen = sizeof(OptError);

                        if(getsockopt(client_fd, SOL_SOCKET, SO_ERROR, &OptError, &OptLen) < 0)
                        {
                            //connect fail
                            perror("connect fail");
                        }

                        if(OptError != 0)
                        {
                            //connect fail
                            perror("connect fail");
                        }
                        else
                        {
                            Connection* Conn = new TCPConnection(Local);
                            ConnectionToServer = Conn;
                            printf("connect succeed.\n");
                            //Local->SetFileDescriptor(result);
                            ret = 0;
                        }
                    }
                    else
                    {
                        printf("connect fail");
                    }
                }
            }
        }
        return ret;

    }

    void TCPClientNetManagerWorkerIOS::StopWork()
    {

        if(ConnectionToServer != nullptr && ConnectionToServer->GetSSock() != nullptr)
        {
            FD_CLR(ConnectionToServer->GetSSock()->GetFileDescriptor(), &readfds);
            ConnectionToServer->GetSSock()->ShutDown();
            ConnectionToServer->GetSSock()->Close();
        }
        std::printf("TCPClientNetManagerWorkerIOS StopWork\n");
    }
}
