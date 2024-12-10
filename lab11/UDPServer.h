#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#define BUFLEN 1024 

class UDPServer {
public:
    UDPServer(unsigned short port);
    ~UDPServer();

    int RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen);
    int SendDatagram(const char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen);

private:
    SOCKET s;
    struct sockaddr_in si_server;
};

#endif
