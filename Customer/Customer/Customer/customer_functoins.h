#ifndef CUSTOMER_FUNCTIONS_H
#define CUSTOMER_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "network.h"

const int ROW = 10;

const int COLUMN = 10;

////////////////////////////////////////////////////
///////////////////////////////////////////////////
//ONLY FOR TEST
void ArrangeONEShip(std::vector<std::vector<char>>& my_field, SOCKET s);
//ONLY FOR TEST
//////////////////////////////////////////////////
////////////////////////////////////////////////

std::vector<std::vector<char>> InitField();
void ShowField(const std::vector<std::vector<char>>& my_field);
void ShowBothFields(const std::vector<std::vector<char>>& my_field, const std::vector<std::vector<char>>& enemy_field);
bool AreChosenCoordinateSame(const std::vector<std::vector<int>>& the_ship, bool is_horisontal);
bool AreCellsArrangedHorizontallySuccessively(const std::vector<std::vector<int>>& ship);
bool AreCellsArrangedVerticallySuccessively( std::vector<std::vector<int>>& ship);
bool CheckSequence( std::vector<std::vector<int>>& my_ship);
void EnterCoordinate(int& coordinate);
bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_);
bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int row_number_, int column_number_);
void AlgorithmArrangeShips(std::vector<std::vector<char>>& field, int quantity_of_decks, SOCKET socket);
void ArrangeShips(std::vector<std::vector<char>>& my_field, SOCKET s);
bool HaveHitTheTarget(std::vector<std::vector<char>>& field, int row_number, int column_number);
void HaveHitMyShip(std::vector<std::vector<char>>& field, int row_number_, int column_number_);
bool AreThereAnySheeps(std::vector<std::vector<char>>& field);
void Game(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_, SOCKET s);
void Results(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_);
bool check_is_linear(const std::vector<std::vector<int>>& ship, bool is_horisontal);
const std::vector<std::vector<int>>& sort_ship(std::vector<std::vector<int>>& ship);

#endif