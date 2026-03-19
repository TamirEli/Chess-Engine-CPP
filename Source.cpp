/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include <string.h>
#include "chessPiece.h"
#include "Board.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); // The white player should start
	Board* b1 = new Board("rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0");
	p.sendMessageToGraphics(msgToGraphics);   // send the board string
	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		string source = msgFromGraphics.substr(0,2);
		string dest = msgFromGraphics.substr(2, 2);
		int numSource = ChessPiece::getPlaceNums(source);
		int numDest = ChessPiece::getPlaceNums(dest);
		int sourceCol = numSource / 10;
		int sourceRow = abs(numSource % 10-8);
		int destCol = numDest / 10;
		int destRow = abs(numDest % 10-8);


		

		string code = b1->checkTheWay(sourceCol, destCol, sourceRow, destRow);

		
		if (sourceCol == destCol && sourceRow == destRow)
		{
			code = "7";
		}
		if (b1->noPlayer(sourceRow, sourceCol))
		{
			code = "2";
		}
		if (b1->noDestSelfPlayer(sourceRow, sourceCol, destRow, destCol))
		{
			code = "3";
		}
		if (!b1->checkValidTurn(sourceRow, sourceCol))
		{
			code = "6";
		}
		if (code == "0")
		{
			b1->updatePlace(sourceCol, destCol, sourceRow, destRow);
			if (b1->selfChess(destRow, destCol))
			{
				b1->updatePlace(destCol, sourceCol, destRow,sourceRow );
				code = "4";
			}
		}
		if (code == "0")
		{
			if (b1->checkOnEnemy(destRow, destCol))
			{
				code = "1";
			}
		}

		if (code == "0" || code == "1")
		{
			b1->changeMoved(destRow,destCol);
			b1->changeTurn();
		}

		msgToGraphics[0] = code[0];
		msgToGraphics[1] = NULL;

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}