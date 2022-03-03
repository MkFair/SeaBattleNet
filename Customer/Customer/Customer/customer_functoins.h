#ifndef CUSTOMER_FUNCTIONS_H
#define CUSTOMER_FUNCTIONS_H

#include <iostream>
#include <vector>

typedef bool (*IsPartOfShip_t)(std::vector<std::vector<int>>& , int , int );

std::vector<std::vector<char>> InitField(int rows, int columns);
void ShowField(const std::vector<std::vector<char>>& my_field, int rows, int columns);
bool CheckSequence(std::vector<std::vector<char>>& my_field, int field_rows, int field_columns, int coordinate_x, int coordinate_y);
void EnterCoordinate(int& coordinate);
bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_);
bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int rows, int columns, int row_number_, int column_number_);
void ArrangeShips(std::vector<std::vector<char>>& my_field, int rows, int columns);

#endif