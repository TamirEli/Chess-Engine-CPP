#pragma once
#include <iostream>

using std::string;

class Player
{
private:
	string _color;
	
public:
	//C'tor
	Player(string color);

	//D'tor
	~Player();

	//setter
	void setColor(string color);

	//getter
	string getColor() const;
};

