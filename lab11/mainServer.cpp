#include <iostream>
#include <cstring>  
#include <thread>
#include <ws2tcpip.h> 
#include "UDPServer.h"
#define PORT 8888  
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define BUFLEN 512

void handleClient(UDPServer& server) {
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);
    char buf[BUFLEN];
    char ipStr[INET_ADDRSTRLEN];
    const char* prompt = "Enter message: ";

    while (true) {
        int receivedBytes = server.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
        if (receivedBytes > 0) {
            buf[receivedBytes] = '\0'; 
            inet_ntop(AF_INET, &si_other.sin_addr, ipStr, INET_ADDRSTRLEN);

            std::cout << "Received packet from " << ipStr << ":" << ntohs(si_other.sin_port) << std::endl;
            std::cout << "Data: " << buf << std::endl;

           
            std::cout << "Sending response: " << prompt << std::endl;
            int sentBytes = server.SendDatagram(prompt, strlen(prompt), (struct sockaddr*)&si_other, slen);
            if (sentBytes == -1) {
                std::cerr << "Failed to send response. Error code: " << WSAGetLastError() << std::endl;
            }
        }
        else {
            std::cerr << "Failed to receive data. Error code: " << WSAGetLastError() << std::endl;
        }
    }
}


int main() {
    WSADATA wsa;
    SOCKET serverSock;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFLEN];
    int slen = sizeof(clientAddr);


    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return 1;
    }


    serverSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;


    if (bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";
    while (true) {
        int receivedBytes = recvfrom(serverSock, buffer, BUFLEN, 0, (struct sockaddr*)&clientAddr, &slen);
        if (receivedBytes == SOCKET_ERROR) {
            std::cerr << "recvfrom failed with error: " << WSAGetLastError() << std::endl;
            continue;
        }

        buffer[receivedBytes] = '\0';
        std::cout << "Received message: " << buffer << std::endl;


        const char* response = "Message received";
        sendto(serverSock, response, strlen(response), 0, (struct sockaddr*)&clientAddr, slen);
    }

    closesocket(serverSock);
    WSACleanup();
    return 0;
}
