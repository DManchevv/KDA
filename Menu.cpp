#include "Menu.h"
#include <fstream>
#include <sstream>
#include "Automat.h"
#include "AutomatContainer.h"
#include "State.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_set>
static AutomatContainer SaveAutomates;
static int automatcounter = 0;
char epsilon = '6';
Menu::Menu() {
	
}
void Menu::Introduction() {
	std::cout << "Welcome to my project's menu. Here are the available commands: " << std::endl;
	std::cout << "(Note: the symbol '6' is treated specially as epsilon.) " << std::endl;
	std::cout << "Open - opens a new file for a new DFA." << std::endl;
	std::cout << "List - prints the ID of all DFAs in the system." << std::endl;
	std::cout << "Print - prints all transitions in the DFA with the selected ID." << std::endl;
	std::cout << "Save - saves an automat with the selected ID in a file." << std::endl;
	std::cout << "Deterministic - checks if the automat with the selected ID is deterministic. " << std::endl;
	std::cout << "Union - unions two automates by their id. Saves the created new automat and sets new ID." << std::endl;
	std::cout << "Concat - concatenates two automates by their id. Saves the created new automat and sets new ID." << std::endl;
	std::cout << "Un - makes a kleene's star to the automat with the selected ID. Saves the created new automat and sets new ID." << std::endl;
	std::cout << "Reg - makes an automat using the selected regular expression. Saves the created new automat and sets new ID." << std::endl;
}
void Menu::StartMenu() {
	std::string commands;
	std::ifstream File;
	while (true) {
		std::cout << "Please enter a command." << std::endl;
		std::cin >> commands;
		if (commands == "Open" or commands == "open") {
			std::string alphabet;
			int numb;
			char letter;
			std::string storeLetter;
			int To;
			int StatesNumb;
			int StartState;
			int NumbFinalStates;
			std::string filename;
			std::cout << "Please enter the path of the file you want to open." << std::endl;
			std::cin >> filename;
			File.open(filename);
			if (!File) {
				std::cout << "Unable to open file!" << std::endl;
			}
			if (File.is_open()) {
				std::cout << "File successfully opened!" << std::endl;
				Automat newAutomat;
				File >> alphabet >> StatesNumb;
				newAutomat.setAlphabet(alphabet);
				newAutomat.setStatesNumb(StatesNumb);
				if (StatesNumb == 0) {
					SaveAutomates.addAutomat(newAutomat);
					SaveAutomates.Container[automatcounter].setID(automatcounter);
				}
				else{
					File >> StartState >> NumbFinalStates;
					newAutomat.setStartState(StartState);
					newAutomat.setNumbFinal(NumbFinalStates);
					if (NumbFinalStates == 0) {
						SaveAutomates.addAutomat(newAutomat);
						SaveAutomates.Container[automatcounter].setID(automatcounter);
					}
					else{
						int* FinalStates = new int[StatesNumb];
						int checkFinal;
						for (size_t i = 0; i < NumbFinalStates; i++) {
							File >> checkFinal;
							FinalStates[checkFinal] = checkFinal;
						}
						for (size_t i = 0; i < StatesNumb; i++) {
							if (FinalStates[i] != i) FinalStates[i] = -1;
						}
						newAutomat.setFinalStates(FinalStates);
						while (!File.eof()) {
							File >> numb >> letter >> To;
							storeLetter += letter;
							CheckState(newAutomat, alphabet, numb, letter, To, StatesNumb, FinalStates);
						}
						SaveAutomates.addAutomat(newAutomat);
						SaveAutomates.Container[automatcounter].setID(automatcounter);
						delete[] FinalStates;
					}
				}
				File.close();
				automatcounter++;
			}
		}
		if (commands == "List" or commands == "list") {
			for (size_t i = 0; i < automatcounter; i++) {
				std::cout << "Identifier for automat number " << i << " - " << SaveAutomates.Container[i].getID() << std::endl;
			}
		}
		if (commands == "Print" or commands == "print") {
			int PrintID;
			std::cout << "Enter the ID of the automat you want to print. " << std::endl;
			std::cin >> PrintID;
			if (!ValidID(PrintID)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
			else {
				std::cout << "The number of states of your automat is: " << SaveAutomates.Container[PrintID].getStatesNumb() << std::endl;
				std::cout << "The ID of the start state is: " << SaveAutomates.Container[PrintID].getStartState() << std::endl;
				std::cout << "The size is: " << SaveAutomates.Container[PrintID].getSize() << std::endl;
				for (size_t i = 0; i < SaveAutomates.Container[PrintID].getSize(); i++) {
					for (std::multimap<char, int>::iterator it = SaveAutomates.Container[PrintID].States[i].Transition.begin(); it != SaveAutomates.Container[PrintID].States[i].Transition.end(); it++)
					{
						SaveAutomates.Container[PrintID].PrintStateID(i);
						std::cout << it->first << " -> " << it->second << std::endl;
						SaveAutomates.Container[PrintID].PrintStates(i);
					}
				}
			}
		}
		if (commands == "Save" or commands == "save"){
			int saveID;
			std::cout << "Enter the new ID of the new automat." << std::endl;
			std::cin >> saveID;
			if (!ValidID(saveID)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
			else Savefile(saveID);
		}
		if (commands == "Empty" or commands == "empty") {
			std::cout << "Type the ID of the automat you want to check if it is empty." << std::endl;
			int Empty_ID;
			bool help;
			std::cin >> Empty_ID;
			if (!ValidID(Empty_ID)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
			else {
				help = isEmpty(Empty_ID);
				if (help) std::cout << "True" << std::endl;
				if (!help) std::cout << "False" << std::endl;
			}
		}
		if (commands == "Deterministic" or commands == "deterministic") {
			std::cout << "Type the ID of the automat you want to check. " << std::endl;
			int DetID;
			bool help;
			std::cin >> DetID;
			if (!ValidID(DetID)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
			else {
				if (isEmpty(DetID)) std::cout << "The automat's language is empty. Error #3." << std::endl;
				else {
					help = IsDeterministic(DetID);
					if (help) std::cout << "True" << std::endl;
					if (!help) std::cout << "False" << std::endl;
				}
			}
		}
		if (commands == "Recognize" or commands == "recognize") {
			int RecognizeID;
			bool value;
			std::cout << "Enter the ID of the automat you want to use." << std::endl;
			std::cin >> RecognizeID;
			value = Recognize(RecognizeID);
			if (value) std::cout << "The word can be recognized by the automat." << std::endl;
			else std::cout << "The word cannot be recognized by the automat." << std::endl;
		}
		if (commands == "Union" or commands == "union") {
			int UnionID1;
			std::cout << "Please enter the ID of the first automat. " << std::endl;
			std::cin >> UnionID1;
			if (!ValidID(UnionID1)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
			else {
				int UnionID2;
				std::cout << "Please enter the ID of the second automat. " << std::endl;
				std::cin >> UnionID2;
				if (!ValidID(UnionID2)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
				else {
					if (isEmpty(UnionID1) or isEmpty(UnionID2)) std::cout << "Cannot union an automat with empty language. Fatal error #3." << std::endl;
					else {
						Union(SaveAutomates, automatcounter, UnionID1, UnionID2);
					}
				}
			}
			std::cout << "The new unioned automat's ID is: " << automatcounter - 1 << "." << std::endl;
		}
		if (commands == "Concat" or commands == "concat") {
			int ConcatID1;
			std::cout << "Please enter the ID of the first automat. " << std::endl;
			std::cin >> ConcatID1;
			if (!ValidID(ConcatID1)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
			else {
				int ConcatID2;
				std::cout << "Please enter the ID of the second automat. " << std::endl;
				std::cin >> ConcatID2;
				if (!ValidID(ConcatID2)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
				else {
					if (isEmpty(ConcatID1) or isEmpty(ConcatID2)) std::cout << "Cannot concatenate an automat with empty language. Fatal error #3." << std::endl;
					else {
						Concat(SaveAutomates, automatcounter, ConcatID1, ConcatID2);
					}
				}
			}
			std::cout << "The new unioned automat's ID is: " << automatcounter - 1 << "." << std::endl;
		}
		if (commands == "Un" or commands == "un") {
			int UnID1;
			std::cout << "Please enter the ID of the automat. " << std::endl;
			std::cin >> UnID1;
			if (!ValidID(UnID1)) std::cout << "Automat's ID is not found. Error #2." << std::endl;
			else {
				if (isEmpty(UnID1)) std::cout << "Cannot do that to an automat with empty language. Fatal error #3." << std::endl;
				else {
					Un(SaveAutomates, automatcounter, UnID1);
				}
			}
			std::cout << "The new unioned automat's ID is: " << automatcounter - 1 << "." << std::endl;
		}
		if (commands == "Reg" or commands == "reg") {
			AutomatContainer RegexContainer;
			int RegexCounter = 0;
			int LastConstructedID = 0;
			std::string regex;
			std::cout << "Please type the regular expression you want to use. " << std::endl;
			std::cin >> regex;
			int	OpenBracketCounter = 0;
			int CloseBracketCounter = 0;
			for (size_t i = 0; i < regex.size(); i++) {
				if (regex[i] == '(') OpenBracketCounter++;
				if (regex[i] == ')') CloseBracketCounter++;
			}
			int *OpenBrackets = new int[OpenBracketCounter];
			int *CloseBrackets = new int[CloseBracketCounter];
			OpenBracketCounter = 0;
			CloseBracketCounter = 0;
			for (size_t i = 0; i < regex.size(); i++) {
				if (regex[i] == '(') {
					OpenBrackets[OpenBracketCounter] = i;
					OpenBracketCounter++;
				}
				if (regex[i] == ')') {
					CloseBrackets[CloseBracketCounter] = i;
					CloseBracketCounter++;
				}
			}
			for (size_t i = 0; i < CloseBracketCounter; i++) {
			//	std::cout << OpenBrackets[i] << " " << std::endl;
			}
			int* VisitedChars = new int[regex.size()];
			for (size_t i = 0; i < regex.size(); i++) {
				VisitedChars[i] = -1;
			}
			for (size_t i = 0; i < OpenBracketCounter; i++) {
				Automat Construction;
				State StartingState;
				std::string ConstrAlphabet;
				int ConstructionStates = 1;
				for (size_t j = OpenBrackets[OpenBracketCounter - i - 1] + 1; j < CloseBrackets[i]; j++) {
					//std::cout << " POSITION IN REGEX: " << j << " " << CloseBrackets[i] << " " << i << std::endl;
					if (regex.size() == 4) {
						StartingState.setID(0);
						StartingState.setFinalTrue();
						StartingState.Transition.insert(std::pair<char, int>(regex[1], 1));
						Construction.addState(StartingState);
						State Final;
						Final.setID(1);
						Final.setFinalTrue();
						Construction.addState(Final);
						RegexContainer.addAutomat(Construction);
						RegexContainer.Container[RegexCounter].setID(RegexCounter);
						RegexCounter++;
						Un(RegexContainer, RegexCounter, RegexCounter - 1);
					}
					else {
						if (j == OpenBrackets[OpenBracketCounter - i - 1] + 1) {
							StartingState.setID(0);
							StartingState.Transition.insert(std::pair<char, int>(regex[j], 1));
							Construction.addState(StartingState);
							ConstrAlphabet += regex[j];
						}
						if (regex[j + 1] != '+' and regex[j + 1] != '*' and regex[j + 2] != '*' and regex[j + 1] != '(' and regex[j + 1] != ')' and VisitedChars[j + 1] == -1) {
							//	std::cout << "Found a new state!" << std::endl;
							State NextState;
							NextState.setID(ConstructionStates);
							ConstructionStates++;
							//	std::cout << "Increased by 1 " << std::endl;
							NextState.Transition.insert(std::pair<char, int>(regex[j + 1], ConstructionStates));
							Construction.addState(NextState);
							bool isFound = false;
							for (size_t b = 0; b < ConstrAlphabet.size(); b++) {
								if (ConstrAlphabet[b] == regex[j + 1]) isFound = true;
							}
							if (!isFound) ConstrAlphabet += regex[j + 1];
							VisitedChars[j + 1] = 1;
						}
						else {

							if (regex[j + 1] == '(' and VisitedChars[j + 1] == -1) {
								//	std::cout << "Found something to concatenate!" << std::endl;
								State FinalState;
								FinalState.setFinalTrue();
								FinalState.setID(ConstructionStates);
								ConstructionStates++;
								Construction.addState(FinalState);
								int* newFinalStates = new int[ConstructionStates];
								for (size_t index = 0; index < ConstructionStates - 1; index++) {
									newFinalStates[index] = -1;
								}
								newFinalStates[ConstructionStates - 1] = ConstructionStates - 1;
								Construction.setAlphabet(ConstrAlphabet);
								Construction.setStartState(0);
								Construction.setStatesNumb(ConstructionStates);
								Construction.setNumbFinal(1);
								Construction.setFinalStates(newFinalStates);
								Construction.setNumbTransitions(ConstructionStates - 1);
								RegexContainer.addAutomat(Construction);
								RegexContainer.Container[RegexCounter].setID(RegexCounter);
								//	std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl;
								RegexCounter++;
								Concat(RegexContainer, RegexCounter, RegexCounter - 1, RegexCounter - 2);
								Construction = RegexContainer.Container[RegexCounter - 1];
								ConstructionStates = Construction.getStatesNumb();
								delete[] newFinalStates;
								VisitedChars[j + 1] = 1;
							}
							if (regex[j + 1] == ')' and VisitedChars[j + 1] == -1 and regex[j + 2] != '*' and j + 1 != regex.size() - 1) {
								//	std::cout << "Found that next symbol is )" << std::endl;
								State FinalState;
								FinalState.setFinalTrue();
								FinalState.setID(ConstructionStates);
								ConstructionStates++;
								Construction.addState(FinalState);
								int* newFinalStates = new int[ConstructionStates];
								for (size_t index = 0; index < ConstructionStates - 1; index++) {
									newFinalStates[index] = -1;
								}
								newFinalStates[ConstructionStates - 1] = ConstructionStates - 1;
								Construction.setAlphabet(ConstrAlphabet);
								Construction.setStartState(0);
								Construction.setStatesNumb(ConstructionStates);
								Construction.setNumbFinal(1);
								Construction.setFinalStates(newFinalStates);
								Construction.setNumbTransitions(ConstructionStates - 1);
								RegexContainer.addAutomat(Construction);
								RegexContainer.Container[RegexCounter].setID(RegexCounter);
								//	std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl;
								RegexCounter++;
								VisitedChars[j + 1] = 1;
								delete[] newFinalStates;
							}
							if (regex[j] != ')' and regex[j] != '(' and regex[j + 1] == '+' and regex[j + 2] == '(' and VisitedChars[j] == -1) {
								State FinalState;
								FinalState.setFinalTrue();
								FinalState.setID(ConstructionStates);
								ConstructionStates++;
								Construction.addState(FinalState);
								int* newFinalStates = new int[ConstructionStates];
								for (size_t index = 0; index < ConstructionStates - 1; index++) {
									newFinalStates[index] = -1;
								}
								newFinalStates[ConstructionStates - 1] = ConstructionStates - 1;
								Construction.setAlphabet(ConstrAlphabet);
								Construction.setStartState(0);
								Construction.setStatesNumb(ConstructionStates);
								Construction.setNumbFinal(1);
								Construction.setFinalStates(newFinalStates);
								Construction.setNumbTransitions(ConstructionStates - 1);
								RegexContainer.addAutomat(Construction);
								RegexContainer.Container[RegexCounter].setID(RegexCounter);
								RegexCounter++;
								Union(RegexContainer, RegexCounter, RegexCounter - 1, LastConstructedID);
							}
							if (regex[j + 1] == '+' and regex[j] == ')' and VisitedChars[j + 1] == -1) std::cout << "Tuka e slojno" << std::endl;
							if (regex[j + 1] == '+' and regex[j + 2] != '(' and regex[j] != ')' and VisitedChars[j + 1] == -1 and VisitedChars[j + 2] == -1 and VisitedChars[j] == -1) {
								//	std::cout << "Found automat to union" << std::endl;
								State FirstFinal;
								FirstFinal.setID(ConstructionStates - 1);
								FirstFinal.setFinalTrue();
								ConstructionStates++;
								int* FirstFinalStates = new int[ConstructionStates];
								for (size_t i = 0; i < ConstructionStates - 1; i++) {
									FirstFinalStates[i] = -1;
								}
								FirstFinalStates[ConstructionStates - 1] = ConstructionStates - 1;
								Construction.addState(FirstFinal);
								Construction.setAlphabet(ConstrAlphabet);
								Construction.setStartState(0);
								Construction.setStatesNumb(ConstructionStates);
								Construction.setNumbFinal(1);
								Construction.setFinalStates(FirstFinalStates);
								Construction.setNumbTransitions(ConstructionStates - 1);
								RegexContainer.addAutomat(Construction);
								RegexContainer.Container[RegexCounter].setID(RegexCounter);
								//	std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl;
								RegexCounter++;

								Automat newAutomat;
								State Start;
								std::string Alphabet;
								Start.setID(0);
								int* _FinalStates = new int[2];
								_FinalStates[0] = -1;
								_FinalStates[1] = 1;
								Start.Transition.insert(std::pair<char, int>(regex[j + 2], 1));
								Alphabet += regex[j + 2];
								State Final;
								Final.setID(1);
								Final.setFinalTrue();
								newAutomat.addState(Start);
								newAutomat.addState(Final);
								newAutomat.setStartState(0);
								newAutomat.setAlphabet(Alphabet);
								newAutomat.setStatesNumb(2);
								newAutomat.setNumbFinal(1);
								newAutomat.setFinalStates(_FinalStates);
								newAutomat.setNumbTransitions(1);
								RegexContainer.addAutomat(newAutomat);
								RegexContainer.Container[RegexCounter].setID(RegexCounter);
								//	std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl;
								RegexCounter++;
								delete[] _FinalStates;
								Union(RegexContainer, RegexCounter, RegexCounter - 2, RegexCounter - 1);
								VisitedChars[j + 1] = 1;
								VisitedChars[j + 2] = 1;
								j += 2;
							}
							if (regex[j - 1] == '*' and regex[j] == '(') {
								//	std::cout << "Found an opening bracket after * , concatenating them: " << RegexCounter -1 << " with " << LastConstructedID << std::endl;
								Concat(RegexContainer, RegexCounter, RegexCounter - 1, LastConstructedID);
							}
							if (regex[j + 2] == '*' and regex[j + 1] != ')' and regex[j + 1] != '(' and VisitedChars[j + 1] == -1 and VisitedChars[j + 2] == -1 and regex[j] != ')' and regex[j] != '(') {
								//	std::cout << "Found automat to Un, the star is after a number, the current symbol is not a bracket => concatenate both." << std::endl;
								State FirstFinal;
								FirstFinal.setID(ConstructionStates - 1);
								FirstFinal.setFinalTrue();
								ConstructionStates++;
								Construction.addState(FirstFinal);
								int* newFinalStates = new int[ConstructionStates];
								for (size_t index = 0; index < ConstructionStates - 1; index++) {
									newFinalStates[index] = -1;
								}
								newFinalStates[ConstructionStates - 1] = ConstructionStates - 1;
								Construction.setAlphabet(ConstrAlphabet);
								Construction.setStartState(0);
								Construction.setStatesNumb(ConstructionStates);
								Construction.setNumbFinal(1);
								Construction.setFinalStates(newFinalStates);
								Construction.setNumbTransitions(ConstructionStates - 1);
								RegexContainer.addAutomat(Construction);
								RegexContainer.Container[RegexCounter].setID(RegexCounter);
								//	std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl; 
								RegexCounter++;
								Automat newAutomat;
								State Start;
								std::string Alphabet;
								Start.setID(0);
								int* _FinalStates = new int[2];
								_FinalStates[0] = -1;
								_FinalStates[1] = 1;
								Start.Transition.insert(std::pair<char, int>(regex[j + 1], 1));
								Alphabet += regex[j + 1];
								State Final;
								Final.setID(1);
								Final.setFinalTrue();
								newAutomat.addState(Start);
								newAutomat.addState(Final);
								newAutomat.setStartState(0);
								newAutomat.setAlphabet(Alphabet);
								newAutomat.setStatesNumb(2);
								newAutomat.setNumbFinal(1);
								newAutomat.setFinalStates(_FinalStates);
								newAutomat.setNumbTransitions(1);
								RegexContainer.addAutomat(newAutomat);
								RegexContainer.Container[RegexCounter].setID(RegexCounter);
								//		std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl; 
								RegexCounter++;
								delete[] _FinalStates;
								Un(RegexContainer, RegexCounter, RegexCounter - 1);
								//	std::cout << "The Regex of the UN automat after a number is: " << RegexCounter - 1 << std::endl;
								VisitedChars[j + 1] = 1;
								VisitedChars[j + 2] = 2;
								Concat(RegexContainer, RegexCounter, RegexCounter - 3, RegexCounter - 1);
								//	std::cout << "The RegexCounter of the concatenated automat after UN is: " << RegexCounter - 1 << std::endl;
								Construction = RegexContainer.Container[RegexCounter - 1];
								ConstructionStates = Construction.getStatesNumb();
								j += 2;
							}
							else {
								if (regex[j + 2] == '*' and regex[j + 1] == ')' and VisitedChars[j + 1] == -1 and VisitedChars[j + 2] == -1) {
									//	std::cout << "Found automat to Un, the star is after a closing bracket." << std::endl;
									State FinalState;
									FinalState.setFinalTrue();
									FinalState.setID(ConstructionStates);
									ConstructionStates++;
									Construction.addState(FinalState);
									int* newFinalStates = new int[ConstructionStates];
									for (size_t index = 0; index < ConstructionStates - 1; index++) {
										newFinalStates[index] = -1;
									}
									newFinalStates[ConstructionStates - 1] = ConstructionStates - 1;
									Construction.setAlphabet(ConstrAlphabet);
									Construction.setStartState(0);
									Construction.setStatesNumb(ConstructionStates);
									Construction.setNumbFinal(1);
									Construction.setFinalStates(newFinalStates);
									Construction.setNumbTransitions(ConstructionStates - 1);
									RegexContainer.addAutomat(Construction);
									RegexContainer.Container[RegexCounter].setID(RegexCounter);
									//	std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl;
									RegexCounter++;
									Un(RegexContainer, RegexCounter, RegexCounter - 1);
									Construction = RegexContainer.Container[RegexCounter - 1];
									ConstructionStates = Construction.getStatesNumb();
									delete[] newFinalStates;
									VisitedChars[j + 1] = 1;
									VisitedChars[j + 2] = 1;
									j += 2;
								}
								else {
									if ((regex[j] == '*' or regex[j] == ')') and regex[j + 1] != '*' and regex[j + 1] != '+' and regex[j + 1] != ')' and regex[j + 1] != '(') {
										//	std::cout << "Found a number after a ) or a *" << std::endl;
										Automat newAutomat;
										State Start;
										std::string Alphabet;
										Start.setID(0);
										int* _FinalStates = new int[2];
										_FinalStates[0] = -1;
										_FinalStates[1] = 1;
										Start.Transition.insert(std::pair<char, int>(regex[j + 1], 1));
										Alphabet += regex[j + 1];
										State Final;
										Final.setID(1);
										Final.setFinalTrue();
										newAutomat.addState(Start);
										newAutomat.addState(Final);
										newAutomat.setStartState(0);
										newAutomat.setAlphabet(Alphabet);
										newAutomat.setStatesNumb(2);
										newAutomat.setNumbFinal(1);
										newAutomat.setFinalStates(_FinalStates);
										newAutomat.setNumbTransitions(1);
										RegexContainer.addAutomat(newAutomat);
										RegexContainer.Container[RegexCounter].setID(RegexCounter);
										std::cout << "The RegexCounter of this automat is: " << RegexCounter << std::endl;
										RegexCounter++;
										Concat(RegexContainer, RegexCounter, RegexCounter - 2, RegexCounter - 1);
									}
								}
							}
						}
					}
					VisitedChars[j] = 1;
				}
				LastConstructedID = RegexCounter - 1;
			}
			SaveAutomates.addAutomat(RegexContainer.Container[RegexCounter - 1]);
			SaveAutomates.Container[automatcounter].setID(automatcounter);
			std::cout << "The new automat's ID is: " << automatcounter << "." << std::endl;
			automatcounter++;
			delete[] OpenBrackets;
			delete[] CloseBrackets;
		}
		if (commands == "Exit" or commands == "exit") {
			break;
		}
	}
}
bool Menu::Recognize(const int RecognizeID) {
	bool isRecognized = true;
	bool IsInAlphabet = false;
	bool returnValue = true;
	std::string word;
	std::cout << "Enter the word you want to check." << std::endl;
	std::cin >> word;
	std::string alphabet = SaveAutomates.Container[RecognizeID].getAlphabet();
	for (size_t i = 0; i < word.size(); i++) {
		IsInAlphabet = false;
		for (size_t j = 0; j < alphabet.size(); j++) {
			if (word[i] == alphabet[j]) IsInAlphabet = true;
		}
		if (!IsInAlphabet) {
			std::cout << "A symbol from the word is not in the automat's alphabet." << std::endl;
			return false;
		}
	}
	Automat CheckFrom;
	if (!IsDeterministic(RecognizeID)) {
		CheckFrom = MakeDFA(RecognizeID);
	}
	int counter;
	int StateIndex = 0;
		for (size_t i = 0; i < word.size(); i++) {
		counter = 0;
		isRecognized = false;
			for (auto it = CheckFrom.States[StateIndex].Transition.begin(); it != CheckFrom.States[StateIndex].Transition.end(); it++) {
				if (it->first == word[i]) {
					std::cout << "Found transition with letter " << word[i] << " , to state: " << it->second << "!" << std::endl;
					StateIndex = it->second;
					isRecognized = true;
					break;
				}
			}
			if (isRecognized = false) {
				returnValue = false;
			break;
			}
		}
		if (!CheckFrom.States[StateIndex].getFinal()) returnValue = false;
		std::cout << "The state at which the word ends is: " << StateIndex << std::endl;
	if (returnValue) return true;
	else return false;
}
Automat Menu::MakeDFA(const int DFAID) {

	std::unordered_set<int> reacheableStates;
	std::queue<int> statesToSearchEpsilonFrom;
	Automat DFA = SaveAutomates.Container[DFAID];
	std::string Alphabet = DFA.getAlphabet();
	Automat New;
	char* usedsymbols = new char(Alphabet.size() + 1);
	for (size_t i = 0; i < Alphabet.size(); i++) {
		usedsymbols[i] = '#';
	}
	int symbolsCounter = 0;
	int Statesize = 1;
	New.setAlphabet(Alphabet);	
	//char* usedSymbols = new char[Alphabet.size() + 1];
	int symbolscounter = 0;
	State NewStart;
	NewStart.setID(0);
	if (DFA.States[0].getFinal()) NewStart.setFinalTrue();
	New.addState(NewStart);
	int newStates = 1;
	New.setStartState(0);
	New.setStatesNumb(1);
	int StatesNumb = DFA.getStatesNumb();
	reacheableStates.insert(SaveAutomates.Container[DFAID].getStartState());
	statesToSearchEpsilonFrom.push(SaveAutomates.Container[DFAID].getStartState());
	while (!statesToSearchEpsilonFrom.empty()) {
		int nextState = statesToSearchEpsilonFrom.front();
		statesToSearchEpsilonFrom.pop();
		for (auto itr = SaveAutomates.Container[DFAID].States[nextState].Transition.find(epsilon); itr != SaveAutomates.Container[DFAID].States[nextState].Transition.end(); itr++) {
			if (reacheableStates.count(itr->second) == 0) {
				statesToSearchEpsilonFrom.push(itr->second);
				reacheableStates.insert(itr->second);
			}
		}
	}
	for (auto it = reacheableStates.begin(); it != reacheableStates.end(); it++) {
		for (size_t j = 0; j < reacheableStates.size(); j++) {
			for (auto itr = SaveAutomates.Container[DFAID].States[*it].Transition.begin(); itr != SaveAutomates.Container[DFAID].States[*it].Transition.end(); itr++) {
				if (itr->first != epsilon and j != *it) {
					DFA.States[*it].Transition.insert(std::pair<char, int>(itr->first, itr->second));
				}
			}
		}
	}
	for (size_t i = 0; i < reacheableStates.size(); i++) {
		DFA.States[i].Transition.erase(epsilon);
	}
	int* StoreID = new int[DFA.getStatesNumb()];
	for (size_t i = 0; i < DFA.getStatesNumb(); i++) {
		StoreID[i] = -1;
	}
	bool isDoubleFound = false;
	int currentNumbStates = StatesNumb;
		for (size_t j = 0; j < Alphabet.size() and !isDoubleFound; j++) {
			isDoubleFound = false;
			for (size_t i = 0; !isDoubleFound; i++) {
			std::vector <int*> ContainAllIDs;
			int repeat = 1;
			bool isFinal = false;
			newStates = 1;
			for (auto it = DFA.States[i].Transition.find(Alphabet[j]); it != DFA.States[i].Transition.end(); it++) {
				if (repeat == 2) {
					auto itprev = prev(it);
					StoreID[itprev->second] = 1;
					StoreID[it->second] = 1;
					isDoubleFound = true;
				}
				if (repeat > 2) {
					StoreID[it->second] = 1;
				}
				if (DFA.States[it->second].getFinal()) isFinal = true;
				repeat++;
			}
			if (isDoubleFound) MakeDet(DFA, New, i, StoreID, newStates, currentNumbStates, isFinal, Alphabet[j], ContainAllIDs, Statesize, Alphabet, usedsymbols, symbolscounter);
		}
	}
	New.setStatesNumb(newStates);
	delete[] usedsymbols;
	return New;
}
void Menu::MakeDet(Automat& automat, Automat& newDFA, const int index, int* UsedStates, int &StatesNumber, const int arrsize, bool Final, char Symbol, std::vector <int*> &Storage, int &size, std::string &alphabet, char* &usedsymbols, int &symbolsCounter) {
	bool CreateNewState = true;
	for (auto itr = Storage.begin(); itr != Storage.end(); itr++) {
		if (equalpointers(*itr, UsedStates, arrsize)) CreateNewState = false;
	}
	if (CreateNewState) {
		State NewState;
		NewState.setID(StatesNumber);
		if (Final) NewState.setFinalTrue();
		newDFA.addState(NewState);
		StatesNumber++;
		size++;
		Storage.push_back(UsedStates);
	}
	newDFA.States[index].Transition.insert(std::pair<char, int>(Symbol, StatesNumber - 1));
	//std::cout << "Making new transitions: " << index << " , with letter: " << Symbol << " , to state number: " << StatesNumber - 1 << std::endl;
	int* newUsedStates = new int[arrsize];
	for (size_t i = 0; i < arrsize; i++) {
		newUsedStates[i] = -1;
	}
	bool FindDifferent = true;
	bool isStateFinal = false;
	bool GetEqual = false;
	int counter = 0;
	for (size_t i = 0; i < arrsize; i++) {
		if (UsedStates[i] == 1) {
			for (auto it = automat.States[i].Transition.find(Symbol); it != automat.States[i].Transition.end(); it++) {
				newUsedStates[it->second] = 1;
				if (automat.States[i].getFinal()) isStateFinal = true;
			}
		}
	}
	for (auto itr = Storage.begin(); itr != Storage.end(); itr++) {
		if (equalpointers(*itr, newUsedStates, arrsize)) {
			FindDifferent = false;
			counter++;
			break;
		}
		else counter++;
	}
	if (FindDifferent) {
			MakeDet(automat, newDFA, StatesNumber - 1, newUsedStates, StatesNumber, arrsize, isStateFinal, Symbol, Storage, size, alphabet, usedsymbols, symbolsCounter);
	}
	if (!FindDifferent) {
		newDFA.States[StatesNumber - 1].Transition.insert(std::pair<char, int>(Symbol, counter));
		//std::cout << "Making new transition: " << StatesNumber - 1 << " , with letter: " << Symbol << " , to state number: " << counter << std::endl;
		usedsymbols[symbolsCounter] = Symbol;
		symbolsCounter++;
	}
	for (size_t i = 0; i < alphabet.size(); i++) {
		if (alphabet[i] != usedsymbols[i]) {
			usedsymbols[i] = alphabet[i];
			std::vector<int*>Storage2;
			int States2 = StatesNumber - 1;
			int size2 = size - 1;
			MakeDet(automat, newDFA, index, UsedStates, States2 , arrsize, Final, alphabet[i], Storage2, size2, alphabet, usedsymbols, symbolsCounter);
		}
	}
	delete[] newUsedStates;
}
bool equalpointers(const int* pointer1, const int* pointer2, int size) {
	for (size_t i = 0; i < size; i++) {
		if (pointer1[i] != pointer2[i]) return false;
	}
	return true;
}
void Menu::Savefile(int ID) {
	std::string alphabet = SaveAutomates.Container[ID].getAlphabet();
	int StatesNumb = SaveAutomates.Container[ID].getStatesNumb();
	int StartState = SaveAutomates.Container[ID].getStartState();
	int NumbFinalStates = SaveAutomates.Container[ID].getNumbFinal();
	int NumbTransitions = SaveAutomates.Container[ID].getNumbTransitions();
	char output[100];
	std::string filename;
	std::cout << "Please enter the file name" << std::endl;
	std::cin >> filename;
	std::ofstream SaveFile(filename, std::ios::app);
	SaveFile << alphabet << std::endl << StatesNumb << std::endl << StartState << std::endl << NumbFinalStates << std::endl;
	for (size_t i = 0; i < StatesNumb; i++) {
		if (SaveAutomates.Container[ID].getFinalStates(i) != -1) SaveFile << SaveAutomates.Container[ID].getFinalStates(i) << " ";
	}
	SaveFile << std::endl;
	for (size_t i = 0; i < StatesNumb; i++) {
		for (std::map<char, int>::iterator it = SaveAutomates.Container[ID].States[i].Transition.begin(); it != SaveAutomates.Container[ID].States[i].Transition.end(); it++) {
			SaveFile << i << " " << it->first << " " << it->second << std::endl;
		}
	}
}
void Menu::CheckState(Automat& obj, std::string alphabet , int id, char Letter, int To, int N, const int* Final) {
	if (isValid(alphabet, Letter)) {
		if (id >= obj.getSize()) {
			State NewState;
			NewState.setID(id);
			for (size_t i = 0; i < N; i++) {
				if (Final[i] == id) {
					NewState.setFinalTrue();
					break;
				}
			}
			NewState.Transition.insert(std::pair<char, int>(Letter, To));
			obj.addState(NewState);
		}
		else {
			obj.States[id].Transition.insert(std::pair<char, int>(Letter, To));
		}
	}
	else {
		std::cout << "The letter is not included of the automat's alphabet. Fatal error #1." << std::endl;
		exit(0);
	}
}
bool Menu::isValid(std::string alphabet, char symb) {
	if (symb == epsilon) return true;
	bool IsFound = false;
	for (size_t i = 0; i < alphabet.length(); i++) {
		if (symb == alphabet[i]) {
			return true;
		}
	}
	return false;
}
bool Menu::IsDeterministic(const int DeterID) {
	for (size_t i = 0; i < SaveAutomates.Container[DeterID].getStatesNumb(); i++) {

		for (std::map<char, int>::iterator it = SaveAutomates.Container[DeterID].States[i].Transition.begin(); it != SaveAutomates.Container[DeterID].States[i].Transition.end(); it++) {
			if (it->first == epsilon) return false;
			for (std::map<char, int>::iterator it2 = SaveAutomates.Container[DeterID].States[i].Transition.begin(); it2 != SaveAutomates.Container[DeterID].States[i].Transition.end(); it2++) {
				if (it != it2 and it->first == it2->first) return false;
			}
		}
	}
	return true;
}
bool Menu::ValidID(const int checkID) {
	if (checkID > automatcounter - 1 or checkID < 0) {
		return false;
	}
	return true;
}
bool Menu::isEmpty(const int EmptyID) {
	if (SaveAutomates.Container[EmptyID].getStatesNumb() == 0) return true;
	if (SaveAutomates.Container[EmptyID].getNumbFinal() == 0) return true;
	return false;
}
void Menu::Union(AutomatContainer& Storage, int &counter, const int UnionID1, const int UnionID2) {
	Automat UnionAutomat;
	std::string UnionedAlphabet;
	int UnionStatesNumb;
	int UnionNumbFinalStates;
	int UnionNumbTransitions;
	int Final_One = Storage.Container[UnionID1].getNumbFinal();
	int Final_Two = Storage.Container[UnionID2].getNumbFinal();
	int States_One = Storage.Container[UnionID1].getStatesNumb();
	int States_Two = Storage.Container[UnionID2].getStatesNumb();
	UnionedAlphabet = Storage.Container[UnionID1].getAlphabet() + Storage.Container[UnionID2].getAlphabet();
	UnionAutomat.setAlphabet(UnionedAlphabet);
	UnionNumbFinalStates = Final_One + Final_Two;
	UnionNumbTransitions = Storage.Container[UnionID1].getNumbTransitions() + Storage.Container[UnionID2].getNumbTransitions() + 2;
	UnionAutomat.setStartState(0);
	State UnionStartState;
	UnionStartState.setID(0);
	int BonusStateOne = 0;
	int BonusStateTwo = 0;
	for (std::multimap<char, int>::iterator it = Storage.Container[UnionID1].States[0].Transition.begin(); it != Storage.Container[UnionID1].States[0].Transition.end(); it++)
	{
		if (it->second == 0) {
			BonusStateOne = 1;
			UnionStartState.Transition.insert(std::pair <char, int>(it->first, 1));
		}
	}
	for (std::multimap<char, int>::iterator it = Storage.Container[UnionID2].States[0].Transition.begin(); it != Storage.Container[UnionID2].States[0].Transition.end(); it++)
	{
		if (it->second == 0) {
			BonusStateTwo = 1;
			UnionStartState.Transition.insert(std::pair <char, int>(it->first, 1 + States_One - 1 + BonusStateOne));
		}
	}
	UnionStatesNumb = States_One + States_Two + 1 - 2 + BonusStateOne + BonusStateTwo;
	int* UnionFinalStates = new int[UnionStatesNumb];
	int* UnionFillStates = new int[UnionStatesNumb];
	for (size_t i = 0; i < UnionStatesNumb; i++) {
		UnionFillStates[i] = 0;
	}
	for (size_t i = 0; i < States_One; i++) {
		if (Storage.Container[UnionID1].States[i].getFinal()) {
			UnionFinalStates[i + BonusStateOne] = i + BonusStateOne;
		}
		else UnionFinalStates[i + BonusStateOne] = -1;
	}
	for (size_t i = 0; i < States_Two; i++) {
		if (Storage.Container[UnionID2].States[i].getFinal()) {
			UnionFinalStates[i + States_One - 1 + BonusStateOne + BonusStateTwo] = i + States_One - 1 + BonusStateOne + BonusStateTwo;
		}
		else UnionFinalStates[i + States_One - 1 + BonusStateOne + BonusStateTwo] = -1;
	}
	if ((BonusStateOne == 0 and Storage.Container[UnionID1].States[0].getFinal()) or (BonusStateTwo == 0 and Storage.Container[UnionID2].States[0].getFinal()))
	{
		UnionStartState.setFinalTrue();
		UnionFinalStates[0] = 0;
	}
	UnionAutomat.addState(UnionStartState);
	UnionAutomat.setStatesNumb(UnionStatesNumb);
	UnionAutomat.setNumbFinal(UnionNumbFinalStates);
	UnionAutomat.setFinalStates(UnionFinalStates);
	for (size_t i = 0; i < States_One; i++) {
		for (std::multimap<char, int>::iterator it = Storage.Container[UnionID1].States[i].Transition.begin(); it != Storage.Container[UnionID1].States[i].Transition.end(); it++)
		{
			if (it->second == 0 and i != 0) {
				CheckState(UnionAutomat, UnionedAlphabet, i + BonusStateOne, it->first, 0, UnionStatesNumb, UnionFinalStates);
				UnionFillStates[i + BonusStateOne] = 1;
			}
			else {
				CheckState(UnionAutomat, UnionedAlphabet, i + BonusStateOne, it->first, it->second + BonusStateOne, UnionStatesNumb, UnionFinalStates);
				UnionFillStates[i + BonusStateOne] = 1;
			}
		}
	}
	for (size_t i = 0; i < States_Two; i++) {
		for (std::multimap<char, int>::iterator it = Storage.Container[UnionID2].States[i].Transition.begin(); it != Storage.Container[UnionID2].States[i].Transition.end(); it++)
		{
			if (i == 0) {
				CheckState(UnionAutomat, UnionedAlphabet, 0, it->first, it->second + BonusStateOne + States_One - 1, UnionStatesNumb, UnionFinalStates);
				UnionFillStates[0] = 1;
			}
			else {
				if (it->second == 0) {
					CheckState(UnionAutomat, UnionedAlphabet, i + States_One - 1 + BonusStateTwo + BonusStateOne, it->first, 0, UnionStatesNumb, UnionFinalStates);
					UnionFillStates[i + States_One - 1 + BonusStateTwo + BonusStateOne] = 1;
				}
				else {
					CheckState(UnionAutomat, UnionedAlphabet, i + States_One - 1 + BonusStateTwo + BonusStateOne, it->first, it->second + BonusStateOne + States_One - 1 + BonusStateTwo, UnionStatesNumb, UnionFinalStates);
					UnionFillStates[i + States_One - 1 + BonusStateTwo + BonusStateOne] = 1;
				}
			}
		}
	}
	for (size_t i = 0; i < UnionStatesNumb; i++) {
		if (UnionFillStates[i] == 0) {
			State FillState;
			FillState.setID(i);
			if (UnionFinalStates[i] == i) FillState.setFinalTrue();
			UnionAutomat.addState(FillState);
		}
	}
	Storage.addAutomat(UnionAutomat);
	Storage.Container[counter].setID(counter);
	counter++;
	delete[] UnionFinalStates;
	delete[] UnionFillStates;
}
void Menu::Concat(AutomatContainer& Storage, int &counter,  const int ConcatID1, const int ConcatID2) {
	Automat ConcatAutomat;
	std::string ConcatAlphabet;
	int ConcatStatesNumb;
	int ConcatNumbTransitions;
	int Final_One = Storage.Container[ConcatID1].getNumbFinal();
	int Final_Two = Storage.Container[ConcatID2].getNumbFinal();
	int States_One = Storage.Container[ConcatID1].getStatesNumb();
	int States_Two = Storage.Container[ConcatID2].getStatesNumb();
	int ConcatStartState = Storage.Container[ConcatID1].getStartState();
	ConcatAlphabet = Storage.Container[ConcatID1].getAlphabet() + Storage.Container[ConcatID2].getAlphabet();
	ConcatStatesNumb = Storage.Container[ConcatID1].getStatesNumb() + Storage.Container[ConcatID2].getStatesNumb();
	ConcatAutomat.setAlphabet(ConcatAlphabet);
	ConcatAutomat.setStartState(ConcatStartState);
	ConcatAutomat.setStatesNumb(ConcatStatesNumb);
	ConcatAutomat.setNumbFinal(Final_Two);
	ConcatNumbTransitions = Storage.Container[ConcatID1].getNumbTransitions() + Storage.Container[ConcatID2].getNumbTransitions() + Final_One;
	int* FillStates = new int[ConcatStatesNumb];
	int* ConcatFinalStates = new int[ConcatStatesNumb];
	for (size_t i = 0; i < ConcatStatesNumb; i++) {
		FillStates[i] = 0;
	}
	for (size_t i = 0; i < States_One; i++) {
		if (Storage.Container[ConcatID1].States[i].getFinal()) {
			ConcatFinalStates[i] = i;
		}
		else ConcatFinalStates[i] = -1;
	}
	for (size_t i = 0; i < States_Two; i++) {
		if (Storage.Container[ConcatID2].States[i].getFinal()) {
			ConcatFinalStates[i + States_One] = i + States_One;
		}
		else ConcatFinalStates[i + States_One] = -1;
	}
	for (size_t i = 0; i < States_One; i++) {
		for (std::multimap<char, int>::iterator it = Storage.Container[ConcatID1].States[i].Transition.begin(); it != Storage.Container[ConcatID1].States[i].Transition.end(); it++)
		{
			CheckState(ConcatAutomat, ConcatAlphabet, i, it->first, it->second, ConcatStatesNumb, ConcatFinalStates);
			FillStates[i] = 1;
		}
	}
	for (size_t i = 0; i < ConcatStatesNumb; i++) {
		if (FillStates[i] == 0) {
			State FillState;
			FillState.setID(i);
			if (ConcatFinalStates[i] == i and i > States_One) FillState.setFinalTrue();
			ConcatAutomat.addState(FillState);
		}
	}
	for (size_t i = 0; i < States_Two; i++) {
		for (std::multimap<char, int>::iterator it = Storage.Container[ConcatID2].States[i].Transition.begin(); it != Storage.Container[ConcatID2].States[i].Transition.end(); it++)
		{
			CheckState(ConcatAutomat, ConcatAlphabet, i + States_One, it->first, it->second + States_One, ConcatStatesNumb, ConcatFinalStates);
			FillStates[i + States_One] = 1;
		}
	}
	for (size_t i = 0; i < States_One; i++) {
		if (Storage.Container[ConcatID1].States[i].getFinal()) {
			CheckState(ConcatAutomat, ConcatAlphabet, i, epsilon, Storage.Container[ConcatID2].getStartState() + States_One, ConcatStatesNumb, ConcatFinalStates);
		}
	}
	for (size_t i = 0; i < States_One; i++) {
		ConcatFinalStates[i] = -1;
		ConcatAutomat.States[i].setFinalFalse();
	}

	ConcatAutomat.setFinalStates(ConcatFinalStates);
	Storage.addAutomat(ConcatAutomat);
	Storage.Container[counter].setID(counter);
	counter++;
	delete[] ConcatFinalStates;
	delete[] FillStates;
}
void Menu::Un(AutomatContainer& Storage, int &counter, const int UnID1) {
	Automat UnAutomat;
	std::string UnAlphabet = Storage.Container[UnID1].getAlphabet();
	int UnStatesNumb = Storage.Container[UnID1].getStatesNumb() + 2;
	int UnNumbFinalStates = Storage.Container[UnID1].getNumbFinal();
	int UnNumbTransitions = Storage.Container[UnID1].getNumbTransitions() + UnNumbFinalStates * 2 + 2;
	int* UnFinalStates = new int[UnStatesNumb];
	UnAutomat.setAlphabet(UnAlphabet);
	UnAutomat.setStatesNumb(UnStatesNumb);
	UnAutomat.setNumbFinal(UnNumbFinalStates);
	UnAutomat.setNumbTransitions(UnNumbTransitions);
	State UnStartState;
	UnStartState.setID(0);
	UnStartState.Transition.insert(std::pair<char, int>(epsilon, Storage.Container[UnID1].getStartState() + 1));
	UnFinalStates[0] = -1;
	State UnFinalState;
	UnFinalState.setFinalTrue();
	UnFinalState.setID(UnStatesNumb - 1);
	UnStartState.Transition.insert(std::pair<char, int>(epsilon, UnStatesNumb - 1));
	UnAutomat.addState(UnStartState);
	for (size_t i = 0; i < UnStatesNumb - 2; i++) {
		if (Storage.Container[UnID1].States[i].getFinal()) {
			UnFinalStates[i + 1] = i + 1;
		}
		else UnFinalStates[i + 1] = -1;
	}
	UnAutomat.setFinalStates(UnFinalStates);
	for (size_t i = 0; i < UnStatesNumb - 2; i++) {
		for (std::multimap<char, int>::iterator it = Storage.Container[UnID1].States[i].Transition.begin(); it != Storage.Container[UnID1].States[i].Transition.end(); it++)
		{
			CheckState(UnAutomat, UnAlphabet, i + 1, it->first, it->second + 1, UnStatesNumb, UnFinalStates);
		}
	}
	for (size_t i = 0; i < UnStatesNumb - 2; i++) {
		if (Storage.Container[UnID1].States[i].getFinal()) {
			CheckState(UnAutomat, UnAlphabet, i + 1, epsilon, Storage.Container[UnID1].getStartState() + 1, UnStatesNumb, UnFinalStates);
			CheckState(UnAutomat, UnAlphabet, i + 1, epsilon, UnStatesNumb - 1, UnStatesNumb, UnFinalStates);
		}
	}
	UnAutomat.addState(UnFinalState);
	Storage.addAutomat(UnAutomat);
	Storage.Container[counter].setID(counter);
	counter++;
	delete[] UnFinalStates;
}
