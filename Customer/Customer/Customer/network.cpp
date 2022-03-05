#include "network.h"

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

SOCKET create_socket() {
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        wprintf(L"Socket create failed with error: %ld\n", WSAGetLastError());
    }
    return s;
}

std::vector<char> to_raw_coordinate(ShipPosition sp) {
    std::vector<char> raw_data;
    raw_data.resize(sizeof(short) * 4);
    std::cout << "encode size " << raw_data.size();
    std::stringstream ss;
    ss.write((char*)&sp.min_pos.first, sizeof(short));
    ss.write((char*)&sp.min_pos.second, sizeof(short));
    ss.write((char*)&sp.max_pos.first, sizeof(short));
    ss.write((char*)&sp.max_pos.second, sizeof(short));
    
    ss.read(raw_data.data(), raw_data.size());
    return raw_data;
}


//Передача данных о корабле на сервер
// param s сетевой сокет клиента
// param ship_info список координат палуб корабля
void add_ship(SOCKET s,std::vector<std::vector<int>> ship_info) {
    std::pair<short, short> min_pos,max_pos;
    min_pos = { ship_info[0][0],ship_info[0][1] };
    max_pos = { 0,0 };
    //вычисляем максимальную и минимальную точку корабля
    for (auto v_pos : ship_info) {
        if(v_pos[0]< min_pos.first)
            min_pos.first = v_pos[0];
        if (v_pos[1] < min_pos.second)
            min_pos.second = v_pos[1];
        if (v_pos[0] > max_pos.first)
            max_pos.first = v_pos[0];
        if (v_pos[1] > max_pos.second)
            max_pos.second = v_pos[1];
    }
    std::cout << "I send next position "<< min_pos.first<<":"<< min_pos.second;
    ShipPosition sp = { min_pos,max_pos };
    std::vector<char> raw_data = to_raw_coordinate(sp);
    send(s, raw_data.data(), raw_data.size(), 0);
}