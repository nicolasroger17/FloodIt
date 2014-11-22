#include "cell.h"
#include <stdlib.h>

using namespace std;

void Cell::notifyDisplay(){
	td->notify(r, c, state + 48); // int + 48 => char
};					    //notify the TextDisplay of the change

void Cell::draw(){
	window->fillRectangle(x, y, width, height, state); // change the cell color
};

Cell::Cell() :state(0), prevState(0), numNeighbours(0), r(0), c(0), td(0), x(0), y(0), width(0), height(0), window(0){};               // Default constructor

int Cell::getState(){
	return state;
};

void Cell::setState(const int& change){
	prevState = state;
	state = change;

	notifyDisplay(); // display in console
	draw(); // display on window
}

void Cell::setCoords(const int r, const int c, const int x, const int y, const int square){ // initialize most variables
	this->x = x;
	this->y = y;
	width = square;
	height = square;

	this->r = r;
	this->c = c;
}

//possible setter for partb when we have XWindow
//void setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w);

void Cell::setDisplay(TextDisplay * t){
	this->td = t;
}

void Cell::setXwindow(Xwindow * w){
	this->window = w;
}

void Cell::addNeighbour(Cell *neighbour){
	if (numNeighbours < maxNeighbours){
		neighbours[numNeighbours] = neighbour;
		numNeighbours += 1;
	}	
}

/*
* The following methods are provided as a hint towards implementing the notification
* You should try to use the methods with the given signatures.
*
* If you feel the need to change the *signature* of the method (not the name) you may
* do so but MUST provide a comprehensive explanation in your code why you felt the change
* was necessary
*/


/*
* Intended to be called only by the grid class for changing the state of the 0 0 cell
*/
void Cell::notify(const int & change){
	setState(change);
	for (int i = 0; i < numNeighbours; i++)
		neighbours[i]->notify(state, prevState);
}

/*
* Intended to be called by Cells to notify their neighbors
* current: this cells current(new) state
* previous: this cells past state
*/
void Cell::notify(const int & current, const int & previous){
	if (state == previous && state != current){
		setState(current);
		for (int i = 0; i < numNeighbours; i++)
			neighbours[i]->notify(state, prevState);
	}
}
