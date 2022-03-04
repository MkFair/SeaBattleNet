#ifndef CUSTOMER_FUNCTIONS_H
#define CUSTOMER_FUNCTIONS_H

#include <iostream>
#include <vector>

typedef void (*ShowField_t)(const std::vector<std::vector<char>>& my_field, int rows, int columns);
typedef bool (*IsSuccessively_t)(std::vector<std::vector<int>> ship, int);
typedef bool (*IsPartOfShip_t)(std::vector<std::vector<int>>& , int , int );
typedef bool (*IsNearHereAnotherShips_t)(std::vector<std::vector<char>>& my_field, int rows, int columns, int row_number_, int column_number_);
typedef void (*AlgorithArrangeShips_t)(std::vector<std::vector<char>>& field, int field_rows, int field_columns, int quantity_of_ships, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF);

std::vector<std::vector<char>> InitField(int rows, int columns);
void ShowField(const std::vector<std::vector<char>>& my_field, int rows, int columns);
bool AreCellsArrangedHorizontallySuccessively(std::vector<std::vector<int>> ship, int quantity_of_deck_);
bool AreCellsArrangedVerticallySuccessively(std::vector<std::vector<int>> ship, int quantity_of_deck_);
bool CheckSequence(int quantity_of_deck, std::vector<std::vector<int>> my_ship, IsSuccessively_t IsSuccessivelyF1, IsSuccessively_t IsSuccessivelyF2);
void EnterCoordinate(int& coordinate);
bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_);
bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int rows, int columns, int row_number_, int column_number_);
void AlgorithArrangeShips(std::vector<std::vector<char>>& field, int field_rows, int field_columns, int quantity_of_ships, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF);
void ArrangeShips(std::vector<std::vector<char>>& my_field, int rows, int columns, AlgorithArrangeShips_t AlgorithArrangeShipsF);

#endif