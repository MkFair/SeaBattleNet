#include <iostream>
#include <vector>

std::vector<std::vector<char>> InitField(int rows, int columns)
{
	std::vector<std::vector<char>> my_field(10, std::vector<char>(10));

	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			my_field[i][j] = 'O';

		return my_field;
}

//for (int i = 1; i <= 10; ++i)
//std::cout << '\t' << i;
//std::cout << '\t';
//for (int i = 1; i <= 10; ++i)
//std::cout << '\t' << i;
//std::cout << std::endl;

void ShowField(const std::vector<std::vector<char>>& my_field, int rows, int columns)
{
	std::cout << "\tYOUR FIELD\t\t\t\tENEMY`S FIELD" << std::endl;

	for (int i = 0; i < rows; ++i)
	{
		std::cout << i + 1;
		for (int j = 0; j < columns; ++j)
			std::cout << '\t' << my_field[i][j];
		std::cout << std::endl;
	}
		

}