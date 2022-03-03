#include <iostream>
#include "customer_functoins.h"

int main()
{
    int row = 10;

    int column = 10;

    std::vector<std::vector<char>> customer_field(row, std::vector<char>(column));
    std::vector<std::vector<char>> enemy_field(row, std::vector<char>(column));
    customer_field = InitField(row, column);
    enemy_field = InitField(row, column);
    ShowField(customer_field, row, column);
    ArrangeShips(customer_field, row, column);

    void Game();

	return 0;
}