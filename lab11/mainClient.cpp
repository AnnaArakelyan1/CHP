#include <iostream>
#include <sstream>  
#include "UDPSocket.h"
#include <cstring>  
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char* argv[])
{
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];

    unsigned short srv_port = 8888;
    char srv_ip_addr[40] = "127.0.0.1"; 

    if (argc == 3) {
     
        strncpy_s(srv_ip_addr, argv[1], sizeof(srv_ip_addr) - 1);
        srv_ip_addr[sizeof(srv_ip_addr) - 1] = '\0'; 
        srv_port = static_cast<unsigned short>(std::stoi(argv[2]));
    }
    else {
        std::cout << "Usage: " << argv[0] << " <Server IP> <Server Port>" << std::endl;
        return -1;
    }

    UDPSocket client_sock;
    memset((char*)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(srv_port);

    if (inet_pton(AF_INET, srv_ip_addr, &si_other.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported: " << srv_ip_addr << std::endl;
        return -1;
    }

    std::cout << "Client will connect to server at " << srv_ip_addr << ":" << srv_port << std::endl;

    while (true) {
        std::cout << "\nEnter message: ";

     
        if (!std::cin.good()) {
            std::cerr << "Input stream error. Exiting." << std::endl;
            break;
        }

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Empty message entered. Please try again." << std::endl;
            continue;
        }

      
        strncpy_s(message, input.c_str(), BUFLEN - 1);
        message[BUFLEN - 1] = '\0';

        std::cout << "Sending message: " << message << std::endl;


        client_sock.SendDatagram(message, strlen(message), (struct sockaddr*)&si_other, slen);

   
        memset(buf, '\0', BUFLEN);
        int receivedBytes = client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);

        if (receivedBytes > 0) {
            buf[receivedBytes] = '\0';  
            std::cout << "Received from server: " << buf << std::endl;
        }
        else {
            std::cerr << "No response received or an error occurred." << std::endl;
        }
    }

    return 0;
}
