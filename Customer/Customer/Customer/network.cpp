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
    send_packet(s, PacketTypes::ADD_SHIPS, raw_data);
}
std::pair<short, short> wait_other_player(SOCKET s) {
    std::cout << "Wait other player ...";
    std::pair<PacketTypes, std::vector<char>>res = recv_packet(s);
    std::cout << "step ok" << std::endl;
    std::stringstream ss;
    ss.read(res.second.data(), sizeof(short)*2);
    std::pair<short, short> result = {0,0};
    ss.write((char*)&result.first,sizeof(short));
    ss.seekg(sizeof(short));
    ss.write((char*)&result.second,sizeof(short));
    return result;
}
void send_packet(SOCKET s, PacketTypes packet_type, std::vector<char>data) {
    std::stringstream ss;
    std::vector<char> raw_packet;
    raw_packet.resize(sizeof(short));
    ss.write((char*)&packet_type, sizeof(short));
    ss.read(raw_packet.data(), sizeof(short));
    if(!data.empty())
        raw_packet.insert(raw_packet.end(), data.begin(), data.end());
    for(int y=0;y<100;y++)
        raw_packet.push_back('s');
    int size = send(s, raw_packet.data(), raw_packet.size(), 0);
    std::cout  << std::dec << "I send packet size " << raw_packet.size()<< "-" << WSAGetLastError()<<"=" << size << "-" << std::string(raw_packet.begin(), raw_packet.end()) << std::endl;
}
std::pair<PacketTypes,std::vector<char>> recv_packet(SOCKET s){
    std::vector<char> raw_packet;
    raw_packet.resize(1024);
    short size = recv(s, raw_packet.data(), raw_packet.size(),0);
    std::cout << "I recv packet size " << size << std::string(raw_packet.begin(), raw_packet.end()) << std::endl;
    std::stringstream ss;
    ss.write(raw_packet.data(), sizeof(short));
    PacketTypes type = PacketTypes::UNRECOG;
    std::cout << ss.str()<<std::endl;
    ss.seekg(0);
    ss.read((char*)&type,sizeof(short));
    std::cout << std::hex<<type << std::endl;
    raw_packet.erase(raw_packet.begin(), raw_packet.begin()+ sizeof(short));
    return std::pair<PacketTypes, std::vector<char>>(type, raw_packet);
}

bool is_wait_state(SOCKET s) {
    return wait_event(s, PacketTypes::ARRANGEMENT_SHIPS);
}
//ожидание подключения второго игрока
void wait_player(SOCKET s,std::chrono::milliseconds delay ) {
    while (is_wait_state(s)) {
        std::this_thread::sleep_for(delay);
    }
}

std::pair<PacketTypes, std::vector<char>> check_state(SOCKET s) {
    send_packet(s, PacketTypes::CHECK_STATE, std::vector<char>());
    return recv_packet(s);
}
//отправка координат выстрела
void send_firing_zone(SOCKET s,short x,short y) {
    std::vector<char> data;
    data.resize(sizeof(short)*2);
    std::stringstream ss;
    ss.write((char*)&x,sizeof(short));
    ss.write((char*)&y,sizeof(short));
    ss.read(data.data(), sizeof(short)*2);
    send_packet(s, PacketTypes::FIRE, data);
}
//ожидание сообщения о старте игры, возвращает PacketTypes
PacketTypes wait_start_game(SOCKET s, std::chrono::milliseconds delay ) {
    std::pair<PacketTypes, std::vector<char>> data = recv_packet(s);// check_state(s);
    
    std::cout << "Start loop wait game start ..."<< (int)data.first << std::string(data.second.begin(), data.second.end() )<<std::endl;
    while (data.first!= PacketTypes::CAN_MOVE && data.first != PacketTypes::OTHER_MOVE) {
        std::this_thread::sleep_for(delay);
        data = recv_packet(s);
    }
    std::cout << "Start play game" << std::endl;
    PacketTypes result;
    std::stringstream ss;
    ss.write(data.second.data(),sizeof(short));
    ss.read((char*)&result,sizeof(short));
    return result;
}
bool wait_event(SOCKET s ,PacketTypes check_type) {
    short type;


    int size = recv(s, (char*)&type, sizeof(short), 0);
    if (size == sizeof(short) and type == check_type) {
        return false;
    }
    return true;

}