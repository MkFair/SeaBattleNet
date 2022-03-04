#include <iostream>
#include <vector>
#include "customer_functoins.h"

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
	//std::cout << "\tYOUR FIELD\t\t\t\tENEMY`S FIELD" << std::endl;
	std::cout << "\tYOUR FIELD" << std::endl;

	for (int i = 1; i <= columns; ++i)
	{
		if (i == 1) std::cout << "    " << i;
		else std::cout << "  " << i;
	}

	std::cout << std::endl;

	for (int i = 0; i < rows; ++i)
	{
		std::cout << i + 1;
		for (int j = 0; j < columns; ++j)
		{
			if (i != 9  && j == 0) std::cout << "   " << my_field[i][j];
			else std::cout << "  " << my_field[i][j];
		}
		std::cout << std::endl;
	}


}
bool AreCellsArrangedHorizontallySuccessively(std::vector<std::vector<int>> ship, int quantity_of_deck_)
{
	switch (quantity_of_deck_)
	{
		case 1: return true; break;
		case 2: if (ship[0][1] == ship[1][1] && (ship[0][1] + 1 == ship[1][1] || ship[0][1] - 1 == ship[1][1])) return true;
		case 3: if (ship[0][1] == ship[1][1] && ship[2][1] == ship[1][1]  && 
				   ((ship[0][0] + 1 == ship[1][0] && ship[0][0] + 2 == ship[2][0] )  ||  
					(ship[0][0] - 1 == ship[1][0] && ship[0][0] + 1 == ship[2][0] )  ||
					(ship[0][0] + 1 == ship[2][0] && ship[2][0] + 1 == ship[1][0] )  ||
					(ship[0][0] - 1 == ship[1][0] && ship[2][0] + 1 == ship[0][0] )  ||
					(ship[2][0] + 1 == ship[0][0] && ship[0][0] + 1 == ship[1][0] )  ||
					(ship[2][0] + 1 == ship[1][0] && ship[1][0] + 1 == ship[0][0]))) return true;
		case 4: if (ship[0][1] == ship[1][1] && ship[2][1] == ship[1][1] && ship[2][1] == ship[3][1] &&
				  ((ship[0][0] + 1 == ship[1][0] && ship[0][0] + 2 == ship[2][0] && ship[0][0] + 3 == ship[3][0]) ||
				   (ship[0][0] + 1 == ship[1][0] && ship[0][0] + 2 == ship[3][0] && ship[0][0] + 3 == ship[2][0]) ||
				   (ship[0][0] + 1 == ship[3][0] && ship[0][0] + 2 == ship[1][0] && ship[0][0] + 3 == ship[2][0]) ||
				   (ship[0][0] + 1 == ship[3][0] && ship[0][0] + 2 == ship[2][0] && ship[0][0] + 3 == ship[1][0]) ||
				   (ship[0][0] + 1 == ship[2][0] && ship[0][0] + 2 == ship[1][0] && ship[0][0] + 3 == ship[3][0]) ||
				   (ship[0][0] + 1 == ship[2][0] && ship[0][0] + 2 == ship[3][0] && ship[0][0] + 3 == ship[3][0]) ||

				   (ship[1][0] + 1 == ship[0][0] && ship[1][0] + 2 == ship[2][0] && ship[1][0] + 3 == ship[3][0]) ||
				   (ship[1][0] + 1 == ship[0][0] && ship[1][0] + 2 == ship[3][0] && ship[1][0] + 3 == ship[2][0]) ||
				   (ship[1][0] + 1 == ship[2][0] && ship[1][0] + 2 == ship[3][0] && ship[1][0] + 3 == ship[0][0]) ||
				   (ship[1][0] + 1 == ship[2][0] && ship[1][0] + 2 == ship[0][0] && ship[1][0] + 3 == ship[3][0]) ||
				   (ship[1][0] + 1 == ship[3][0] && ship[1][0] + 2 == ship[2][0] && ship[1][0] + 3 == ship[0][0]) ||
				   (ship[1][0] + 1 == ship[3][0] && ship[1][0] + 2 == ship[0][0] && ship[1][0] + 3 == ship[2][0]) ||

				   (ship[3][0] + 1 == ship[0][0] && ship[3][0] + 2 == ship[2][0] && ship[3][0] + 3 == ship[1][0]) ||
				   (ship[3][0] + 1 == ship[0][0] && ship[3][0] + 2 == ship[1][0] && ship[3][0] + 3 == ship[2][0]) ||
				   (ship[3][0] + 1 == ship[1][0] && ship[3][0] + 2 == ship[2][0] && ship[3][0] + 3 == ship[0][0]) ||
				   (ship[3][0] + 1 == ship[1][0] && ship[3][0] + 2 == ship[0][0] && ship[3][0] + 3 == ship[2][0]) ||
				   (ship[3][0] + 1 == ship[2][0] && ship[3][0] + 2 == ship[1][0] && ship[3][0] + 3 == ship[0][0]) ||
				   (ship[3][0] + 1 == ship[2][0] && ship[3][0] + 2 == ship[0][0] && ship[3][0] + 3 == ship[1][0]) ||

				   (ship[2][0] + 1 == ship[0][0] && ship[2][0] + 2 == ship[3][0] && ship[3][0] + 3 == ship[1][0]) ||
				   (ship[2][0] + 1 == ship[0][0] && ship[2][0] + 2 == ship[1][0] && ship[3][0] + 3 == ship[3][0]) ||
				   (ship[2][0] + 1 == ship[1][0] && ship[2][0] + 2 == ship[0][0] && ship[3][0] + 3 == ship[3][0]) ||
				   (ship[2][0] + 1 == ship[1][0] && ship[2][0] + 2 == ship[3][0] && ship[3][0] + 3 == ship[0][0]) ||
				   (ship[2][0] + 1 == ship[3][0] && ship[2][0] + 2 == ship[1][0] && ship[3][0] + 3 == ship[0][0]) ||
				   (ship[2][0] + 1 == ship[3][0] && ship[2][0] + 2 == ship[0][0] && ship[3][0] + 3 == ship[1][0]))) return true;
	}
	return false;
}

bool AreCellsArrangedVerticallySuccessively(std::vector<std::vector<int>> ship, int quantity_of_deck_)
{
	switch (quantity_of_deck_)
	{
		case 1: return true; break;
		case 2: if (ship[0][0] == ship[1][0] && (ship[0][1] + 1 == ship[1][1] || ship[0][1] - 1 == ship[1][1])) return true;
		case 3: if (ship[0][0] == ship[1][0] && ship[2][0] == ship[1][0] &&
				  ((ship[0][1] + 1 == ship[1][1] && ship[0][1] + 2 == ship[2][1]) ||
					(ship[0][1] - 1 == ship[1][1] && ship[0][1] + 1 == ship[2][1]) ||
					(ship[0][1] + 1 == ship[2][1] && ship[2][1] + 1 == ship[1][1]) ||
					(ship[0][1] - 1 == ship[1][1] && ship[2][1] + 1 == ship[0][1]) ||
					(ship[2][1] + 1 == ship[0][1] && ship[0][1] + 1 == ship[1][1]) ||
					(ship[2][1] + 1 == ship[1][1] && ship[1][1] + 1 == ship[0][1]))) return true;
		case 4: if (ship[0][0] == ship[1][0] && ship[2][0] == ship[1][0] && ship[2][0] == ship[3][0] &&
			      ((ship[0][1] + 1 == ship[1][1] && ship[0][1] + 2 == ship[2][1] && ship[0][1] + 3 == ship[3][1]) ||
					(ship[0][1] + 1 == ship[1][1] && ship[0][1] + 2 == ship[3][1] && ship[0][1] + 3 == ship[2][1]) ||
					(ship[0][1] + 1 == ship[3][1] && ship[0][1] + 2 == ship[1][1] && ship[0][1] + 3 == ship[2][1]) ||
					(ship[0][1] + 1 == ship[3][1] && ship[0][1] + 2 == ship[2][1] && ship[0][1] + 3 == ship[1][1]) ||
					(ship[0][1] + 1 == ship[2][1] && ship[0][1] + 2 == ship[1][1] && ship[0][1] + 3 == ship[3][1]) ||
					(ship[0][1] + 1 == ship[2][1] && ship[0][1] + 2 == ship[3][1] && ship[0][1] + 3 == ship[3][1]) ||

					(ship[1][1] + 1 == ship[0][1] && ship[1][1] + 2 == ship[2][1] && ship[1][1] + 3 == ship[3][1]) ||
					(ship[1][1] + 1 == ship[0][1] && ship[1][1] + 2 == ship[3][1] && ship[1][1] + 3 == ship[2][1]) ||
					(ship[1][1] + 1 == ship[2][1] && ship[1][1] + 2 == ship[3][1] && ship[1][1] + 3 == ship[0][1]) ||
					(ship[1][1] + 1 == ship[2][1] && ship[1][1] + 2 == ship[0][1] && ship[1][1] + 3 == ship[3][1]) ||
					(ship[1][1] + 1 == ship[3][1] && ship[1][1] + 2 == ship[2][1] && ship[1][1] + 3 == ship[0][1]) ||
					(ship[1][1] + 1 == ship[3][1] && ship[1][1] + 2 == ship[0][1] && ship[1][1] + 3 == ship[2][1]) ||

					(ship[3][1] + 1 == ship[0][1] && ship[3][1] + 2 == ship[2][1] && ship[3][1] + 3 == ship[1][1]) ||
					(ship[3][1] + 1 == ship[0][1] && ship[3][1] + 2 == ship[1][1] && ship[3][1] + 3 == ship[2][1]) ||
					(ship[3][1] + 1 == ship[1][1] && ship[3][1] + 2 == ship[2][1] && ship[3][1] + 3 == ship[0][1]) ||
					(ship[3][1] + 1 == ship[1][1] && ship[3][1] + 2 == ship[0][1] && ship[3][1] + 3 == ship[2][1]) ||
					(ship[3][1] + 1 == ship[2][1] && ship[3][1] + 2 == ship[1][1] && ship[3][1] + 3 == ship[0][1]) ||
					(ship[3][1] + 1 == ship[2][1] && ship[3][1] + 2 == ship[0][1] && ship[3][1] + 3 == ship[1][1]) ||

					(ship[2][1] + 1 == ship[0][1] && ship[2][1] + 2 == ship[3][1] && ship[3][1] + 3 == ship[1][1]) ||
					(ship[2][1] + 1 == ship[0][1] && ship[2][1] + 2 == ship[1][1] && ship[3][1] + 3 == ship[3][1]) ||
					(ship[2][1] + 1 == ship[1][1] && ship[2][1] + 2 == ship[0][1] && ship[3][1] + 3 == ship[3][1]) ||
					(ship[2][1] + 1 == ship[1][1] && ship[2][1] + 2 == ship[3][1] && ship[3][1] + 3 == ship[0][1]) ||
					(ship[2][1] + 1 == ship[3][1] && ship[2][1] + 2 == ship[1][1] && ship[3][1] + 3 == ship[0][1]) ||
					(ship[2][1] + 1 == ship[3][1] && ship[2][1] + 2 == ship[0][1] && ship[3][1] + 3 == ship[1][1]))) return true;
	}
	return false;
}
bool CheckSequence(int quantity_of_deck, std::vector<std::vector<int>> my_ship, IsSuccessively_t IsSuccessivelyF1, IsSuccessively_t IsSuccessivelyF2)//������ �� ��������?���������: ������� ���� � ��� �������. ����� ���������� �������
{
	//�������� ����������� �� �������.
	//�� ���� ��� �� �������� ����� ��������
	// ������� ���� ������������� ���������� || ���� �����������
	if (IsSuccessivelyF1(my_ship, quantity_of_deck)  ||  IsSuccessivelyF2(my_ship, quantity_of_deck)  ) return true;
	
	return false;
}
void EnterCoordinate(int& coordinate)
{
	while (!std::cin >> coordinate || coordinate > 10 || coordinate <= 0)
	{
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		std::cin.ignore(100, '\n');
	}
	--coordinate;//����������� ��� ������� ������ ��� -1
}

bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_ )
{
	//����� �� ��� ���������������� �������
	for (int i = 0; i < (int)this_ship.size(); ++i)
		if (this_ship[i][0] == row_number_ && this_ship[i][1] == column_number_) return true;
	return false;
}

bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int rows, int columns, int row_number_, int column_number_)
{ 
	//�������� ��� �� ����� ������ ��������
	// ���� ������ ����� � ������ �������� return true;

	//�������� ����� �������    check from  LEFT  TO  RIGHT
	if (column_number_ != 9  &&  my_field[row_number_][column_number_ + 1] == 'k') return true;
	//�������� ������ ������    check from  RIGHT  TO  LEFT 
	if (column_number_ != 0  &&  my_field[row_number_][column_number_ - 1] == 'k') return true;
	//��������  ������ ����     check from  TOP  TO  BOTTOM
	if (row_number_ != 9  &&  my_field[row_number_ + 1][column_number_] == 'k') return true;
	//��������  ����� �����     check from  BOTTOM  TO  TOP
	if (row_number_ != 0  &&  my_field[row_number_ - 1][column_number_] == 'k') return true;

	return false;
}
void AlgorithArrangeShips(std::vector<std::vector<char>>& field, int field_rows, int field_columns, int quantity_of_ships, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF)
{
	int row_number;

	int column_number;

	for (int i = 0; i < quantity_of_ships; ++i)// a loop of entering ships  ���� �������� ��������
	{
		std::vector<std::vector<int>> ship(quantity_of_decks, std::vector<int>(2)); //������� ������ c ������������ ��������� ������ �������
		//������� ������������� � ��������� �������
		for (int i = 0; i < quantity_of_decks; ++i)//������������� ������� ������������� ���������� �� ���� 30
			ship[i][1] = ship[i][0] = 30;

		do
		{
			for (int i = 1; i <= quantity_of_decks; ++i)// �������� �� ������ ������
			{
				std::cout << "Enter a row:";
				EnterCoordinate(row_number);

				std::cout << "Enter a column:";
				EnterCoordinate(column_number);

				//�������� ��� �� ����� ������ ��������. 
				if (field[row_number][column_number] == 'k' || (IsPartOfShipF(ship, row_number, column_number) && IsNearHereAnotherShipsF(field, field_rows, field_columns, row_number, column_number)))//���� ��� ��� ����� ������� ��� ���� ����� ��� ����� �������
				{
					std::cout << "There is already part of a ship or a ship in this cell or near here." << std::endl;
					std::cout << "Please try again to enter cell coordinates." << std::endl;
					--i;
				}
				else //� ������ ��������� ������� ���������� ���������� ������� ������
				{
					ship[i - 1][0] = row_number;
					ship[i - 1][1] = column_number;
				}
			}
		} while(CheckSequence(quantity_of_decks, ship, AreCellsArrangedHorizontallySuccessively, AreCellsArrangedVerticallySuccessively)); //�������� ����������� �� �������
		
		//���������� ������� �� ����
		for(int i = 0; i < quantity_of_decks; ++i)//loop for a decks of the ship
			field[  ship[i][0]  ][  ship[i][1]  ] = 'k';
		//show field
		ShowFieldF(field, field_rows, field_columns);
	}
}

void ArrangeShips(std::vector<std::vector<char>>& my_field, int rows, int columns, AlgorithArrangeShips_t AlgorithArrangeShipsF)
{
	for(int quantity_of_decks_ = 4, quantity_of_ships_ = 1; quantity_of_decks_ >= 1; --quantity_of_decks_, ++quantity_of_ships_)
	{
		std::cout << "Arange ";
		switch (quantity_of_decks_)
		{
			case 1: std::cout << "single";
			case 2: std::cout << "double";
			case 3: std::cout << "three";
			case 4: std::cout << "four";
		}
		std::cout << " - deck ship!" << std::endl;
		AlgorithArrangeShipsF(my_field, rows, columns, quantity_of_ships_, quantity_of_decks_, IsNearHereAnotherShips, IsPartOfShip, ShowField);
	}
}

//bool ���_��_��� �������_���������(std::vector<std::vector<char>>&  ��� ����){}
//bool ���_��_�������_�����_���������(std::vector<std::vector<char>>&  ���� �����){}

//bool ����_��_����������(std::vector<std::vector<char>>& ���� ���, std::vector<std::vector<char>>& ���� �����, ���_��� �������_���������,  ���_�������_�����_���������)
//{ ���_��� �������_���������  ||  ���_�������_�����_���������  }

//void ���_���(std::vector<std::vector<char>>&  ���� �����, �����_��_�_����(),  ����_��_����������() )
//{
//���
// if ( !�����_��_�_����() || ( �����_��_�_����() &&  ����_��_����������() )    ) { break; }
// if else (�����_��_�_����() && ! ����_��_����������() ) ���_���(); ��������
//}

void Game()
{
	//do
	//{
	// 
		//my step ( arguments  :    bool  HIT_LI_IN_ GOAL()    bool   IS_LI_INCER(), )
		//display:
		// 1. if  hasnt  hit
		// 2. if you have  hit and completely sank the ship. RECURSION
		// 3. if you hit and did not completely sink the ship. RECURSION
		// if (THERE IS A WINNER()) break;
		//enemy step from the server
		// 1. if  hasnt  hit
		// 2. if  has hit, RECURSION
		//


	//} while(IaThereAWinner(arguments));
	//} while(����_��_����������(���������));
	

}