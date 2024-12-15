#include "UDPServer.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

UDPServer::UDPServer(SOCKET socket) : serverSock(socket) {}


UDPServer::UDPServer() {
    serverSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
    }
}


UDPServer::~UDPServer() {
    closesocket(serverSock);
}


int UDPServer::Bind(struct sockaddr* addr, int addrlen) {
    return bind(serverSock, addr, addrlen);
}


int UDPServer::SendDatagram(const char* buf, int len, struct sockaddr* addr, int addrlen) {
    return sendto(serverSock, buf, len, 0, addr, addrlen);
}


int UDPServer::RecvDatagram(char* buf, int len, struct sockaddr* addr, int* addrlen) {
    return recvfrom(serverSock, buf, len, 0, addr, addrlen);
}
