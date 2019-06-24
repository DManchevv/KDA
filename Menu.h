#pragma once
#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <set>
#include "Automat.h"
#include "AutomatContainer.h"
#include "State.h"
#include "Convert.h"

class Menu {	
public:
	Menu();
	void Introduction(); // Introduction with the commands menu
	void StartMenu(); // Function where the user enters his commands
	void Savefile(int ID); // Saving automat in a file
	void CheckState(Automat& obj, std::string alphabet, int id, char Letter, int To, int N, const int* Final); // Creating a new state and adding it with its transition to the automat when reading from a file
	bool isValid(std::string alphabet, char symb); // Checking if the symbol is included in the automat's alphabet.
	bool IsDeterministic(const int DeterID); // Checks if the automat is deterministic.
	bool ValidID(const int checkID); // Checks if the input ID is valid;
	bool isEmpty(const int EmptyID);
	void Union(AutomatContainer& Storage, int &counter, const int UnionID1, const int UnionID2);
	void Concat(AutomatContainer& Storage, int &counter, const int ConcatID1, const int ConcatID2);
	void Un(AutomatContainer& Storage, int &counter, const int UnID1);
	bool Recognize(const int RecognizeID);
	Automat MakeDFA(const int DFAID);
	void MakeDet(Automat &automat, Automat& newDFA, const int index, int* UsedStates, int &StatesNumber, const int arrsize, bool Final, char Symbol, std::vector <int*> &Storage, int &size, std::string &alphabet, char* &usedsymbols, int &symbolsCounter);
};
bool equalpointers(const int* pointer1, const int* pointer2, int size);

/*void Introduction(); // Introduction with the commands menu
void StartMenu(); // Function where the user enters his commands
void Savefile(int ID); // Saving automat in a file
void CheckState(Automat& obj, std::string alphabet, int id, char Letter, int To, int N, const int* Final); // Creating a new state and adding it with its transition to the automat when reading from a file
bool isValid(std::string alphabet, char symb); // Checking if the symbol is included in the automat's alphabet.
bool IsDeterministic(const int DeterID); // Checks if the automat is deterministic.
bool ValidID(const int checkID); // Checks if the input ID is valid;
bool isEmpty(const int EmptyID);*/