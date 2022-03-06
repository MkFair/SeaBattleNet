#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "server_functions.h"

#define LISTEN_PORT 5445

struct ShipPosition {
    std::pair<short, short> min_pos, max_pos;
};

ShipPosition from_raw_data(std::vector<char>raw_data) {
    std::stringstream ss;
    raw_data.resize(sizeof(short) * 4);
    std::cout << "raw data " << raw_data.data();
    ss.write(raw_data.data(), raw_data.size());
    ShipPosition sp;
    ss.seekg(0);
    //ss>>sp.min_pos.first;
    ss.read((char*)&sp.min_pos.first, sizeof(short));
    ss.seekg(sizeof(short));
    std::cout << "tell size " << sp.min_pos.first;
    ss.read((char*)&sp.min_pos.second, sizeof(short));
    ss.seekg(sizeof(short)*2);
    
    ss.read((char*)&sp.max_pos.first, sizeof(short));
    ss.seekg(sizeof(short)*3);
    
    ss.read((char*)&sp.max_pos.second, sizeof(short));
    return sp;
}

WSADATA windows_init() {
    WSADATA wsadata;
    auto iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);

    }
    return wsadata;
}

sockaddr_in saddr_init() {
    sockaddr_in sa;
    in_addr ia;

    inet_pton(AF_INET, "127.0.0.1", &ia);

    sa.sin_addr.s_addr = ia.S_un.S_addr;
    sa.sin_family = AF_INET;

    sa.sin_port = htons(LISTEN_PORT);
    return sa;
}



int main()
{

    SOCKET sock;
    sockaddr_in saddr;


    sockaddr_in saddr_cl;
    int saddr_len = sizeof(sockaddr);

    WSADATA wsadata = windows_init();
    


    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cout << "Error create soket";
        return 0;
    }

    saddr = saddr_init();



    int status = bind(sock, (sockaddr*)&saddr, sizeof(sockaddr));
    if (status == SOCKET_ERROR) {
        std::cout << "Error soket bind";
        return 0;
    }

    if (listen(sock, 5) == SOCKET_ERROR) {
        std::cout << "Error soket listen";
        return 0;
    }

    SOCKET s_cl;
    while ((s_cl = accept(sock, (sockaddr*)&saddr_cl, &saddr_len)) != INVALID_SOCKET) {
        std::cout << "Accept new client" << std::endl;

        std::vector<char> buf;
        buf.resize(1024);

        int size = recv(s_cl, buf.data(), 1024, 0);
        std::string bufstr(buf.begin(), buf.end());
        std::cout << "Client send me next data:" << bufstr << std::endl;

        ShipPosition sp = from_raw_data(buf);
        std::cout << "Client send me next position ship: x1=" << sp.min_pos.first <<" y1=" << sp.min_pos.second << "x2=" << sp.max_pos.first << " y2=" << sp.max_pos.second << std::endl;

        std::string responce = "HELLO KITTI";
        send(s_cl, responce.data(), responce.size(), 0);

        std::cout << "New client disconnected" << std::endl;
        closesocket(s_cl);

    }

    closesocket(sock);

    WSACleanup();

    return 0;
}