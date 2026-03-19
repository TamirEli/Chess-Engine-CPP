#include "King.h"
#include <cstdlib>

King::King(string place, Player owner) :ChessPiece(place, "k", owner)
{
}

bool King::setPlace(string placeToMove, ChessPiece* Board[SIZE][SIZE])
{
	//this part is setting the row and the column of the Rook before the move
	string place = this->getPlace();
	char letterPlace = place[0];
	string numPlaceTemp = place[1] + "";
	int numPlace = std::stoi(numPlaceTemp);

	//this part is setting the row and the column of the destination Rook 
	char letterPlaceDest = placeToMove[0];
	string numPlaceDestPlace = placeToMove[1] + "";
	int numPlaceDest = std::stoi(numPlaceDestPlace);

	bool valid = true;
	int col = letterPlace - 'A';

	//this part is checking if the move of the king is valid place or not
    if(!(abs(letterPlace-letterPlaceDest)<=1&&abs(numPlace-numPlaceDest)<=1)) {
		valid = false;
	}

	if(Board[col][numPlaceDest - 1] != nullptr) {
		if (Board[col][numPlaceDest - 1]->getOwner().getColor() == this->getOwner().getColor()) {
			valid = false;
		}
	}
	return valid;
}
