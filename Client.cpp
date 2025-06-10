#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>
#include <string>
#include <vector>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

void listening(SOCKET socket) {
    char buffer[400] = {0};
    int pos = 0;
    while (true) {
        int bytes = recv(socket, buffer + pos, sizeof(buffer) - pos - 1, 0);
        if (bytes <= 0) {
            printf("RECEIVE - ERROR\n");
            break;
        }
        pos += bytes;
        buffer[pos] = '\0'; 

        char* msgStart = buffer;
        char* msgEnd;
        while ((msgEnd = strchr(msgStart, '\n')) != nullptr) {
            *msgEnd = '\0';
            printf("%s\n", msgStart);
            msgStart = msgEnd + 1;
        }
       
        if (msgStart != buffer) {
            int remaining = pos - (msgStart - buffer);
            memmove(buffer, msgStart, remaining);
            pos = remaining;
        }
    }
    closesocket(socket);
}

int main() {
    vector<thread> ThreadVector;
    string name;
    char name_tab[200] = {0};
    cout << "ENTER NAME:";
    getline(cin, name);
    strcpy_s(name_tab, sizeof(name_tab), name.c_str());

    WSADATA wsaData;
    int wsaDatares = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaDatares != 0) {
        printf("WSA - ERROR\n");
        return 1;
    }
    printf("WSA - SUCCES\n");

    SOCKET c_soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (c_soc == INVALID_SOCKET) {
        printf("SOCKET - ERROR %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("SOCKET - SUCCES\n");

    sockaddr_in c_service;
    c_service.sin_family = AF_INET;
    c_service.sin_addr.s_addr = inet_addr("127.0.0.1");
    c_service.sin_port = htons(55555);

    if (connect(c_soc, (SOCKADDR*)&c_service, sizeof(c_service)) == SOCKET_ERROR) {
        printf("CONNECT - ERROR - %d\n", WSAGetLastError());
        closesocket(c_soc);
        WSACleanup();
        return 1;
    }
    printf("CONNECT - SUCCES\n");
    send(c_soc, name_tab, strlen(name_tab) + 1, 0);
    ThreadVector.emplace_back([&]() { listening(c_soc); });

    while (true) {
        char buffer[200] = {0};
        cin.getline(buffer, 200);
        int bytes = send(c_soc, buffer, strlen(buffer) + 1, 0);
        if (bytes == SOCKET_ERROR) {
            printf("SEND - ERROR\n");
            break;
        }
    }
    closesocket(c_soc);
    WSACleanup();
    return 0;
}
