#include "UDPSocket.h"

int UDPSocket::WSAInit() {
    static unsigned int count = 0;
    if (count++)
        return 0;

#ifdef WIN32
    WSADATA wsa;
    printf("\nInitializing Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return -1;
    }
    printf("Initialized.\n");
#endif 
    return 0;
}

UDPSocket::UDPSocket() {
    WSAInit();

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == SOCKET_ERROR) {
        printf("socket() failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}

UDPSocket::~UDPSocket() {
    if (s != INVALID_SOCKET) {
        closesocket(s);
        WSACleanup();
    }
}

int UDPSocket::SendDatagram(const char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen) {
    if (sendto(s, msg, (int)msglen, 0, si_dest, slen) == SOCKET_ERROR) {
        printf("sendto() failed with error code : %d", WSAGetLastError());
        return -1;
    }
    return 0;
}

int UDPSocket::RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen) {
    int received_len = recvfrom(s, buf, buflen - 1, 0, si_dest, slen);
    if (received_len == SOCKET_ERROR) {
        printf("recvfrom() failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    buf[received_len] = '\0';
    return 0;
}
