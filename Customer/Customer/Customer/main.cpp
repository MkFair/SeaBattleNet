#include <iostream>
#include "customer_functoins.h"
#include "network.h"


extern const int ROW;

extern const int COLUMN;

int main()
{
    windows_init();
    sockaddr_in saddr = saddr_init();
    SOCKET s = create_socket();
    int u = connect(s, (sockaddr*)&saddr,sizeof(sockaddr));
    if (u == SOCKET_ERROR) {
        std::cerr << "Error client: " << WSAGetLastError();
    }

    std::vector<std::vector<char>> customer_field(ROW, std::vector<char>(COLUMN));
    std::vector<std::vector<char>> enemy_field(ROW, std::vector<char>(COLUMN));
    customer_field = InitField();
    enemy_field = InitField();
    ShowField(customer_field);
    ArrangeShips(customer_field, AlgorithArrangeShips);

    void Game();

	return 0;
}