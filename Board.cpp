#include "Board.h"

Board::Board(string startBoard)
{
	for (int a = 0; a < SIZE; a++)
	{
		for (int b = 0; b < SIZE; b++)
		{
			_board[a][b] = nullptr;
		}
	}

	int i = 0;//for loops
	int col = 0;//column
	int row = 0;//row
	char typePiece = ' ';//for the loop
	string place = "";//the place in the board
	int zeroAscii = 48;//the ascii of zero
	char num = ' ';
	Player* black = new Player("black");
	Player* white = new Player("white");

	//initializing the board
	for (i = 0; i < 64; i++)
	{
		typePiece = startBoard[i];
		row = i / 8;
		col = i % 8;
		if (typePiece != '#')
		{
			place = "";
			place += char(col +'A');
			num = char(row + 1 + zeroAscii);
			place += num;

			switch (startBoard[i]) {
			case('R'):
				_board[row][col] = new Rook(place,*white);
				break;

			case('N'):
				_board[row][col] = new Knight(place,*white);
				break;
			
			case('B'):
				_board[row][col] = new Bishop(place,*white);
				break;
			
			case('K'):
				_board[row][col] = new King(place,*white);
				break;
				
			case('Q'):
				_board[row][col] = new Queen(place, *white);
				break;

			case('P'):
				_board[row][col] = new Pawn(place, *white);
				break;

			case('r'):
				_board[row][col] = new Rook(place, *black);
				break;

			case('n'):
				_board[row][col] = new Knight(place, *black);
				break;

			case('b'):
				_board[row][col] = new Bishop(place, *black);
				break;

			case('k'):
				_board[row][col] = new King(place, *black);
				break;

			case('q'):
				_board[row][col] = new Queen(place, *black);
				break;

			case('p'):
				_board[row][col] = new Pawn(place, *black);
			default:
				break;
			}
		}
		else
		{
			_board[row][col] = nullptr;
		}

			
	}
	//this part checks who start
	if (startBoard[64] == '1')
	{
		_turn = false;
	}
}


//D'tor
Board::~Board()
{
}

//prints the board
void Board::printBoard() const
{
	for (int a = 0; a < SIZE; a++)
	{
		for (int b = 0; b < SIZE; b++)
		{
			if (_board[a][b] != nullptr)
			{
				std::cout << _board[a][b]->getType() << "  ";
			}
			else
			{
				std::cout << "#" << "  ";
			}
		}
		std::cout<<std::endl;
	}
}

//This is a "move func " for the pieces
Board* Board::updatePlace(int startCol,int endCol,int startRow,int endRow)
{
	if (this->_board[endRow][endCol] != nullptr && this->_board[endRow][endCol]->getOwner().getColor() == this->_board[startRow][startCol]->getOwner().getColor())
	{
		return this;
	}
	if (this->_board[endRow][endCol] != nullptr&& this->_board[endRow][endCol]->getOwner().getColor() != this->_board[startRow][startCol]->getOwner().getColor() )
	{
		delete(this->_board[endRow][endCol]);
	}
	this->_board[endRow][endCol] = this->_board[startRow][startCol];
	this->_board[startRow][startCol] = nullptr;
	Board* b1 = new Board("################################################################1");
	for (int i = 0; i < SIZE; i++)
	{
		for (int a = 0; a < SIZE; a++)
		{
			b1->_board[i][a] = this->_board[i][a];
		}
	}
		
	return b1;

}

//This func checks if the move is valid
string Board::checkTheWay(int startCol, int endCol, int startRow, int endRow)
{
	if (this->_board[startRow][startCol]!=nullptr)
	{
		if (this->_board[startRow][startCol]->getType() == "k" || this->_board[startRow][startCol]->getType() == "K")
		{
			if (!(abs(startCol - endCol) <= 1 && abs(startRow - endRow) <= 1)) {
				return "6";
			}
			if (startCol == endCol)
			{
				if (!this->checkCol(startCol, endCol, startRow, endRow)) { return "6"; }
				else { return "0"; }
			}
			if (startRow == endRow)
			{
				if (!this->checkRow(startCol, endCol, startRow, endRow)) { return "6"; }
				else { return "0"; }
			}
			if (!this->checkDiagonal(startCol, endCol, startRow, endRow)) { return "6"; }

			return "0";
		}
		if (this->_board[startRow][startCol]->getType() == "r" || this->_board[startRow][startCol]->getType() == "R")
		{
			if (startCol == endCol)
			{
				if (this->checkCol(startCol, endCol, startRow, endRow)) { return "0"; }
			}
			if (startRow == endRow)
			{
				if (this->checkRow(startCol, endCol, startRow, endRow)) { return "0"; }
			}
			return "6";
			
		}
		if (this->_board[startRow][startCol]->getType() == "b" || this->_board[startRow][startCol]->getType() == "B")
		{
			if (this->checkDiagonal(startCol, endCol, startRow, endRow)) {return "0"; }
			else { return "6"; }
		}
		if (this->_board[startRow][startCol]->getType() == "q" || this->_board[startRow][startCol]->getType() == "Q")
		{
			if (startCol == endCol)
			{
				if (!this->checkCol(startCol, endCol, startRow, endRow)) { return "6"; }
				else { return "0"; }
			}
			if (startRow == endRow)
			{
				if (!this->checkRow(startCol, endCol, startRow, endRow)) { return "6"; }
				else { return "0"; }
			}
			if (!this->checkDiagonal(startCol, endCol, startRow, endRow)) { return "6"; }

			return "0";
		}
		if (this->_board[startRow][startCol]->getType() == "p" || this->_board[startRow][startCol]->getType() == "P")
		{
			if (this->_board[startRow][startCol]->getOwner().getColor()=="black")
			{
				if (!this->_board[startRow][startCol]->getMoved())
				{
					if (startCol == endCol)
					{
						if (endRow- startRow <=2&& endRow - startRow >0)
						{
							if (this->checkCol(startCol, endCol, startRow, endRow)) 
							{
								return "0";
							}
						}
					}
					else if ((endCol == startCol + 1 || endCol == startCol - 1) && endRow == startRow + 1)
					{
						if (this->_board[endRow][endCol] != nullptr && this->_board[endRow][endCol]->getOwner().getColor() != this->_board[startRow][startCol]->getOwner().getColor())
						{
							return "0";
						}
					}
				}
				else
				{
					if (startCol == endCol)
					{
						if (endRow - startRow == 1)
						{
							if (this->checkCol(startCol, endCol, startRow, endRow))
							{
								return "0";
							}
						}
					}
					else if ((endCol == startCol + 1 || endCol == startCol - 1) && endRow == startRow + 1)
					{
						if (this->_board[endRow][endCol] != nullptr && this->_board[endRow][endCol]->getOwner().getColor() != this->_board[startRow][startCol]->getOwner().getColor())
						{
							return "0";
						}
					}
				}
			}
			else
			{
				if (!this->_board[startRow][startCol]->getMoved())
				{
					if (startCol == endCol)
					{
						if (startRow - endRow <= 2 && startRow - endRow > 0)
						{
							if (this->checkCol(startCol, endCol, startRow, endRow))
							{
								return "0";
							}
						}

					}
					else if ((endCol == startCol + 1 || endCol == startCol - 1) && endRow == startRow - 1)
					{
						if (this->_board[endRow][endCol] != nullptr && this->_board[endRow][endCol]->getOwner().getColor() != this->_board[startRow][startCol]->getOwner().getColor())
						{
							return "0";
						}
					}
				}
				else
				{
					if (startCol == endCol)
					{
						if (startRow - endRow == 1)
						{
							if (this->checkCol(startCol, endCol, startRow, endRow))
							{
								return "0";
							}
						}
					}
					else if ((endCol == startCol + 1 || endCol == startCol - 1) && endRow == startRow - 1)
					{
						if (this->_board[endRow][endCol] != nullptr && this->_board[endRow][endCol]->getOwner().getColor() != this->_board[startRow][startCol]->getOwner().getColor())
						{
							return "0";
						}
					}
				}
			}
			return "6";
		}
		if (this->_board[startRow][startCol]->getType() == "n" || this->_board[startRow][startCol]->getType() == "N")
		{
			if (abs(startRow-endRow)==2&&abs(startCol-endCol)==1||abs(startRow-endRow)==1&&abs(startCol-endCol)==2)
			{
				return "0";
			}
			return "6";
		}




	}
	return 	"2";

}


//check valid move in a col
bool Board::checkCol(int startCol, int endCol, int startRow, int endRow)
{
	int bigger = std::max(startRow, endRow);
	int smaller = std::min(startRow, endRow);
	for (int i = smaller + 1; i < bigger; i++)
	{
		if (this->_board[i][endCol] != nullptr)
		{
			return false;
		}
	}
	if (this->_board[endRow][endCol] != nullptr)
	{
		if (this->_board[endRow][endCol]->getOwner().getColor() == this->_board[startRow][startCol]->getOwner().getColor())
		{
			return false;
		}
	}
	return true;
}

//check valid move in a row
bool Board::checkRow(int startCol, int endCol, int startRow, int endRow)
{
	int bigger = std::max(startCol, endCol);
	int smaller = std::min(startCol, endCol);
	for (int i = smaller + 1; i < bigger; i++)
	{
		if (this->_board[endRow][i] != nullptr)
		{
			return false;
		}
	}
	if (this->_board[endRow][endCol] != nullptr)
	{
		if (this->_board[endRow][endCol]->getOwner().getColor() == this->_board[startRow][startCol]->getOwner().getColor())
		{
			return false;
		}
	}
	return true;
}


//check if the move is valid in diagonal
bool Board::checkDiagonal(int startCol, int endCol, int startRow, int endRow)
{
	int copyOfStartCol = startCol;
	int copyOfEndCol = endCol;
	int copyOfStartRow = startRow;
	int copyOfEndRow = endRow;
	if (endCol > startCol && endRow > startRow&& abs(endRow-startRow) == abs(endCol-startCol))
	{
		//4,4 - 7,7
		for (int i = startCol+1; i < endCol; i++)
		{
			copyOfStartCol++;
			copyOfStartRow++;
			if (this->_board[copyOfStartRow][copyOfStartCol]!=nullptr)
			{
				return false;
			}
		}
		if (this->_board[endRow][endCol] != nullptr)
		{
			if (this->_board[endRow][endCol]->getOwner().getColor() == this->_board[startRow][startCol]->getOwner().getColor())
			{
				return false;
			}
		}
		return true;
	}
	else if(endCol>startCol&&endRow<startRow && abs(endRow - startRow) == abs(endCol - startCol))
	{
		//4,4 - 2,6
		for (int i = startCol + 1; i < endCol; i++)
		{
			copyOfStartCol++;
			copyOfStartRow--;
			if (this->_board[copyOfStartRow][copyOfStartCol] != nullptr)
			{
				return false;
			}
		}
		if (this->_board[endRow][endCol] != nullptr)
		{
			if (this->_board[endRow][endCol]->getOwner().getColor() == this->_board[startRow][startCol]->getOwner().getColor())
			{
				return false;
			}
		}
		return true;
	}
	else if(endCol<startCol&&endRow>startRow && abs(endRow - startRow) == abs(endCol - startCol))
	{
		//4,4 - 6,2
		for (int i = startRow + 1; i < endRow; i++)
		{
			copyOfStartCol--;
			copyOfStartRow++;
			if (this->_board[copyOfStartRow][copyOfStartCol] != nullptr)
			{
				return false;
			}
		}
		if (this->_board[endRow][endCol] != nullptr)
		{
			if (this->_board[endRow][endCol]->getOwner().getColor() == this->_board[startRow][startCol]->getOwner().getColor())
			{
				return false;
			}
		}
		return true;
	}
	else if (endCol < startCol && endRow < startRow && abs(endRow - startRow) == abs(endCol - startCol))
	{
		//4,4 - 2,2
		for (int i = startCol - 1; i > endCol; i--)
		{
			copyOfStartCol--;
			copyOfStartRow--;
			if (this->_board[copyOfStartRow][copyOfStartCol] != nullptr)
			{
				return false;
			}

		}
		if (this->_board[endRow][endCol] != nullptr)
		{
			if (this->_board[endRow][endCol]->getOwner().getColor() == this->_board[startRow][startCol]->getOwner().getColor())
			{
				return false;
			}
		}
		return true;
	}
	return false;
}


//checks if there is a self check
bool Board::selfChess(int row,int col)
{
	string colorTypeAfterChange = this->_board[row][col]->getOwner().getColor();
	int rowKing = 0;
	int colKing = 0;
	for (int a = 0;a < SIZE; a++)
	{
		for (int b = 0; b < SIZE; b++)
		{
			if (this->_board[a][b]!=nullptr &&(this->_board[a][b]->getOwner().getColor() == colorTypeAfterChange&& (this->_board[a][b]->getType() == "k" || this->_board[a][b]->getType()=="K")))
			{
				rowKing = a;
				colKing = b;
			}
		}
	}
	for (int a = 0; a < SIZE; a++)
	{
		for (int b = 0; b < SIZE; b++)
		{
			if (this->_board[a][b] != nullptr && this->_board[a][b]->getOwner().getColor() != colorTypeAfterChange)
			{
				if (this->checkTheWay(b, colKing,a, rowKing)=="0" || this->checkTheWay(b, colKing, a, rowKing) == "1")
				{
					return true;
				}
			}
		}
	}
	return false;
	
}

bool Board::checkOnEnemy(int row, int col)
{
	string colorTypeAfterChange = this->_board[row][col]->getOwner().getColor();
	int rowKing = 0;
	int colKing = 0;
	for (int a = 0; a < SIZE; a++)
	{
		for (int b = 0; b < SIZE; b++)
		{
			if (this->_board[a][b] != nullptr && (this->_board[a][b]->getOwner().getColor() != colorTypeAfterChange && (this->_board[a][b]->getType() == "k" || this->_board[a][b]->getType() == "K")))
			{
				rowKing = a;
				colKing = b;
			}
		}
	}

	for (int a = 0; a < SIZE; a++)
	{
		for (int b = 0; b < SIZE; b++)
		{
			if (this->_board[a][b] != nullptr && this->_board[a][b]->getOwner().getColor() != this->_board[rowKing][colKing]->getOwner().getColor())
			{
				if (this->checkTheWay(b, colKing,a, rowKing) == "0" || this->checkTheWay(b, colKing,a , rowKing) == "1")
				{
					return true;
				}
			}
		}
	}
	return false;



}

bool Board::noPlayer(int row, int col) const
{
	if (this->_board[row][col] == nullptr)
	{
		return true;
	}
	return false;
}

bool Board::noDestSelfPlayer(int startRow, int startCol, int endRow, int endCol) const
{
	if (this->_board[endRow][endCol]!=nullptr&&this->_board[startRow][startCol]->getOwner().getColor() == this->_board[endRow][endCol]->getOwner().getColor())
	{
		return true;
	}
	return false;
}

void Board::changeMoved(int row, int col)
{
	this->_board[row][col]->changeMoved();
}
//this function check if the color of the piece that moved is its turn
bool Board::checkValidTurn(int row, int col)
{
	if (this->_board[row][col]->getOwner().getColor()=="white"&&this->_turn|| this->_board[row][col]->getOwner().getColor() == "black" && !this->_turn)
	{
		return true;
	}
	return false;
}

void Board::changeTurn()
{
	this->_turn = !this->_turn;
}
