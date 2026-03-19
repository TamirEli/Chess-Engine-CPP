#include "Rook.h"

Rook::Rook(string place, Player owner) : ChessPiece(place, "r", owner)
{
}

bool Rook::setPlace(string placeToMove, Board board)
{
	//this part is setting the row and the column of the Rook before the move
	string numPlaceTemp = "";
	string place = this->getPlace();
	char letterPlace = place[0];
	numPlaceTemp += (place[1] - ZERO_ASCII);
	int numPlace = int(numPlaceTemp[0]);
	int colSource = letterPlace - 'A';
	int rowSource = numPlace - 1;

	//this part is setting the row and the column of the destination Rook 
	string numPlaceDestPlace = "";
	char letterPlaceDest = placeToMove[0];
	numPlaceDestPlace += (placeToMove[1] - ZERO_ASCII);
	int numPlaceDest = int(numPlaceDestPlace[0]);
	int colDest = letterPlaceDest - 'A';
	int rowDest = numPlaceDest - 1;

	int col = 0;
	bool valid = true;
	int i = 0;//for loops

	//This part of code checks if the move is valid
	if (letterPlace != letterPlaceDest && numPlace != numPlaceDest) { return false; }

	//moving up and down
	if (letterPlace == letterPlaceDest) {
		board.updatePlace(colSource, colDest, rowSource, rowDest);
	}

	//moving to the sides
	else if (numPlace == numPlaceDest) {
		board.updatePlace(colSource, colDest, rowSource, rowDest);
	}
}



