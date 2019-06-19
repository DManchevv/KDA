#include <iostream>
#include <cstring>
#include <map>
#include <iomanip>
#include <fstream>
#include "State.h"
#include "Automat.h"
#include "Menu.h"
#include <sstream>
Automat Store;
Automat StoreRepeatStates;
//void CheckState(const char* alphabet, int id, char Letter, int To, int N, const int* Final);
//bool isValid(const char* alphabet, char symb);

int main() {
	Introduction();
	StartMenu();
/*	char* alphabet = new char[40];
	int numb;
	char letter;
	std::string storeLetter;
	int To;
	int StatesNumb;
	int StartState;
	int NumbFinalStates;
	int* FinalStates;
	int NumbTransitions;
	char output[100];
	std::ifstream File;
	std::string filename;
	std::cin >> filename;
	File.open(filename);
	if (!File) {
		std::cout << "Unable to open file";
		exit(1); 
	}
	if (File.is_open()) {
		File >> alphabet >> StatesNumb >> StartState >> NumbFinalStates;
		std::cout << "Your automat's alphabet is: " << alphabet << std::endl;
		std::cout << "The number of the states in the automat is: " << StatesNumb << std::endl;
		std::cout << "The starting state of the automat is on position: " << StartState << std::endl;
		std::cout << "The Number of the final states in the automat is: " << NumbFinalStates << std::endl;
		FinalStates = new int[NumbFinalStates];
		std::cout << "The FinalStates of the automat have IDs: ";
		for (size_t i = 0; i < NumbFinalStates; i++) {
			File >> FinalStates[i];
				std::cout << FinalStates[i] << " ";
		}
		std::cout << std::endl;
		while (!File.eof()){
			File >> numb >> letter >> To;
			storeLetter += letter;
			CheckState(alphabet, numb, letter, To , NumbFinalStates, FinalStates);
		}
	}
	std::cout << std::endl;
	File.close();	
	for (int i = 0; i < Store.getSize(); i++)
	{
		for (std::multimap<char, int>::iterator it = Store.States[i].Transition.begin(); it != Store.States[i].Transition.end(); it++)
		{
			Store.PrintStateID(i);
			std::cout << it->first << " -> " << it->second << std::endl;
			Store.PrintStates(i);
		}
	}
	Savefile(6);*/
	return 0;
}
/*void CheckState(const char* alphabet, int id, char Letter, int To, int N,  const int* Final) {
	if (isValid(alphabet, Letter)) {
		if (id >= Store.getSize()) {
			State NewState;
			NewState.setID(id);
			for (size_t i = 0; i < N; i++) {
				if (Final[i] == id) {
					NewState.setFinalTrue();
					break;
				}
			}
			NewState.Transition.insert(std::pair<char, int>(Letter, To));
			Store.addState(NewState);
		}
		else
		{
			Store.States[id].Transition.insert(std::pair<char, int>(Letter, To));
		}
	}
	else {
		std::cout << "The letter is not included of the automat's alphabet. Fatal error #1." << std::endl;
		exit(0);
	}
}
bool isValid(const char* alphabet, char symb) {
	bool IsFound = false;
	for (size_t i = 0; i < strlen(alphabet); i++) {
		if (symb == alphabet[i]) {
			return true;
		}
	}
	 return false;
}
*/