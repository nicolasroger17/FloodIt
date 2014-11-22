#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(int n):gridSize(n){
	colourCount[0] = n*n; // sets the colour count of 0 to the maximum
	theDisplay = new char*[n]; // create the first array (rows)
	for (int i = 0; i < n; i++){
		theDisplay[i] = new char[n + 1]; // create the column + end of char
		for (int j = 0; j < n; j++)
			theDisplay[i][j] = '0'; // default value to 0
		theDisplay[i][n] = '\0'; // end of char
	}
}
	/*
	* The TextDisplay is an observer of each Cell. Cells call notify to
	* update the (r,c) location to be ch
	*/
void TextDisplay::notify(int r, int c, char ch){
	theDisplay[r][c] = ch; // modify the textDisplay
}

	/*
	* To check the win condition, the Grid calls the isFilled
	* method which returns true if all cells are the same color
	*/
bool TextDisplay::isFilled(){
	for (int i = 0; i < 5; i++){
		if (colourCount[i] == gridSize*gridSize) // return true if only one color is represented
			return true;
	}
	return false;
}

TextDisplay::~TextDisplay(){
	for (int i = 0; i < gridSize; i++)
		delete[] theDisplay[i]; // delete each column
	delete[] theDisplay; // delete the array
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
	td.colourCount[0] = td.colourCount[1] = td.colourCount[2] = td.colourCount[3] = td.colourCount[4] = 0; // reset each color count
	for (int i = 0; i < td.gridSize; i++){
		for (int j = 0; j < td.gridSize; j++){
			out << td.theDisplay[i][j]; // add the cell to the output
			// char to int, haven't found anything better
			int v;
			stringstream is;
			is << td.theDisplay[i][j];
			is >> v;
			// 
			td.colourCount[v]++; // increase the color of the cell
		}
		out << endl; // jump line
	}
	return out;
}