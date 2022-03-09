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
        return 1;
    }
    std::cout << "Wait connect other player ...";
    wait_player(s);
    //тестовая отправка координат корабля в начале игры
    std::vector<std::vector<int>> posv{ {1,2}, {2,2}, {5,3} };
    add_ship(s, posv);

    std::vector<std::vector<char>> customer_field(ROW, std::vector<char>(COLUMN));
    std::vector<std::vector<char>> enemy_field(ROW, std::vector<char>(COLUMN));
    customer_field = InitField();
    enemy_field = InitField();
    ShowField(customer_field);
    

    ArrangeONEShip(customer_field, AlgorithmArrangeShips);// A FUNC ONLY FOR TEST
    //ArrangeShips(customer_field, AlgorithmArrangeShips);// A REAL FUNC


    Game(customer_field, enemy_field, HaveHitTheTarget, AreThereAnySheeps);
    Results(customer_field, enemy_field, AreThereAnySheeps);

	return 0;
}