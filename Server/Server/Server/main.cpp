#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <utility>
#include <thread>
#include "server_functions.h"

#define LISTEN_PORT 5445

struct Ship {
    std::pair<short, short> min_pos, max_pos;
    short deck_count;
};

struct Player {
    SOCKET s;
    std::vector<Ship> ships;
};

enum GameStates {
    WAIT = 1,
    ARRANGEMENT = 2,
    RUNNING = 3,
    END = 5
};

struct Game {
    std::pair<Player, Player> players;
    short player_tern_id;
    GameStates current_state;
    short count_players;
};

enum PacketTypes {
    ARRANGEMENT_SHIPS = 1,
    ADD_SHIPS = 2,
    WAIT_PLAYER = 11,
    CAN_MOVE = 3,
    OTHER_MOVE = 4,
    END_GAME = 5
};

short count_deck_calculate(std::pair<short, short> min_pos, std::pair<short, short> max_pos) {
    if (min_pos.first == max_pos.first)
        return abs(min_pos.second-max_pos.second);
    if (min_pos.second == max_pos.second)
        return abs(min_pos.first - max_pos.first);
}

Ship from_raw_data(std::vector<char>raw_data) {
    std::stringstream ss;
    raw_data.resize(sizeof(short) * 4);
    ss.write(raw_data.data(), raw_data.size());
    Ship sp;
    ss.seekg(0);
    //ss>>sp.min_pos.first;
    ss.read((char*)&sp.min_pos.first, sizeof(short));
    ss.seekg(sizeof(short));
    ss.read((char*)&sp.min_pos.second, sizeof(short));
    ss.seekg(sizeof(short)*2);
    
    ss.read((char*)&sp.max_pos.first, sizeof(short));
    ss.seekg(sizeof(short)*3);
    
    ss.read((char*)&sp.max_pos.second, sizeof(short));
    sp.deck_count = count_deck_calculate(sp.min_pos, sp.max_pos);
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


void client(SOCKET s_cl,Game* g) {
    std::vector<char> buf;
    buf.resize(1024);
    int size = recv(s_cl, buf.data(), 1024, 0);
    while (size>0) {

        std::string bufstr(buf.begin(), buf.end());
        std::cout << "Client send me next data:" << bufstr << " with length = " << size << std::endl;

        short type = 0;
        std::stringstream ss;
        ss.write(buf.data(), sizeof(short));
        ss.read((char*)&type, sizeof(short));
        if (type == PacketTypes::ADD_SHIPS and g->current_state==GameStates::ARRANGEMENT) {
            std::cout << "Packet recv: Adding ship" << std::endl;
            buf.erase(buf.begin(), buf.begin() + sizeof(short));
            std::cout << "After resize data" << buf.size() << std::endl;
            Ship sp = from_raw_data(buf);
            std::cout << "Client send me next position ship: x1=" << sp.min_pos.first << " y1=" << sp.min_pos.second << " x2=" << sp.max_pos.first << " y2=" << sp.max_pos.second << std::endl;
        }
        if (type == PacketTypes::WAIT_PLAYER) {
            short type = (g->count_players == 1) ? PacketTypes::WAIT_PLAYER : PacketTypes::ARRANGEMENT_SHIPS;
            std::cout << "WAIT_PLAYER" <<std::endl;
            send(s_cl, (char*)&type, sizeof(short), 0);
        }
        buf.clear();
        size = recv(s_cl, buf.data(), 1024, 0);
    }
    std::string responce = "HELLO KITTI";
    send(s_cl, responce.data(), responce.size(), 0);

    std::cout << "New client disconnected" << std::endl;
    closesocket(s_cl);

}

void arrangement_start(SOCKET s) {
    short type = PacketTypes::ARRANGEMENT_SHIPS;
    int size = send(s, (char*)&type, sizeof(short), 0);
}


int main()
{

    SOCKET sock;
    sockaddr_in saddr;


    sockaddr_in saddr_cl;
    int saddr_len = sizeof(sockaddr);

    WSADATA wsadata = windows_init();
    
    std::vector<std::thread> clients_th;

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
    Game game;
    game.current_state = GameStates::WAIT;
    game.count_players=0;
    while ((s_cl = accept(sock, (sockaddr*)&saddr_cl, &saddr_len)) != INVALID_SOCKET) {
        std::cout << "Accept new client" << std::endl;
        
        Player pl;
        pl.s = s_cl;
        if (game.count_players) {
            game.players.second = pl;
            //game.players.second.s
            //известим игроков о старте расстановки 
            arrangement_start(game.players.first.s);
            arrangement_start(game.players.second.s);
            game.current_state = GameStates::ARRANGEMENT;
        }
        else {
            game.players.first = pl;
        }
        game.count_players++;
        clients_th.push_back(std::thread(client,s_cl,&game));

    }
    for (std::thread& th : clients_th) {
        if (th.joinable()) {
            th.join();
        }
    }
    closesocket(sock);

    WSACleanup();

    return 0;
}