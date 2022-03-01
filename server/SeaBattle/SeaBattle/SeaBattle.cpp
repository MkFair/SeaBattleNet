#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>

#define LISTEN_PORT 5445

//èíèöèàëèçèðóåì ñèñòåìó ñîâåòîâ äëÿ âèíäû
WSADATA windows_init() {
    WSADATA wsadata;
    auto iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);

    }
    return wsadata;
}
//çàïîëíÿåì ñòðóêòóðó ñ óêàçàíèåì ïîðòà è àäðåñà ðàáîòû
sockaddr_in saddr_init() {
    sockaddr_in sa;
    in_addr ia;
    //ïðåîáðàçóåì àäðåñ
    inet_pton(AF_INET, "127.0.0.1", &ia);

    sa.sin_addr.s_addr = ia.S_un.S_addr;
    sa.sin_family = AF_INET;
    //ïðåîáðàçóåì ïîðò
    sa.sin_port = htons(LISTEN_PORT);
    return sa;
}



int main()
{
    //ãëàâíûé ñîêåò-ðàçüåì ñåðâåðà
    SOCKET sock;
    sockaddr_in saddr;

    //äàííûå î ïîëüçîâàòåëå êîòîðûé ïîäêëþ÷èëñÿ
    sockaddr_in saddr_cl;
    int saddr_len = sizeof(sockaddr);



    WSADATA wsadata;
    auto iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);

    }

    //ñîçäàåì ñîêåò ïî ïðîòîêîëó tcp 
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cout << "Error create soket";
        return 0;
    }

    saddr = saddr_init();


    //ïðèâÿçûâàåì ïîðò ê ñîêåòó êàê áû ïðèìåíÿÿ íàñòðîéêè çàäàííûå saddr_init
    int status = bind(sock, (sockaddr*)&saddr, sizeof(sockaddr));
    if (status == SOCKET_ERROR) {
        std::cout << "Error soket bind";
        return 0;
    }
    //ãîâîðèì ïðîñëóøèâàòü ñîêåò-ðàçüåì, ÷òîáû ïîëó÷àòü ïîäêëþ÷åíèÿ êëèåíòîâ
    if (listen(sock, 5) == SOCKET_ERROR) {
        std::cout << "Error soket listen";
        return 0;
    }
    //ïîëó÷àåì ïîäêëþ÷åíèå êëèåíòà - ïðîãðàììà çàâèñàåò â îæèäàíèè êëèåíòà
    SOCKET s_cl;
    while ((s_cl = accept(sock, (sockaddr*)&saddr_cl, &saddr_len)) != INVALID_SOCKET) {
        std::cout << "Accept new client" << std::endl;

        std::vector<char> buf;
        buf.resize(1024);
        //ïîëó÷àåì äàííûå â âûäåëåííûé áóôåð - çàâèñàåò ïîêà íå ïîëó÷èò äàííûõ
        int size = recv(s_cl, buf.data(), 1024, 0);
        std::string bufstr(buf.begin(), buf.end());
        std::cout << "Client send me next data:" << bufstr << std::endl;


        //îòïðàâëÿåì îòâåò - âðåìåííî ïðîñòóþ ñòðîêó
        std::string responce = "HELLO KITTI";
        send(s_cl, responce.data(), responce.size(), 0);

        std::cout << "New client disconnected" << std::endl;
        closesocket(s_cl);

    }
    //ïðèíóäèòåëüíîå çàêðûòèå ñîêåòà - èíîãäà îáÿçàòåëüíàÿ ïðîöåäóðà
    closesocket(sock);

    WSACleanup();
}
