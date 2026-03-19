#pragma once
#include "chessPiece.h"
#include <string>

#define SIZE 8

class King : public ChessPiece
{
private:
	bool _check = false;
public:
	//C'tor
	King(string place, Player owner);

	//set place
	bool setPlace(string placeToMove, ChessPiece* Board[SIZE][SIZE]);
};

