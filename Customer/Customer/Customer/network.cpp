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


//�������� ������ � ������� �� ������
// param s ������� ����� �������
// param ship_info ������ ��������� ����� �������
void add_ship(SOCKET s,std::vector<std::vector<int>> ship_info) {
    std::pair<short, short> min_pos,max_pos;
    min_pos = { ship_info[0][0],ship_info[0][1] };
    max_pos = { 0,0 };
    //��������� ������������ � ����������� ����� �������
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
void send_packet(SOCKET s, PacketTypes packet_type, std::vector<char>data) {
    std::stringstream ss;
    std::vector<char> raw_packet;
    raw_packet.resize(sizeof(short));
    ss.write((char*)&packet_type, sizeof(short));
    ss.read(raw_packet.data(), sizeof(short));
    if(!data.empty())
        raw_packet.insert(raw_packet.end(), data.begin(), data.end());
    std::cout << "I send packet size " << raw_packet.size() << std::endl;
    send(s, raw_packet.data(), raw_packet.size(), 0);
}
std::pair<PacketTypes,std::vector<char>> recv_packet(SOCKET s){
    std::vector<char> raw_packet;
    raw_packet.resize(1024);
    recv(s, raw_packet.data(), raw_packet.size(),0);
    std::stringstream ss;
    ss.write(raw_packet.data(), sizeof(short));
    PacketTypes type;
    ss.read((char*)&type,sizeof(short));
    raw_packet.erase(raw_packet.begin(), raw_packet.begin()+ sizeof(short));
    return std::pair<PacketTypes, std::vector<char>>(type, raw_packet);
}

bool is_wait_state(SOCKET s) {
    return wait_event(s, PacketTypes::ARRANGEMENT_SHIPS);
}
//�������� ����������� ������� ������
void wait_player(SOCKET s,std::chrono::milliseconds delay ) {
    while (is_wait_state(s)) {
        std::this_thread::sleep_for(delay);
    }
}

std::pair<PacketTypes, std::vector<char>> check_state(SOCKET s) {
    send_packet(s, PacketTypes::CHECK_STATE, std::vector<char>());
    return recv_packet(s);
}
//�������� ��������� ��������
void send_firing_zone(SOCKET s,short x,short y) {
    std::vector<char> data;
    std::stringstream ss;
    ss.write((char*)&x,sizeof(short));
    ss.write((char*)&y,sizeof(short));
    ss.read(data.data(), sizeof(short)*2);
    send_packet(s, PacketTypes::FIRE, data);
}
//�������� ��������� � ������ ����, ���������� PacketTypes
PacketTypes wait_start_game(SOCKET s, std::chrono::milliseconds delay ) {
    std::pair<PacketTypes, std::vector<char>> data = check_state(s);
    while (data.first!= PacketTypes::START_GAME) {
        std::this_thread::sleep_for(delay);
        data = check_state(s);
    }
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