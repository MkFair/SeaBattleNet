#include <iostream>
#include <vector>
#include "customer_functoins.h"
#include "network.h"

extern const int ROW;

extern const int COLUMN;

std::vector<std::vector<char>> InitField()
{
	std::vector<std::vector<char>> my_field(ROW, std::vector<char>(COLUMN));

	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COLUMN; ++j)
			my_field[i][j] = 'O';

	return my_field;
}

//for (int i = 1; i <= 10; ++i)
//std::cout << '\t' << i;
//std::cout << '\t';
//for (int i = 1; i <= 10; ++i)
//std::cout << '\t' << i;
//std::cout << std::endl;

void ShowField(const std::vector<std::vector<char>>& my_field)
{
	//std::cout << "\tYOUR FIELD\t\t\t\tENEMY`S FIELD" << std::endl;
	std::cout << std::endl << "\tYOUR FIELD" << std::endl;

	for (int i = 1; i <= COLUMN; ++i)
	{
		if (i == 1) std::cout << "    " << i;
		else std::cout << "  " << i;
	}

	std::cout << std::endl;

	for (int i = 0; i < ROW; ++i)
	{
		std::cout << i + 1;
		for (int j = 0; j < COLUMN; ++j)
		{
			if (i != 9  && j == 0) std::cout << "   " << my_field[i][j];
			else std::cout << "  " << my_field[i][j];
		}
		std::cout << std::endl;
	}

}
void ShowBothFields(const std::vector<std::vector<char>>& my_field, const std::vector<std::vector<char>>& enemy_field)
{
	std::cout << "\t\t\tYOUR FIELD\t\t\t\t\t\t\t\t\tENEMY`S FIELD" << std::endl;
	//std::cout << std::endl << "\tYOUR FIELD" << std::endl;

	for (int i = 1; i <= COLUMN; ++i)
	{
		if (i == 1) std::cout << "    " << i;
		else std::cout << "  " << i;
	}
	std::cout << "\t\t\t";
	for (int i = 1; i <= COLUMN; ++i)
	{
		if (i == 1) std::cout << "    " << i;
		else std::cout << "  " << i;
	}
	std::cout << std::endl;

	for (int i = 0; i < ROW; ++i)
	{
		std::cout << i + 1;
		for (int j = 0; j < COLUMN; ++j)
		{
			if (i != 9 && j == 0) std::cout << "   " << my_field[i][j];
			else std::cout << "  " << my_field[i][j];
		}
		std::cout << "\t\t\t" << i + 1;
		for (int j = 0; j < COLUMN; ++j)
		{
			if (i != 9 && j == 0) std::cout << "   " << enemy_field[i][j];
			else std::cout << "  " << enemy_field[i][j];
		}
		std::cout << std::endl;
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CHECK/OF/SHIPS////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AreChosenCoordinateSame(const std::vector<std::vector<int>>& the_ship, bool is_horisontal)
{
	for (std::vector<std::vector<int>>::const_iterator i = the_ship.begin() + 1; i != the_ship.end(); ++i)
		if (the_ship[0][(int)is_horisontal] != (*i)[(int)is_horisontal]) return false;
		else return true;
}

bool AreCellsArrangedHorizontallySuccessively(const std::vector<std::vector<int>>& ship)
{
	//Y  ARE THE SAME
	if (  !AreChosenCoordinateSame(ship, true)  ) return false;
	return check_is_linear(ship, true);
	/*
	switch (ship.size())
	{
		case 1: return true; break;
		case 2: if (ship[0][0] + 1 == ship[1][0] || ship[0][0] - 1 == ship[1][0]) return true;
		case 3: if ((ship[0][0] + 1 == ship[1][0] && ship[0][0] + 2 == ship[2][0] )  ||  
					(ship[0][0] - 1 == ship[1][0] && ship[0][0] + 1 == ship[2][0] )  ||
					(ship[0][0] + 1 == ship[2][0] && ship[2][0] + 1 == ship[1][0] )  ||
					(ship[0][0] - 1 == ship[1][0] && ship[2][0] + 1 == ship[0][0] )  ||
					(ship[2][0] + 1 == ship[0][0] && ship[0][0] + 1 == ship[1][0] )  ||
					(ship[2][0] + 1 == ship[1][0] && ship[1][0] + 1 == ship[0][0] )) return true;
		case 4: if ((ship[0][0] + 1 == ship[1][0] && ship[0][0] + 2 == ship[2][0] && ship[0][0] + 3 == ship[3][0]) ||
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
				   (ship[2][0] + 1 == ship[3][0] && ship[2][0] + 2 == ship[0][0] && ship[3][0] + 3 == ship[1][0])) return true;
	}
	return false;*/
}
const std::vector<std::vector<int>>& sort_ship(std::vector<std::vector<int>>& ship) {
	sort(ship.begin(), ship.end(), [](std::vector<int> first, std::vector<int> second) {return first[0] < second[0]; });
	sort(ship.begin(), ship.end(), [](std::vector<int> first, std::vector<int> second) {return first[1] < second[1]; });
	for (auto el : ship) {
		std::cout << el[0] << el[1];
	}
	std::cout << "-------------------- -"<<std::endl;
	return ship;
}

bool check_is_linear(const std::vector<std::vector<int>>& ship,bool is_horisontal) {
	for (short i = 1; i < ship.size(); i++) {
		std::cout << "current coord test "<< ship[i][static_cast<int>(is_horisontal)]<<std::endl;
		if(ship[i][static_cast<int>(!is_horisontal)]!= ship[i-1][static_cast<int>(!is_horisontal)]+1)
			return false;
	}
	return true;
}

bool AreCellsArrangedVerticallySuccessively( std::vector<std::vector<int>>& ship)
{
	
	//X  ARE THE SAME
	if (!AreChosenCoordinateSame(ship, false)) return false;
	return check_is_linear(ship,false);
	/*
	switch (ship.size())
	{
		case 1: return true; break;
		case 2: if (ship[0][1] + 1 == ship[1][1] || ship[0][1] - 1 == ship[1][1]) return true;
		case 3: if ((ship[0][1] + 1 == ship[1][1] && ship[0][1] + 2 == ship[2][1]) ||
					(ship[0][1] - 1 == ship[1][1] && ship[0][1] + 1 == ship[2][1]) ||
					(ship[0][1] + 1 == ship[2][1] && ship[2][1] + 1 == ship[1][1]) ||
					(ship[0][1] - 1 == ship[1][1] && ship[2][1] + 1 == ship[0][1]) ||
					(ship[2][1] + 1 == ship[0][1] && ship[0][1] + 1 == ship[1][1]) ||
					(ship[2][1] + 1 == ship[1][1] && ship[1][1] + 1 == ship[0][1])) return true;
		case 4: if ((ship[0][1] + 1 == ship[1][1] && ship[0][1] + 2 == ship[2][1] && ship[0][1] + 3 == ship[3][1]) ||
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
					(ship[2][1] + 1 == ship[3][1] && ship[2][1] + 2 == ship[0][1] && ship[3][1] + 3 == ship[1][1])) return true;
	}
	return false;*/
}

bool CheckSequence( std::vector<std::vector<int>>& my_ship)//подряд ли клеточки?аргументы: сначала поле и его размеры. потом координаты корабля
{
	sort_ship(my_ship);
	//проверка ПОЛНОЦЕННЫЙ ЛИ КОРАБЛЬ.
	//ТО ЕСТЬ НЕТ ЛИ ПРОБЕЛОВ МЕЖДУ ПАЛУБАМИ
	// КОРАБЛЬ ЛИБО ГОРИЗОНТАЛЬНО РАСПОЛОЖЕН || ЛИБО ВЕРТИКАЛЬНО
	if (   AreCellsArrangedHorizontallySuccessively(my_ship)  ||  AreCellsArrangedVerticallySuccessively(my_ship)  ) return true;
	std::cout << "------Ship is invalid------"<<std::endl;
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CHECK/OF/SHIPS////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EnterCoordinate(int& coordinate)
{
	std::cin >> coordinate;
	while (!coordinate || coordinate > 10 || coordinate <= 0)
	{
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		std::cin.ignore(100, '\n');
		std::cin >> coordinate;
	}
	std::cout << "you have entered " << coordinate<<std::endl;
	--coordinate;//преобразуем для вектора данные нат -1
}

bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_ )
{
	//часть ли это рассматриваемого корабля
	for (int i = 0; i < (int)this_ship.size(); ++i)
		if (this_ship[i][0] == row_number_ && this_ship[i][1] == column_number_) return true;
	return false;
}

bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int row_number_, int column_number_)
{ 
	//ПРОВЕРКА НЕТ ЛИ РЯДОМ ДРУГИХ КОРАБЛЕЙ
	// ЕСЛИ ПАЛУБА РЯДОМ С ДРУГИМ КОРАБЛЕМ return true;

	//проверка СЛЕВА НАПРАВО    check from  LEFT  TO  RIGHT
	if (column_number_ != 9  &&  my_field[row_number_][column_number_ + 1] == 'k') return true;
	//проверка СПРАВА НАЛЕВО    check from  RIGHT  TO  LEFT 
	if (column_number_ != 0  &&  my_field[row_number_][column_number_ - 1] == 'k') return true;
	//проверка  СВЕРХУ ВНИЗ     check from  TOP  TO  BOTTOM
	if (row_number_ != 9  &&  my_field[row_number_ + 1][column_number_] == 'k') return true;
	//проверка  СНИЗУ ВВЕРХ     check from  BOTTOM  TO  TOP
	if (row_number_ != 0  &&  my_field[row_number_ - 1][column_number_] == 'k') return true;

	return false;
}

void AlgorithmArrangeShips(std::vector<std::vector<char>>& field, int quantity_of_decks,SOCKET socket)
{
	int row_number;

	int column_number;

	int quantity_of_ships;

	switch (quantity_of_decks)
	{
		case 1: quantity_of_ships = 4; break;
		case 2: quantity_of_ships = 3; break;
		case 3: quantity_of_ships = 2; break;
		case 4: quantity_of_ships = 1; break;
	}
	for (int i = 0; i < quantity_of_ships; ++i)// a loop of entering ships  цикл введения кораблей
	{
		std::vector<std::vector<int>> ship(quantity_of_decks, std::vector<int>(2)); //создаем вектор c координатами координат одного корабля
		//ВЫНЕСТИ ИНИЦИАЛИЗАЦИЮ В ОТДЕЛЬНУЮ ФУНКЦИЮ
		for (int i = 0; i < quantity_of_decks; ++i)//ИНИЦИАЛИЗАЦИЯ КОРАБЛЯ НЕПРАВИЛЬНЫМИ ЗНАЧЕНИЯМИ то есть 30
			ship[i][1] = ship[i][0] = 30;

		do
		{
			for (int i = 0; i < quantity_of_decks; ++i)// ПРОХОДИМ ПО КАЖДОЙ ПАЛУБЕ
			{
				std::cout << "Enter a row:";
				EnterCoordinate(row_number);

				std::cout << "Enter a column:";
				EnterCoordinate(column_number);

				//ПРОВЕРКА НЕТ ЛИ РЯДОМ ДРУГИХ КОРАБЛЕЙ. 
				if (field[row_number][column_number] == 'k'  )//если уже там стоит корабль или если рядом уже стоял корабль
				{
					std::cout << "There is already a ship on the field in this cell." << std::endl;
					std::cout << "Please try again to enter cell coordinates." << std::endl;
					--i;
				} else if (  IsNearHereAnotherShips(field, row_number, column_number)  )
				{
					std::cout << "Sorry, you can`t place here a deck of a ship. There is another ships in the field near here." << std::endl;
					std::cout << "Please try again to enter cell coordinates." << std::endl;
					--i;
				} else //в вектор координат корабля записываем координаты текущей палубы
				{
					ship[i][0] = row_number;
					ship[i][1] = column_number;
					
				}
			}
		} while(!CheckSequence(ship)); //проверка ПОЛНОЦЕННЫЙ ЛИ КОРАБЛЬ
		
		//ЗАПИСЫВАЕМ КОРАБЛЬ НА ПОЛЕ
		for (int i = 0; i < quantity_of_decks; ++i) {//loop for a decks of the ship
			field[ship[i][0]][ship[i][1]] = 'k';
			std::cout << "Ship append in the list";
		}
		//SENT ON SERVER SHIP VECTOR
		add_ship(socket, ship);
		//show field
		ShowField(field);
	}
}

void ArrangeShips(std::vector<std::vector<char>>& my_field, SOCKET s)
{
	for(int quantity_of_decks_ = 4; quantity_of_decks_ >= 1; --quantity_of_decks_)
	{
		std::cout << "Arange ";
		switch (quantity_of_decks_)
		{
			case 1: std::cout << "single";
			case 2: std::cout << "double";
			case 3: std::cout << "three";
			case 4: std::cout << "four";
		}
		if (quantity_of_decks_ != 4) 
			std::cout << " - deck ships!" << std::endl;
		else 
			std::cout << " - deck ship!" << std::endl;

		AlgorithmArrangeShips(my_field, quantity_of_decks_, s);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ONLY FOR TEST///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ArrangeONEShip(std::vector<std::vector<char>>& my_field, SOCKET s)
{
		std::cout << "Arange four - deck ship!" << std::endl;
		AlgorithmArrangeShips(my_field, 4,s);
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ONLY FOR TEST///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool AreAllEnemyShipsSunked(const std::vector<std::vector<char>>& some_field)
{
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COLUMN; ++j)
			if (some_field[i][j] == 'k') return false;
	return true;
}

bool HaveHitTheTarget(std::vector<std::vector<char>>& field, int row_number_, int column_number_)
{
	if (field[row_number_][column_number_] == 'k')
		field[row_number_][column_number_] = 'p';// HAVE HIT THE TARGET   ПОПАЛ
	else field[row_number_][column_number_] = 'm';//HAVE MISSED    ПРОМАХНУЛСЯ

	ShowField(field);

	if (field[row_number_][column_number_] == 'm') return false;
	else return true;
}

void HaveHitMyShip(std::vector<std::vector<char>>& field, int row_number_, int column_number_)
{
	if (field[row_number_][column_number_] == 'k')
		field[row_number_][column_number_] = 'p';// HAVE HIT THE TARGET   ПОПАЛ
	else field[row_number_][column_number_] = 'm';//HAVE MISSED    ПРОМАХНУЛСЯ

	ShowField(field);
}

bool AreThereAnySheeps(std::vector<std::vector<char>>& field)
{
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COLUMN; ++j)
			if (field[i][j] == 'k') return true;
	return false;
}

void Step(std::vector<std::vector<char>>& some_field,SOCKET s)
{
	int row_number;

	int column_number;

	do
	{
		std::cout << "Enter a row:";
		EnterCoordinate(row_number);
		std::cout << "Enter a column:";
		EnterCoordinate(column_number);
	} while(   HaveHitTheTarget(some_field, row_number, column_number) && AreThereAnySheeps(some_field)   );
	send_firing_zone(s,row_number, column_number);
}

void Game(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_,SOCKET socket)
{
	std::cout << "Wait start game ..." << std::endl;
	PacketTypes type = wait_start_game(socket);
	std::cout << "game is starting  ..." << std::endl;
	bool my_first_step = false;
	if (type == PacketTypes::CAN_MOVE)
		my_first_step = true;
	while (true) // the eternal loop
	{
		ShowBothFields(customer_field_, enemy_field_);
		if (my_first_step) {
			Step(enemy_field_, socket); // STEP OF THE CUSTOMER
			std::pair<short , short> res = wait_other_player(socket);
		}
		else {
			std::pair<short, short> res = wait_other_player(socket);
			Step(enemy_field_, socket); // STEP OF THE CUSTOMER
		}
		if (!AreThereAnySheeps(enemy_field_) || !AreThereAnySheeps(customer_field_)) break;
		
	}
}

void Results(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_)
{
	if (AreThereAnySheeps(customer_field_))
		std::cout << "You are a winner. Congratulations!" << std::endl;
	else 
		std::cout << "You are a looser. ";
	std::cout << "Bye." << std::endl;
}