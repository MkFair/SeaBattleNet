#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <vector>

std::vector<std::vector<char>> InitField(int rows, int columns);
void ShowField(const std::vector<std::vector<char>>& my_field, int rows, int columns);

#endif