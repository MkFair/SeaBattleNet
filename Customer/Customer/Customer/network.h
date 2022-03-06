#pragma once
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <sstream>
#define LISTEN_PORT 5445

struct ShipPosition {
	std::pair<short, short> min_pos, max_pos;
};

void add_ship(SOCKET s, std::vector<std::vector<int>>);
std::vector<char> to_raw_coordinate(ShipPosition);
WSADATA windows_init();
sockaddr_in saddr_init();
SOCKET create_socket();