#include <iostream>
#include <cstring>  
#include <thread>
#include <ws2tcpip.h> 
#include "UDPServer.h"
#define PORT 8888  

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

         
            server.SendDatagram(prompt, strlen(prompt), (struct sockaddr*)&si_other, slen);
        }
    }
}

int main(int argc, char* argv[]) {
    unsigned short srvport = (argc == 1) ? PORT : atoi(argv[1]);
    UDPServer server(srvport);

    std::thread clientThread(handleClient, std::ref(server));
    clientThread.detach(); 

    std::cout << "Server is running on port " << srvport << "..." << std::endl;

    while (true) {

        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }

    return 0;
}
