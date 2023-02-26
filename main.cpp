#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <map>
#include <vector>
#include <string>
#include <set>
#define LOG(x) std::cout << x;

char playerMark = 'X';
short player = 1;

char board[3][3] = 
{
	{'-', '-', '-'},
	{'-', '-', '-'},
	{'-', '-', '-'}
};

std::map<std::string, char> spots = {
	{"A1", board[0][0]},
	{"A2", board[1][0]},
	{"A3", board[2][0]},
	{"B1", board[0][1]},
	{"B2", board[1][1]},
	{"B3", board[2][1]},
	{"C1", board[0][2]},
	{"C2", board[1][2]},
	{"C3", board[2][2]},
};

void clearScreen()
{
	std::cout << "\033[2J\033[1;1H";
}

std::string Capitalize(std::string str)
{
	for (char& letter : str)
	{
		letter = toupper(letter);
	}
	return str;
}

void printSpots()
{
	for (const auto key : spots)
	{
		LOG(key.first);
		LOG(", ");
		LOG(char(key.second));
		LOG("\n");
	}
}

void replaceSpot(std::string spot)
{
	for (auto &key : spots)
	{
		if (key.first == spot)
		{
			key.second = playerMark;
		}
	}
}

char togglePlayerMark(short player) 
{
	if (player == 1)
		return 'X';
	else
		return 'O';
}

short togglePlayer(short player)
{
	if (player == 1)
		return 2;
	else
		return 1;
}

bool spotOpen(std::string spot) 
{
	for (const auto key : spots)
	{
		if (spot == key.first)
		{
			return true;
		}
	}
	return false;
}

void printBoard() 
{
	std::printf("   A   B   C\n");
	std::printf("1  %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
	std::printf("  -----------\n");
	std::printf("2  %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
	std::printf("  -----------\n");
	std::printf("3  %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

void updateBoard()
{
	board[0][0] = spots.at("A1");
	board[1][0] = spots.at("A2");
	board[2][0] = spots.at("A3");
	board[0][1] = spots.at("B1");
	board[1][1] = spots.at("B2");
	board[2][1] = spots.at("B3");
	board[0][2] = spots.at("C1");
	board[1][2] = spots.at("C2");
	board[2][2] = spots.at("C3");
}

char horizontalWin()
{
	std::set<char> row;
	for (int i = 0; i < 3; i++)
	{
		row.clear();
		for (int j = 0; j < 3; j++)
		{
			row.insert(board[i][j]);
		}
		if (row.size() == 1)
		{
			for (char item : row)
			{
				if (item != '-')
					return item;
			}
		}
	}
	return '-';
}

char verticalWin()
{
	std::set<char> column;
	for (int i = 0; i < 3; i++)
	{
		column.clear();
		for (int j = 0; j < 3; j++)
		{
			column.insert(board[j][i]);
		}
		if (column.size() == 1)
		{
			for (char mark : column)
			{
				if (mark != '-')
					return mark;
			}
		}
	}
	return '-';
}

char diagonalWin()
{
	std::set<char> diagonal;
	for (int i = 0; i < 3; i++)
	{
		diagonal.insert(board[i][i]);
	}
	if (diagonal.size() == 1)
	{
		for (char mark : diagonal)
		{
			if (mark != '-')
				return mark;
		}
	}
	diagonal.clear();
	for (int i = 0; i < 3; i++)
	{
		diagonal.insert(board[i][2 - i]);
	}
	if (diagonal.size() == 1)
	{
		for (char mark : diagonal)
		{
			if (mark != '-')
				return mark;
		}
	}
	return '-';
}
char win()
{
	char winMark;
	winMark = horizontalWin();
	if (winMark != '-')
	{
		return winMark;
	}
	winMark = verticalWin();
	if (winMark != '-')
	{
		return winMark;
	}
	winMark = diagonalWin();
	if (winMark != '-')
	{
		return winMark;
	}
	
	return '-';
}

void wonGame(short player)
{
	printBoard();
	std::printf("Good Job Player %i, You Won!", player);
}

int main()
{
	while (true) {
		printBoard();
		std::string playerSpot;
		std::printf("\n Player %i, choose a spot: ", player);
		std::cin >> playerSpot;
		playerSpot = Capitalize(playerSpot);
		while (!spotOpen(playerSpot))
		{
			std::printf("\n Not a valid spot. Please enter valid spot: ");
			std::cin >> playerSpot;
			playerSpot = Capitalize(playerSpot);
		}
		
		replaceSpot(playerSpot);
		updateBoard();
		clearScreen();
		if (win() != '-')
		{
			wonGame(player);
			return 0;
		}
		player = togglePlayer(player);
		playerMark = togglePlayerMark(player);
	}
}
