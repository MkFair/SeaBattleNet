#ifndef CUSTOMER_FUNCTIONS_H
#define CUSTOMER_FUNCTIONS_H

#include <iostream>
#include <vector>

const int ROW = 10;

const int COLUMN = 10;

typedef void (*ShowField_t)(const std::vector<std::vector<char>>& my_field);
typedef bool (*IsSuccessively_t)(std::vector<std::vector<int>> ship, int);
typedef bool (*IsPartOfShip_t)(std::vector<std::vector<int>>& , int , int );
typedef bool (*IsNearHereAnotherShips_t)(std::vector<std::vector<char>>& my_field, int row_number_, int column_number_);
typedef void (*AlgorithArrangeShips_t)(std::vector<std::vector<char>>& field, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF);
typedef bool (*HaveHitTheTarget_t)(std::vector<std::vector<char>>& field, int row_number, int column_number, ShowField_t ShowFieldF);
typedef bool (*AreThereAnySheeps_t)(std::vector<std::vector<char>>& field);


std::vector<std::vector<char>> InitField();
void ShowField(const std::vector<std::vector<char>>& my_field);
bool AreCellsArrangedHorizontallySuccessively(std::vector<std::vector<int>> ship, int quantity_of_deck_);
bool AreCellsArrangedVerticallySuccessively(std::vector<std::vector<int>> ship, int quantity_of_deck_);
bool CheckSequence(int quantity_of_deck, std::vector<std::vector<int>> my_ship, IsSuccessively_t IsSuccessivelyF1, IsSuccessively_t IsSuccessivelyF2);
void EnterCoordinate(int& coordinate);
bool IsPartOfShip(std::vector<std::vector<int>>& this_ship, int row_number_, int column_number_);
bool IsNearHereAnotherShips(std::vector<std::vector<char>>& my_field, int row_number_, int column_number_);
void AlgorithArrangeShips(std::vector<std::vector<char>>& field, int quantity_of_decks, IsNearHereAnotherShips_t IsNearHereAnotherShipsF, IsPartOfShip_t IsPartOfShipF, ShowField_t ShowFieldF);
void ArrangeShips(std::vector<std::vector<char>>& my_field, AlgorithArrangeShips_t AlgorithArrangeShipsF);
bool HaveHitTheTarget(std::vector<std::vector<char>>& field, int row_number, int column_number, ShowField_t ShowFieldF);
bool AreThereAnySheeps(std::vector<std::vector<char>>& field);
void Game(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_, HaveHitTheTarget_t HaveHitTheTargetF, AreThereAnySheeps_t AreThereAnySheepsF);
void Results(std::vector<std::vector<char>>& customer_field_, std::vector<std::vector<char>>& enemy_field_, AreThereAnySheeps_t AreThereAnySheepsF);

#endif