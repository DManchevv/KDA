#pragma once
#include <iostream>
#include "Automat.h"
void Introduction(); // Introduction with the commands menu
void StartMenu(); // Function where the user enters his commands
void Savefile(int ID); // Saving automat in a file
void CheckState(Automat& obj, std::string alphabet, int id, char Letter, int To, int N, const int* Final); // Creating a new state and adding it with its transition to the automat when reading from a file
bool isValid(std::string alphabet, char symb); // Checking if the symbol is included in the automat's alphabet.
