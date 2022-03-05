#pragma once
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#define LISTEN_PORT 5445

WSADATA windows_init();
sockaddr_in saddr_init();
SOCKET create_socket();