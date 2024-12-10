#include <iostream>
#include <sstream>  
#include "UDPSocket.h"
#include <cstring>  
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 8888
#define BUFLEN 512

int main() {
    WSADATA wsa;
    SOCKET clientSock;
    struct sockaddr_in serverAddr;
    char message[BUFLEN];
    char buffer[BUFLEN];
    int slen = sizeof(serverAddr);

   
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return 1;
    }

 
    clientSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }


    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    while (true) {
        std::cout << "Enter message: ";
        std::cin.getline(message, BUFLEN);

 
        if (sendto(clientSock, message, strlen(message), 0, (struct sockaddr*)&serverAddr, slen) == SOCKET_ERROR) {
            std::cerr << "sendto failed with error: " << WSAGetLastError() << std::endl;
            continue;
        }

     
        int receivedBytes = recvfrom(clientSock, buffer, BUFLEN, 0, (struct sockaddr*)&serverAddr, &slen);
        if (receivedBytes == SOCKET_ERROR) {
            std::cerr << "recvfrom failed with error: " << WSAGetLastError() << std::endl;
        }
        else {
            buffer[receivedBytes] = '\0';
            std::cout << "Received from server: " << buffer << std::endl;
        }
    }

    closesocket(clientSock);
    WSACleanup();
    return 0;
}
