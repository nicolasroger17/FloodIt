#include "cell.h"
#include "grid.h"
#include "textdisplay.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(){
	string s;
	Grid * grid = new Grid(); // grid
	int leftMoves = 0; // number of moves
	bool gameStarted = false; // store if new has been called

	while (1) {
		getline(cin, s);
		if (cin.fail()) break;

		if (s[0] == 'n'){ // new
			if(!gameStarted){ // only if game not started
				s = s.replace(s.begin(), s.begin() + 4, "");
				delete grid;
				grid = new Grid();
				grid->init(atoi(s.c_str()));
			}
		}
		else if (s[0] == 'g'){ // game
			s = s.replace(s.begin(), s.begin() + 5, "");
			leftMoves = atoi(s.c_str()); // get the number
			gameStarted = true;
			cout << leftMoves << " move" << ((leftMoves != 1) ? "s" : "") << " left" << endl;
		}
		else if (s[0] == 's'){ //switch
			if (gameStarted){ // only if game started
				s = s.replace(s.begin(), s.begin() + 7, "");
				grid->change(atoi(s.c_str()));
				cout << *grid;
				cout << leftMoves << " move" << ((leftMoves != 1) ? "s" : "") << " left" << endl;
			}
		}
		else if (s[0] == 'i'){ // include or init
			if (s[2] == 'i'){ // init
				while (getline(cin, s)){
					if (cin.fail() || s == "-1 -1")
						break;
					int arr[3];
					istringstream iss(s);
					iss >> arr[0] >> arr[1] >> arr[2]; // cascade assignment of the coords
					grid->init(arr[0], arr[1], arr[2]);
				}
			}
			else if (s[2] == 'c'){ // include
				s = s.replace(s.begin(), s.begin() + 8, "");
				ifstream in(s.c_str()); // open the file
				int arr[3];
				while (!in.eof()){
					in >> arr[0] >> arr[1] >> arr[2]; // cascade assignment of the coords
					grid->init(arr[0], arr[1], arr[2]);
				}
			}
			cout << *grid;
		}
		else if (s[0] == '?'){ // display help
			cout << "White: 0" << endl << "Black: 1" << endl;
			cout << "Red:   2" << endl << "Green: 3" << endl;
			cout << "Blue:  4" << endl;
		}

		if (gameStarted){
			if (grid->isWon()){
				cout << "Won" << endl;
				grid->displayResult("Won !");
				break;
			}
			else if (leftMoves == 0){
				cout << "Lost" << endl;
				grid->displayResult("Lost !");
				break;
			}
			leftMoves--; // decrease moves count
		}
	}
	char c; // wait before exiting 
	cin >> c; //waiting for ctrl+d
	delete grid; // delete the grid
	return 0;
}
