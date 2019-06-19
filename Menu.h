#pragma once
#include <iostream>
#include "Automat.h"
void Introduction();
void StartMenu();
void Savefile(int ID);
void CheckState(Automat& obj, const char* alphabet, int id, char Letter, int To, int N, const int* Final);
bool isValid(const char* alphabet, char symb);
