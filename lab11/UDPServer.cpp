#include "UDPServer.h"
#include <stdexcept>

UDPServer::UDPServer(unsigned short port) {

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }


    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        throw std::runtime_error("Socket creation failed");
    }

 
    si_server.sin_family = AF_INET;
    si_server.sin_port = htons(port);
    si_server.sin_addr.s_addr = INADDR_ANY;


    if (bind(s, (struct sockaddr*)&si_server, sizeof(si_server)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind failed");
    }
}

UDPServer::~UDPServer() {
    closesocket(s);
    WSACleanup();
}

int UDPServer::RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen) {
    int receivedBytes = recvfrom(s, buf, buflen, 0, si_dest, slen);
    if (receivedBytes == SOCKET_ERROR) {
        throw std::runtime_error("recvfrom failed");
    }
    return receivedBytes;
}

int UDPServer::SendDatagram(const char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen) {
    int sentBytes = sendto(s, msg, msglen, 0, si_dest, slen);
    if (sentBytes == SOCKET_ERROR) {
        throw std::runtime_error("sendto failed");
    }
    return sentBytes;
}
