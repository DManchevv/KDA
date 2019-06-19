#include "Menu.h"
#include <fstream>
#include <sstream>
#include "Automat.h"
#include "AutomatContainer.h"
#include "State.h"
AutomatContainer SaveAutomates;
int automatcounter = 0;
void Introduction() {
	std::cout << "Welcome to my project's menu. Here are the available commands: " << std::endl;
	std::cout << "Open - opens a new file for a new DFA." << std::endl;
	std::cout << "List - prints the ID of all DFAs in the system." << std::endl;
	std::cout << "Print - prints all transitions in the DFA with the selected ID." << std::endl;
	std::cout << "Save - saves an automat in a file." << std::endl;
	std::cout << "Union - unions two automates by their id. " << std::endl;
}
void StartMenu() {
	char alphabet[40];
	int numb;
	char letter;
	std::string storeLetter;
	int To;
	int StatesNumb;
	int StartState;
	int NumbFinalStates;
	int FinalStates[100];
	int NumbTransitions; 
	std::ifstream File;
	std::string commands;
	while (true) {
		std::cout << "Please enter a command." << std::endl;
		std::cin >> commands;
		if (commands == "Open" or commands == "open") {
			std::string filename;
			std::cout << "Please enter the path of the file you want to open." << std::endl;
			std::cin >> filename;
			File.open(filename);
			if (!File) {
				std::cout << "Unable to open file";
				exit(1);
			}
			if (File.is_open()) {
				Automat newAutomat;
				File >> alphabet >> StatesNumb >> StartState >> NumbFinalStates;
				newAutomat.setAlphabet(alphabet);
				newAutomat.setStatesNumb(StatesNumb);
				newAutomat.setStartState(StartState);
				newAutomat.setNumbFinal(NumbFinalStates);
				//	std::cout << "Your automat's alphabet is: " << alphabet << std::endl;
				//	std::cout << "The number of the states in the automat is: " << StatesNumb << std::endl;
				//	std::cout << "The starting state of the automat is on position: " << StartState << std::endl;
				//	std::cout << "The Number of the final states in the automat is: " << NumbFinalStates << std::endl;
				//FinalStates = new int[StatesNumb + 1];
				//std::cout << "The FinalStates of the automat have IDs: ";
				int checkFinal;
				for (size_t i = 0; i < NumbFinalStates; i++) {
					File >> checkFinal;
					FinalStates[checkFinal] = checkFinal;
				}
				for (size_t i = 0; i < StatesNumb; i++) {
					if (FinalStates[i] != i) FinalStates[i] = -1;
				}
				newAutomat.setFinalStates(FinalStates);
				std::cout << std::endl;
				while (!File.eof()) {
					File >> numb >> letter >> To;
					storeLetter += letter;
					CheckState(newAutomat, alphabet, numb, letter, To, StatesNumb, FinalStates);
				}
				SaveAutomates.addAutomat(newAutomat);
				SaveAutomates.Container[automatcounter].setID(automatcounter);
			}
			File.close();
			automatcounter++;
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
		if (commands == "Save" or commands == "save"){
			int saveID;
			std::cout << "Enter the new ID of the new automat." << std::endl;
			std::cin >> saveID;
			Savefile(saveID);
		}
		/*if (commands == "Recognize" or commands == "Recognize") {
			int RecognizeID;
			bool isRecognized = false;
			std::string word;
			std::cout << "Enter the ID of the automat you want to use." << std::endl;
			std::cin >> RecognizeID;
			std::cout << "Enter the word you want to check." << std::endl;
			std::cin >> word;
			for (size_t i = 0; i < SaveAutomates.Container[RecognizeID].getSize();) {
				for (std::multimap<char, int>::iterator it = SaveAutomates.Container[RecognizeID].States[i].Transition.begin(); it != SaveAutomates.Container[RecognizeID].States[i].Transition.end(); it++) {
					if (word[i] == it->first) {
						i = it->second;
					}
				}
			}
		}*/
		if (commands == "Union" or commands == "union") {
			int UnionID1;
			std::cout << "Please enter the ID of the first automat. " << std::endl;
			std::cin >> UnionID1;
			int UnionID2;
			std::cout << "Please enter the ID of the second automat. " << std::endl;
			std::cin >> UnionID2;
			Automat UnionAutomat;
			std::string UnionedAlphabet;
			int UnionStatesNumb;
			int UnionNumbFinalStates;
			int UnionNumbTransitions;
			int Final_One = SaveAutomates.Container[UnionID1].getNumbFinal();
			int Final_Two = SaveAutomates.Container[UnionID2].getNumbFinal();
			//UnionedAlphabet = SaveAutomates.Container[UnionID1].getAlphabet() + SaveAutomates.Container[UnionID2].getAlphabet();
			UnionStatesNumb = SaveAutomates.Container[UnionID1].getStatesNumb() + SaveAutomates.Container[UnionID2].getStatesNumb() + 1;
			UnionNumbFinalStates = Final_One + Final_Two;
			std::cout << UnionNumbFinalStates;
			UnionNumbTransitions = SaveAutomates.Container[UnionID1].getNumbTransitions() + SaveAutomates.Container[UnionID2].getNumbTransitions() + 2;
			int* UnionFinalStates = new int[UnionNumbFinalStates + 1];
			/*for (size_t i = 0; i < Final_One; i++) {
				if (i == SaveAutomates.Container[UnionID1].getFinalStates(i)) {
					UnionFinalStates[i + 1] = i;
				}
				else UnionFinalStates[i + 1] = -1;
			}
			for (size_t i = 0; i < Final_Two; i++) {
				if (i == SaveAutomates.Container[UnionID2].getFinalStates(i)) {
					UnionFinalStates[i + Final_One + 1] = i + Final_One;
				}
				else UnionFinalStates[i + Final_One + 1] = -1;
			}
			for (size_t i = 0; i < UnionNumbFinalStates; i++) {
				std::cout << UnionFinalStates[i] << std::endl;
			}
			UnionAutomat.setStartState(0);
			UnionAutomat.setFinalStates(UnionFinalStates);
			UnionAutomat.setStatesNumb(UnionStatesNumb);
			SaveAutomates.addAutomat(UnionAutomat);
			SaveAutomates.Container[automatcounter].setID(automatcounter);
			automatcounter++;*/
			//UnionAutomat.setAlphabet()
		}
		if (commands == "Exit" or commands == "exit") {
			exit(1);
		}
	}
}
template <typename T>
std::string tostring(T val)
{
	std::stringstream stream;
	stream << val;
	return stream.str();
}
void Savefile(int ID) {
	int numb;
	char* alphabet = new char[40];
	char letter;
	int To;
	int StatesNumb;
	int StartState;
	int NumbFinalStates;
	int* FinalStates;
	int NumbTransitions;
	char output[100];
	std::string filename;
	std::cout << "Please enter the file name" << std::endl;
	std::ofstream SaveFile(filename, std::ios::app);
	//SaveFile << ID << std::endl;
	std::cout << "Enter the alphabet." << std::endl;
	std::cin >> alphabet;
	std::cout << "Enter the number of states." << std::endl;
	std::cin >> StatesNumb;
	std::cout << "Enter the ID of the starting state. " << std::endl;
	std::cin >> StartState;
	std::cout << "Enter the number of the final states. " << std::endl;
	std::cin >> NumbFinalStates;
	SaveFile << alphabet << std::endl << StatesNumb << std::endl << StartState << std::endl << NumbFinalStates << std::endl;
	std::cout << "Enter the IDs of the final states. " << std::endl;
	FinalStates = new int[NumbFinalStates];
	for (size_t i = 0; i < NumbFinalStates; i++) {
		std::cin >> FinalStates[i];
		SaveFile << FinalStates[i] << " ";
	}
	SaveFile << std::endl;
	std::cout << "Enter the number of the automat's transitions. " << std::endl;
	std::cin >> NumbTransitions;
	std::cout << "Enter the transitions (from which state's ID, with what symbol, to which state's ID" << std::endl;
	for (size_t i = 0; i < NumbTransitions; i++) {
		std::cin >> numb >> letter >> To;
		SaveFile << numb << " " << letter << " " << To << std::endl;
	}
}
void CheckState(Automat& obj, const char* alphabet, int id, char Letter, int To, int N, const int* Final) {
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
		else
		{
			obj.States[id].Transition.insert(std::pair<char, int>(Letter, To));
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