#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib")

#define BUFLEN 1024 

class UDPSocket {
protected:
    SOCKET s;

public:
    static int WSAInit();

    UDPSocket();
    virtual ~UDPSocket();

    int SendDatagram(const char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen);
    int RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen);
};
