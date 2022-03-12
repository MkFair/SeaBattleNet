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
#define TOTAL_COUNT_SHIPS 2

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
    END_GAME = 5,
    START_GAME = 6,
    CHECK_STATE = 7,
    FIRE = 8,
    PLAYER_STEP = 9,
    GAME_PROCESS = 10,
};

short count_deck_calculate(std::pair<short, short> min_pos, std::pair<short, short> max_pos) {
    if (min_pos.first == max_pos.first)
        return abs(min_pos.second-max_pos.second);
    if (min_pos.second == max_pos.second)
        return abs(min_pos.first - max_pos.first);
}
bool is_success_hit(std::vector<Ship> ships,short x, short y) {
    for (auto ship : ships) {
        if (ship.min_pos.first == ship.max_pos.first and x == ship.max_pos.first) {
            if (ship.min_pos.second < y < ship.max_pos.second)
                return true;
        }
        else if(ship.min_pos.second == ship.max_pos.second and y == ship.max_pos.second){
            if(ship.min_pos.first < x < ship.max_pos.first)
                return true;
        }
    }
    return false;
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
void send_packet(SOCKET s, PacketTypes packet_type, std::vector<char>data) {
    std::stringstream ss;
    std::vector<char> raw_packet;
    raw_packet.resize(sizeof(short));
    ss.write((char*)&packet_type, sizeof(short));
    ss.read(raw_packet.data(), sizeof(short));
    if (!data.empty())
        raw_packet.insert(raw_packet.end(), data.begin(), data.end());
    for (int y = 0; y < 100; y++)
        raw_packet.push_back('s');
    
    int size = send(s, raw_packet.data(), raw_packet.size(), 0);
    std::cout << "-----------------------------------------\nI send packet size " << raw_packet.size()<<"="<< size << std::string(raw_packet.begin(), raw_packet.end()) << std::endl;
    std::cout << "-----------------------------------------\n";
}

void client(SOCKET s_cl,Game* g) {
    
    /*FD_SET fd_read;
    FD_ZERO(&fd_read);
    FD_SET(s_cl, &fd_read);
    */
    bool is_close = false;
    std::vector<char> buffer;
    buffer.resize(1024);
    int recv_size;
    std::cout << "Socket- " << s_cl << std::endl;
    while (!is_close) {
        std::cout << "Enter loop" << std::endl;
       /* int count = select(0, &fd_read, 0, 0, 0); */
        recv_size = 0;
        buffer.resize(1024);
        recv_size = recv(s_cl, buffer.data(), buffer.size(), 0);
        std::cout << "Recv bytes from socket- "<< s_cl<<": " << recv_size<<WSAGetLastError() << std::endl;
        /*switch (count) {
        case 0:
            break;
        case -1:
            break;
        default:
            */
        
            if (recv_size == -1) is_close = true;
            if (recv_size > 0) {

                std::string bufstr(buffer.begin(), buffer.end());
                std::cout << "Client send me next data:" << bufstr << " with length = " << recv_size << std::endl;

                short type = 0;
                std::stringstream ss;
                ss.write(buffer.data(), sizeof(short));
                ss.read((char*)&type, sizeof(short));
                switch (type) {
                    //std::cout << "Send state " << type << std::endl;
                case PacketTypes::FIRE: {
                        ss.write(buffer.data(), sizeof(short)*2);
                        short x = 0, y = 0;
                        ss.seekg(sizeof(short));
                        ss.read((char*)&x, sizeof(short));
                        ss.seekg(sizeof(short) * 2);
                        ss.read((char*)&y, sizeof(short));
                        buffer.erase(buffer.begin(), buffer.begin()+sizeof(short)*2);
                        buffer.erase(buffer.begin() + sizeof(short) * 2, buffer.end());
                        std::cout << "Packet recv: Fire by pos " << x << ":" << y << std::endl;
                        if (g->player_tern_id == 1) {
                            send_packet(g->players.first.s, PacketTypes::OTHER_MOVE, buffer);
                            send_packet(g->players.second.s, PacketTypes::CAN_MOVE, buffer);
                            g->player_tern_id = 2;
                            std::cout << "Packet send: second CAN_MOVE " << x << ":" << y << std::endl;
                        }
                        else {
                            send_packet(g->players.first.s, PacketTypes::CAN_MOVE, buffer);
                            send_packet(g->players.second.s, PacketTypes::OTHER_MOVE, buffer);
                            std::cout << "Packet send: second CAN_MOVE " << x << ":" << y << std::endl;
                            g->player_tern_id = 1;
                        }
                    }
                    break;
                
                case PacketTypes::ADD_SHIPS:
                    if (g->current_state == GameStates::ARRANGEMENT) {
                        std::cout << "Packet recv: Adding ship" << std::endl;
                        buffer.erase(buffer.begin(), buffer.begin() + sizeof(short));
                        std::cout << "After resize data" << buffer.size() << std::endl;
                        Ship sp = from_raw_data(buffer);
                        if (g->players.first.s == s_cl) {
                            g->players.first.ships.push_back(sp);
                        }
                        else {
                            g->players.second.ships.push_back(sp);
                        }
                        //std::cout << "Client send me next position ship: x1=" << sp.min_pos.first << " y1=" << sp.min_pos.second << " x2=" << sp.max_pos.first << " y2=" << sp.max_pos.second << std::endl;
                        short count_ships = g->players.first.ships.size() + g->players.second.ships.size();
                        if (count_ships == TOTAL_COUNT_SHIPS) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));
                            send_packet(g->players.first.s, PacketTypes::CAN_MOVE, std::vector<char>());
                            send_packet(g->players.second.s, PacketTypes::OTHER_MOVE, std::vector<char>());
                            
                            //send_packet(g->players.second.s,PacketTypes::START_GAME,std::vector<char>());
                            g->current_state = GameStates::RUNNING;
                            std::cout << "START_GAME" << std::endl;
                        }

                    }
                    break;
                case PacketTypes::WAIT_PLAYER: {
                    short type = (g->count_players == 1) ? PacketTypes::WAIT_PLAYER : PacketTypes::ARRANGEMENT_SHIPS;
                    send(s_cl, (char*)&type, sizeof(short), 0);
                }
                                             break;
                case PacketTypes::CHECK_STATE:

                    /*short state = PacketTypes::OTHER_MOVE;
                    if (g->current_state == GameStates::RUNNING) {
                        if (g->player_tern_id == 1 and g->players.first.s == s_cl) {
                            state = PacketTypes::CAN_MOVE;
                        }
                        if (g->player_tern_id == 2 and g->players.second.s == s_cl) {
                            state = PacketTypes::CAN_MOVE;
                        }
                    }
                    std::cout << "Send state " << state << std::endl;
                    send(s_cl, (char*)&state, sizeof(short), 0);*/
                    break;
                }
                
            //}
            }
            buffer.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
    game.player_tern_id = 1;
    while ((s_cl = accept(sock, (sockaddr*)&saddr_cl, &saddr_len)) != INVALID_SOCKET) {
        std::cout << "Accept new client" << std::endl;
        
        Player pl;
        pl.s = s_cl;
        int current_player_index = 0;
        if (game.count_players) {
            game.players.second = pl;
            //game.players.second.s
            //известим игроков о старте расстановки 
            arrangement_start(game.players.first.s);
            arrangement_start(game.players.second.s);
            game.current_state = GameStates::ARRANGEMENT;
            current_player_index = 1;
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