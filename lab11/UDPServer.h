#pragma once
#include <winsock2.h>

class UDPServer {
public:
 
    UDPServer(SOCKET socket);

 
    UDPServer();

    ~UDPServer();  

    int Bind(struct sockaddr* addr, int addrlen);
    int SendDatagram(const char* buf, int len, struct sockaddr* addr, int addrlen);
    int RecvDatagram(char* buf, int len, struct sockaddr* addr, int* addrlen);

private:
    SOCKET serverSock; 
};
