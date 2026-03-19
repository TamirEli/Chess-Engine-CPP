#pragma once
#include "chessPiece.h"
#include "Board.h"
#include <string>
#define  ZERO_ASCII 48

class Board;
#define SIZE 8
class Rook : public ChessPiece
{
public:
	//C'tor
	Rook(string place, Player owner);

	//setter
	virtual bool setPlace(string placeToMove,Board board);
	//bool checkMove(string placeToMove, ChessPiece* board[SIZE][SIZE]);
};


