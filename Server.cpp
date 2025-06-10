#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
std::mutex socketMutex;
std::mutex chatHistoryMutex;
std::vector<SOCKET> SocketVector;
std::vector<std::string> chatHistory;

void communication(SOCKET socket, std::vector<SOCKET>& SocketVector, std::vector<std::string>& chatHistory) {
    char buffer[200] = {0};
    string userName;
    string separator = " : ";

    
    int bytes = recv(socket, buffer, sizeof(buffer), 0);
    if (bytes <= 0) {
        printf("USER_NAME - ERROR\n");
        closesocket(socket);
        return;
    }
    userName = buffer;
    printf("USER_NAME: %s\n", userName.c_str());

    
    {
        std::lock_guard<std::mutex> lock(chatHistoryMutex);
        for (const auto& msg : chatHistory) {
            std::string msgWithNewline = msg + "\n";
            send(socket, msgWithNewline.c_str(), msgWithNewline.size(), 0);
        }
    }

    
    while (true) {
        bytes = recv(socket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            printf("RECEIVE - ERROR\n");
            break;
        }
        std::string message(buffer);
        std::string fullMsg = userName + separator + message;
        printf("%s\n", fullMsg.c_str());

        
        {
            std::lock_guard<std::mutex> lock(chatHistoryMutex);
            chatHistory.push_back(fullMsg);
        }

    
        {
            std::lock_guard<std::mutex> lock(socketMutex);
            for (SOCKET s : SocketVector) {
                if (s != socket) {
                    std::string msgWithNewline = fullMsg + "\n";
                    send(s, msgWithNewline.c_str(), msgWithNewline.size(), 0);
                }
            }
        }
    }

    closesocket(socket);
    
    {
        std::lock_guard<std::mutex> lock(socketMutex);
        SocketVector.erase(std::remove(SocketVector.begin(), SocketVector.end(), socket), SocketVector.end());
    }
}

int main() {
    std::vector<SOCKET> SocketVector;
    std::vector<std::string> chatHistory;
    std::vector<std::thread> ThreadVector;

    WSADATA wsaData;
    int wsaDatares = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaDatares != 0) {
        printf("WSA - ERROR\n");
        return 1;
    }
    printf("WSA - SUCCES\n");

    // socket TCP, ipv4
    SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (soc == INVALID_SOCKET) {
        printf("SOCKET - ERROR %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("SOCKET - SUCCES\n");

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(55555);

    if (bind(soc, reinterpret_cast<SOCKADDR*>(&service), sizeof(service)) == SOCKET_ERROR) {
        printf("BIND - ERROR\n");
        closesocket(soc);
        WSACleanup();
        return 1;
    }
    printf("BIND - SUCCES\n");

    if (listen(soc, 1) == SOCKET_ERROR) {
        printf("LISTENER - ERROR\n");
        closesocket(soc);
        WSACleanup();
        return 1;
    }
    printf("LISTENER - SUCCES\n");

    while (true) {
        SOCKET acceptS = accept(soc, NULL, NULL);
        if (acceptS == INVALID_SOCKET) {
            printf("ACCEPT - ERROR\n");
            continue;
        }
        printf("NEW CONNECTION\n");
        {
            std::lock_guard<std::mutex> lock(socketMutex);
            SocketVector.push_back(acceptS);
        }
        ThreadVector.emplace_back([&]() { communication(acceptS, SocketVector, chatHistory); });
    }

    closesocket(soc);
    WSACleanup();
    return 0;
}
