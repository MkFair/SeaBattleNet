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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CHECK/OF/SHIPS////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AreChosenCoordinateSame(const std::vector<std::vector<int>>& the_ship, bool is_horisontal)
{
	for (std::vector<std::vector<int>>::const_iterator i = the_ship.begin() + 1; i != the_ship.end(); ++i)
		if (the_ship.begin()[(int)is_horisontal] != i[(int)is_horisontal]) return false;
		else return true;
}

bool AreCellsArrangedHorizontallySuccessively(std::vector<std::vector<int>> ship, AreChosenCoordinateSame_t AreChosenCoordinateSameF)
{
	//Y  ARE THE SAME
	if (  !AreChosenCoordinateSameF(ship, true)  ) return false;

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
	return false;
}

bool AreCellsArrangedVerticallySuccessively(std::vector<std::vector<int>> ship, AreChosenCoordinateSame_t AreChosenCoordinateSameF)
{
	//X  ARE THE SAME
	if (!AreChosenCoordinateSameF(ship, false)) return false;

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
	return false;
}

bool CheckSequence(const std::vector<std::vector<int>>& my_ship, IsSuccessively_t IsSuccessivelyF1, IsSuccessively_t IsSuccessivelyF2)//ÔÓ‰ˇ‰ ÎË ÍÎÂÚÓ˜ÍË?‡„ÛÏÂÌÚ˚: ÒÌ‡˜‡Î‡ ÔÓÎÂ Ë Â„Ó ‡ÁÏÂ˚. ÔÓÚÓÏ ÍÓÓ‰ËÌ‡Ú˚ ÍÓ‡·Îˇ
{
	//ÔÓ‚ÂÍ‡ œŒÀÕŒ÷≈ÕÕ€… À»  Œ–¿¡À‹.
	//“Œ ≈—“‹ Õ≈“ À» œ–Œ¡≈ÀŒ¬ Ã≈∆ƒ” œ¿À”¡¿Ã»
	//  Œ–¿¡À‹ À»¡Œ √Œ–»«ŒÕ“¿À‹ÕŒ –¿—œŒÀŒ∆≈Õ || À»¡Œ ¬≈–“» ¿À‹ÕŒ
	if (IsSuccessivelyF1(my_ship, AreChosenCoordinateSame)  ||  IsSuccessivelyF2(my_ship, AreChosenCoordinateSame)  ) return true;
	
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
	--coordinate;//ÔÂÓ·‡ÁÛÂÏ ‰Îˇ ‚ÂÍÚÓ‡ ‰‡ÌÌ˚Â Ì‡Ú -1
}

bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_ )
{
	//˜‡ÒÚ¸ ÎË ˝ÚÓ ‡ÒÒÏ‡ÚË‚‡ÂÏÓ„Ó ÍÓ‡·Îˇ
	for (int i = 0; i < (int)this_ship.size(); ++i)
		if (this_ship[i][0] == row_number_ && this_ship[i][1] == column_number_) return true;
	return false;
}

bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int row_number_, int column_number_)
{ 
	//œ–Œ¬≈– ¿ Õ≈“ À» –ﬂƒŒÃ ƒ–”√»’  Œ–¿¡À≈…
	// ≈—À» œ¿À”¡¿ –ﬂƒŒÃ — ƒ–”√»Ã  Œ–¿¡À≈Ã return true;

	//ÔÓ‚ÂÍ‡ —À≈¬¿ Õ¿œ–¿¬Œ    check from  LEFT  TO  RIGHT
	if (column_number_ != 9  &&  my_field[row_number_][column_number_ + 1] == 'k') return true;
	//ÔÓ‚ÂÍ‡ —œ–¿¬¿ Õ¿À≈¬Œ    check from  RIGHT  TO  LEFT 
	if (column_number_ != 0  &&  my_field[row_number_][column_number_ - 1] == 'k') return true;
	//ÔÓ‚ÂÍ‡  —¬≈–’” ¬Õ»«     check from  TOP  TO  BOTTOM
	if (row_number_ != 9  &&  my_field[row_number_ + 1][column_number_] == 'k') return true;
	//ÔÓ‚ÂÍ‡  —Õ»«” ¬¬≈–’     check from  BOTTOM  TO  TOP
	if (row_number_ != 0  &&  my_field[row_number_ - 1][column_number_] == 'k') return true;

	return false;
}

void AlgorithmArrangeShips(std::vector<std::vector<char>>& field, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF)
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
	for (int i = 0; i < quantity_of_ships; ++i)// a loop of entering ships  ˆËÍÎ ‚‚Â‰ÂÌËˇ ÍÓ‡·ÎÂÈ
	{
		std::vector<std::vector<int>> ship(quantity_of_decks, std::vector<int>(2)); //ÒÓÁ‰‡ÂÏ ‚ÂÍÚÓ c ÍÓÓ‰ËÌ‡Ú‡ÏË ÍÓÓ‰ËÌ‡Ú Ó‰ÌÓ„Ó ÍÓ‡·Îˇ
		//¬€Õ≈—“» »Õ»÷»¿À»«¿÷»ﬁ ¬ Œ“ƒ≈À‹Õ”ﬁ ‘”Õ ÷»ﬁ
		for (int i = 0; i < quantity_of_decks; ++i)//»Õ»÷»¿À»«¿÷»ﬂ  Œ–¿¡Àﬂ Õ≈œ–¿¬»À‹Õ€Ã» «Õ¿◊≈Õ»ﬂÃ» ÚÓ ÂÒÚ¸ 30
			ship[i][1] = ship[i][0] = 30;

		do
		{
			for (int i = 0; i < quantity_of_decks; ++i)// œ–Œ’Œƒ»Ã œŒ  ¿∆ƒŒ… œ¿À”¡≈
			{
				std::cout << "Enter a row:";
				EnterCoordinate(row_number);

				std::cout << "Enter a column:";
				EnterCoordinate(column_number);

				//œ–Œ¬≈– ¿ Õ≈“ À» –ﬂƒŒÃ ƒ–”√»’  Œ–¿¡À≈…. 
				if (field[row_number][column_number] == 'k'  )//ÂÒÎË ÛÊÂ Ú‡Ï ÒÚÓËÚ ÍÓ‡·Î¸ ËÎË ÂÒÎË ˇ‰ÓÏ ÛÊÂ ÒÚÓˇÎ ÍÓ‡·Î¸
				{
					std::cout << "There is already a ship on the field in this cell." << std::endl;
					std::cout << "Please try again to enter cell coordinates." << std::endl;
					--i;
				} else if (  IsNearHereAnotherShipsF(field, row_number, column_number)  )
				{
					std::cout << "Sorry, you can`t place here a deck of a ship. There is another ships in the field near here." << std::endl;
					std::cout << "Please try again to enter cell coordinates." << std::endl;
					--i;
				} else //‚ ‚ÂÍÚÓ ÍÓÓ‰ËÌ‡Ú ÍÓ‡·Îˇ Á‡ÔËÒ˚‚‡ÂÏ ÍÓÓ‰ËÌ‡Ú˚ ÚÂÍÛ˘ÂÈ Ô‡ÎÛ·˚
				{
					ship[i][0] = row_number;
					ship[i][1] = column_number;
				}
			}
		} while(!CheckSequence(ship, AreCellsArrangedHorizontallySuccessively, AreCellsArrangedVerticallySuccessively)); //ÔÓ‚ÂÍ‡ œŒÀÕŒ÷≈ÕÕ€… À»  Œ–¿¡À‹
		
		//«¿œ»—€¬¿≈Ã  Œ–¿¡À‹ Õ¿ œŒÀ≈
		for(int i = 0; i < quantity_of_decks; ++i)//loop for a decks of the ship
			field[  ship[i][0]  ][  ship[i][1]  ] = 'k';

		//SENT ON SERVER SHIP VECTOR
		

		//show field
		ShowFieldF(field);
	}
}

void ArrangeShips(std::vector<std::vector<char>>& my_field, AlgorithmArrangeShips_t AlgorithmArrangeShipsF)
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

		AlgorithmArrangeShipsF(my_field, quantity_of_decks_, IsNearHereAnotherShips, IsPartOfShip, ShowField);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ONLY FOR TEST///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ArrangeONEShip(std::vector<std::vector<char>>& my_field, AlgorithmArrangeShips_t AlgorithmArrangeShipsF)
{
	
		std::cout << "Arange four - deck ship!" << std::endl;

		AlgorithmArrangeShipsF(my_field, 4, IsNearHereAnotherShips, IsPartOfShip, ShowField);
	
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

bool HaveHitTheTarget(std::vector<std::vector<char>>& field, int row_number_, int column_number_, ShowField_t ShowFieldF)
{
	if (field[row_number_][column_number_] == 'k')
		field[row_number_][column_number_] = 'p';// HAVE HIT THE TARGET   œŒœ¿À
	else field[row_number_][column_number_] = 'm';//HAVE MISSED    œ–ŒÃ¿’Õ”À—ﬂ

	ShowFieldF(field);

	if (field[row_number_][column_number_] == 'm') return false;
	else return true;
}

bool AreThereAnySheeps(std::vector<std::vector<char>>& field)
{
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COLUMN; ++j)
			if (field[i][j] == 'k') return true;
	return false;
}

void Step(std::vector<std::vector<char>>& some_field, HaveHitTheTarget_t HaveHitTheTargetF, AreThereAnySheeps_t AreThereAnySheepsF)
{
	int row_number;

	int column_number;

	do
	{
		std::cout << "Enter a row:";
		EnterCoordinate(row_number);
		std::cout << "Enter a column:";
		EnterCoordinate(column_number);
	} while(   HaveHitTheTargetF(some_field, row_number, column_number, ShowField) && AreThereAnySheepsF(some_field)   );
}

void Game(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_, HaveHitTheTarget_t HaveHitTheTargetF, AreThereAnySheeps_t AreThereAnySheepsF)
{
	while(true) // the eternal loop
	{
		Step(customer_field_, HaveHitTheTargetF, AreThereAnySheepsF); // STEP OF ENEMY
		if (!AreThereAnySheepsF(customer_field_)) break;
		Step(enemy_field_, HaveHitTheTargetF, AreThereAnySheepsF); // STEP OF THE CUSTOMER
		if (!AreThereAnySheepsF(enemy_field_)) break;
	}
}

void Results(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_, AreThereAnySheeps_t AreThereAnySheepsF)
{
	if (AreThereAnySheepsF(customer_field_))
		std::cout << "You are a winner. Congratulations!" << std::endl;
	else 
		std::cout << "You are a looser. ";
	std::cout << "Bye." << std::endl;
}