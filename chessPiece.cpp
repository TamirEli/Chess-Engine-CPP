#include "chessPiece.h"


int ChessPiece::getPlaceNums(string p)
{
	char letter = p[0];
	int numletter = int(letter)- A_ASCII;
	char numberInBoard = p[1];
	int numInBoard = int(numberInBoard) - ZERO_ASCII;
	return numletter * 10 + numInBoard;
}

void ChessPiece::changeMoved()
{
	this->_moved = true;
}

//this func is setting the type of the chessPiece
void ChessPiece::setType(string type)
{
	if (type == "K" ||type=="k" || type == "Q" ||type=="q" || type == "k" || type == "K" || type == "R" ||type=="r" || type == "B" ||type=="b" || type == "P" || type=="p")
	{
		_type = type;
	}
	
}

//C'tor
ChessPiece::ChessPiece(string place,string type, Player owner)
{
	_place = place;
	_moved = false;
	_owner = new Player(owner.getColor());
	if (_owner->getColor() == "black")
	{
		_type = type;
	}
	else
	{
		_type = toupper(type[0]);
	}
}

//D'tor
ChessPiece::~ChessPiece()
{
	_place = "";
	_type = "";
}

//a function return the place 
string ChessPiece::getPlace()const
{
	return _place;
}

//a fuction return the type
string ChessPiece::getType () const
{
	return _type;
}


//this func returns the owner
Player &ChessPiece::getOwner() const
{
	return *_owner;
}

bool ChessPiece::getMoved() const
{
	return _moved;
}



