#pragma once
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <sstream>
#include <chrono>
#include <thread>
#define LISTEN_PORT 5445
enum PacketTypes {
    UNRECOG = 0,
    ARRANGEMENT_SHIPS = 1,
    ADD_SHIPS = 2,
    WAIT_PLAYER = 11,
    CAN_MOVE = 3,
    OTHER_MOVE = 4,
    END_GAME = 5,
    START_GAME = 6,
    CHECK_STATE = 7,
    FIRE = 8
};
enum GameStates {
    WAIT = 1,
    ARRANGEMENT = 2,
    RUNNING = 3,
    END = 5
};
struct ShipPosition {
	std::pair<short, short> min_pos, max_pos;
};
void send_packet(SOCKET s, PacketTypes packet_type, std::vector<char>data);
void add_ship(SOCKET s, std::vector<std::vector<int>>);
std::pair<PacketTypes, std::vector<char>> recv_packet(SOCKET s);
bool wait_event(SOCKET s, PacketTypes);
//void wait_player(SOCKET s, std::chrono::milliseconds delay);
PacketTypes wait_start_game(SOCKET s, std::chrono::milliseconds delay = std::chrono::milliseconds(100));
std::vector<char> to_raw_coordinate(ShipPosition);
WSADATA windows_init();
sockaddr_in saddr_init();
SOCKET create_socket();
void wait_player(SOCKET s, std::chrono::milliseconds delay = std::chrono::milliseconds(100));
bool is_wait_state(SOCKET s);
void send_firing_zone(SOCKET s, short x, short y);
std::pair<PacketTypes, std::vector<char>> check_state(SOCKET s);

std::pair<short, short> wait_other_player(SOCKET s);