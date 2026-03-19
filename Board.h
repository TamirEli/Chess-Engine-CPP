#pragma once
#include <iostream>
#include "chessPiece.h"
#include <stdlib.h>     /* srand, rand */
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include <cstring>
#include <cctype>


class Rook;
#define SIZE 8
class Board
{
private:
	bool _turn = true;//true -white turn, false - black turn
	ChessPiece* _board[SIZE][SIZE];
public:
	//C'tor
	Board(string startBoard);

	//D'tor
	~Board();


	//methods
	void printBoard() const;
	Board* updatePlace(int startCol, int endCol, int startRow, int endRow);
	string checkTheWay(int startCol, int endCol, int startRow, int endRow);
	bool checkCol(int startCol, int endCol, int startRow, int endRow);
	bool checkRow(int startCol, int endCol, int startRow, int endRow);
	bool checkDiagonal(int startCol,int endCol,int startRow,int endRow);
	bool selfChess(int row,int col);
	bool checkOnEnemy(int row, int col);
	bool noPlayer(int row,int col)const;
	bool noDestSelfPlayer(int startRow, int startCol,int endRow,int endCol)const;
	void changeMoved(int row, int col);
	bool checkValidTurn(int row, int col);
	void changeTurn();

};