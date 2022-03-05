#include <iostream>
#include "customer_functoins.h"
#include "network.h"

int main()
{
    windows_init();
    sockaddr_in saddr = saddr_init();
    SOCKET s = create_socket();
    int u = connect(s, (sockaddr*)&saddr,sizeof(sockaddr));
    if (u == SOCKET_ERROR) {
        std::cerr << "Error client: " << WSAGetLastError();
    }

    int row = 10;

    int column = 10;

    std::vector<std::vector<char>> customer_field(row, std::vector<char>(column));
    std::vector<std::vector<char>> enemy_field(row, std::vector<char>(column));
    customer_field = InitField(row, column);
    enemy_field = InitField(row, column);
    ShowField(customer_field, row, column);
    ArrangeShips(customer_field, row, column, AlgorithArrangeShips);

    void Game();

	return 0;
}