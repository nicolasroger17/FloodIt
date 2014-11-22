#include "grid.h"
#include "cell.h"

using namespace std;

Grid::Grid() :theGrid(0), gridSize(0), td(0), theWindow(0){}; // default constructor

Grid::~Grid(){
	for (int i = 0; i < gridSize * gridSize; i++) // loop to delete each Cell
		delete theGrid[i];
	delete[] theGrid; // delete the array
	delete theWindow; // delete the window
	delete td; // delete the textdisplay
};

/*
* The following method is used to determine if the game has been won
* An, inefficient implementation would be to use nested for loops to determine
* that all Cells in theGrid are of the same color.
* A more efficient approach is to compute this information during the game as
* Cells change colors
* Look through the textdisplay.h file for hints on how to do this
*/
bool Grid::isWon(){
	return td->isFilled(); // textDisplay handles the completion of the grid
};

void Grid::init(int n){
	td = new TextDisplay(n); // create the TextDisplay
	theWindow = new Xwindow(SIZE, SIZE + 100); // create the Window
	gridSize = n; // set the size of the grid
	int square = SIZE / n; // calculate the witdh of the cell
	
	theGrid = new Cell*[n * n]; // create the grid
	for (int i = 0; i < n * n; i++)
		theGrid[i] = new Cell(); // instantiate each Cell

	for (int i = 0; i < n * n; i++){
		int r = i / n; // define the row
		int c = i % n; // define the column

		theGrid[i]->setDisplay(td); // set the display
		theGrid[i]->setXwindow(theWindow); // set the window
		theGrid[i]->setCoords(r, c, c * square, r * square, square); // set the coords
		theGrid[i]->setState(0); // set the default state and push it to the textDisplay and Window
		if (i > n) // above neighbour
			theGrid[i]->addNeighbour(theGrid[i - n]);
		if (i % n > 0) // left neighbour
			theGrid[i]->addNeighbour(theGrid[i - 1]);
		if (i % n < n - 1) // right neighbour
			theGrid[i]->addNeighbour(theGrid[i + 1]);
		if (i < n * (n - 1)) // below neighbour
			theGrid[i]->addNeighbour(theGrid[i + n]);
	}
};                 // Sets up an n x n grid.  Clears old grid, if necessary.

void Grid::change(const int & state){
	theGrid[0]->notify(state);
};  // Notify Cell (0,0) of the change to new state: state 

void Grid::init(int r, int c, int state){
	if (r >= 0 && c >= 0 && r < gridSize && c < gridSize){ // check if the position is valid
		theGrid[r * gridSize + c]->setState(state); // call two times to set the prevState 
		theGrid[r * gridSize + c]->setState(state); // to the same value
	}
}; //set the state for r,c to state

void Grid::displayResult(std::string s){
	theWindow->drawString(SIZE / 2, SIZE + 50, s); // print Won or Lost
}

std::ostream &operator<<(std::ostream &out, const Grid &g){
	out << *g.td; // print the textdisplay
	return out;
};
