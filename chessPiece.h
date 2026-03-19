#pragma once
#include <iostream>
#include "Player.h"
#include <cctype>


using std::string;

#define ZERO_ASCII 48
#define A_ASCII 97
#define SIZE 8
class ChessPiece
{
private:
	//fields
	string _place;
	string _type;
	Player* _owner;
	bool _moved;
public:
	//C'tor
	ChessPiece(string place, string type, Player owner);
	
	//D'tor
	~ ChessPiece(); 

	//getters
	string getPlace() const;
	string getType() const;
	Player &getOwner()const;
	bool getMoved()const;

	//static method

	static int getPlaceNums(string p);


	//method
	void changeMoved();

	//setter
	void setType(string);
};

