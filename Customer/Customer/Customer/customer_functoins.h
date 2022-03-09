#ifndef CUSTOMER_FUNCTIONS_H
#define CUSTOMER_FUNCTIONS_H

#include <iostream>
#include <vector>
#include "network.h"

const int ROW = 10;

const int COLUMN = 10;

typedef void (*ShowField_t)(const std::vector<std::vector<char>>& my_field);
typedef bool (*AreChosenCoordinateSame_t)(const std::vector<std::vector<int>>& the_ship, bool is_horisontal);
typedef bool (*IsSuccessively_t)(const std::vector<std::vector<int>>& ship, AreChosenCoordinateSame_t AreChosenCoordinateSameF);
typedef bool (*IsPartOfShip_t)(std::vector<std::vector<int>>& , int , int );
typedef bool (*IsNearHereAnotherShips_t)(std::vector<std::vector<char>>& my_field, int row_number_, int column_number_);
typedef void (*AlgorithmArrangeShips_t)(std::vector<std::vector<char>>& field, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF);
typedef bool (*HaveHitTheTarget_t)(std::vector<std::vector<char>>& field, int row_number, int column_number, ShowField_t ShowFieldF);
typedef bool (*AreThereAnySheeps_t)(std::vector<std::vector<char>>& field);



////////////////////////////////////////////////////
///////////////////////////////////////////////////
//ONLY FOR TEST
void ArrangeONEShip(std::vector<std::vector<char>>& my_field, AlgorithmArrangeShips_t AlgorithmArrangeShipsF, SOCKET s);
//ONLY FOR TEST
//////////////////////////////////////////////////
////////////////////////////////////////////////


std::vector<std::vector<char>> InitField();
void ShowField(const std::vector<std::vector<char>>& my_field);
bool AreChosenCoordinateSame(const std::vector<std::vector<int>>& the_ship, bool is_horisontal);
bool AreCellsArrangedHorizontallySuccessively(const std::vector<std::vector<int>>& ship, AreChosenCoordinateSame_t AreChosenCoordinateSameF);
bool AreCellsArrangedVerticallySuccessively(const std::vector<std::vector<int>>& ship, AreChosenCoordinateSame_t AreChosenCoordinateSameF);
bool CheckSequence(const std::vector<std::vector<int>>& my_ship, IsSuccessively_t IsSuccessivelyF1, IsSuccessively_t IsSuccessivelyF2);
void EnterCoordinate(int& coordinate);
bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_);
bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int row_number_, int column_number_);
void AlgorithmArrangeShips(std::vector<std::vector<char>>& field, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF);
void ArrangeShips(std::vector<std::vector<char>>& my_field, AlgorithmArrangeShips_t AlgorithmArrangeShipsF);
bool HaveHitTheTarget(std::vector<std::vector<char>>& field, int row_number, int column_number, ShowField_t ShowFieldF);
bool AreThereAnySheeps(std::vector<std::vector<char>>& field);
void Game(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_, HaveHitTheTarget_t HaveHitTheTargetF, AreThereAnySheeps_t AreThereAnySheepsF);
void Results(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_, AreThereAnySheeps_t AreThereAnySheepsF);

#endif