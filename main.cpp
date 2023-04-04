// Neccesary imports.
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <map>
#include <string>
#include <set>
#define LOG(x) std::cout << x;

// The player and player mark
char playerMark = 'X';
short player = 1;

char board[3][3] = {
	// The board that's printed out
  {'-', '-', '-'},
	{'-', '-', '-'},
	{'-', '-', '-'}
};

std::map<std::string, char> spots = {
	// The board for inputting marks
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

void clearScreen() {
	// Clears the screen. I don't understand this lol
	std::cout << "\033[2J\033[1;1H";
}

void Capitalize(std::string& str) {
	// Capitalizes all of the letters in a string.
	for (char& letter : str) {
		letter = toupper(letter);
	}
}

void printSpots() {
	// Prints map spots for testing
	for (const auto key : spots) {
		LOG(key.first);
		LOG(", ");
		LOG(char(key.second));
		LOG("\n");
	}
}

void printBoard() {
	// Prints the board for the player
	std::printf("   A   B   C\n");
	std::printf("1  %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
	std::printf("  -----------\n");
	std::printf("2  %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
	std::printf("  -----------\n");
	std::printf("3  %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

void updateBoard() {
	// Updates all the board spots, so it prints correctly
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

bool horizontalWin() {
	// Checks board for horizontal wins
	std::set<char> row;
	for (int i = 0; i < 3; i++) {
		row.clear();
		for (int j = 0; j < 3; j++) {
			row.insert(board[i][j]);
		}
		if (row.size() == 1) {
			for (char item : row) {
				if (item != '-') {
					return 1;
				}
			}
		}
	}
	return 0;
}

bool verticalWin() {
	// Checks the board for wins vertically
	std::set<char> column;
	for (int i = 0; i < 3; i++) {
		column.clear();
		for (int j = 0; j < 3; j++) {
			column.insert(board[j][i]);
		}
		if (column.size() == 1) {
			for (char mark : column) {
				if (mark != '-') {
					return 1;
				}
			}
		}
	}
	return 0;
}

bool diagonalWin() {
	// Checks board for wins diagonally
	std::set<char> diagonal;
	for (int i = 0; i < 3; i++) {
		diagonal.insert(board[i][i]);
	}
	if (diagonal.size() == 1) {
		for (char mark : diagonal) {
			if (mark != '-')
				return 1;
		}
	}
	diagonal.clear();
	for (int i = 0; i < 3; i++) {
		diagonal.insert(board[i][2 - i]);
	}
	if (diagonal.size() == 1) {
		for (char mark : diagonal) {
			if (mark != '-')
				return 1;
		}
	}
	return 0;
}
bool win() {
  if (diagonalWin() || verticalWin() || horizontalWin())
    return 1;
	return 0;
}

void wonGame(short player) {
	printBoard();
	std::printf("Good Job Player %i, You Won!", player);
}

int main()
{
	std::string playerSpot;
  clearScreen();
  while (1) {
		printBoard();
		std::printf("\n Player %i, choose a spot: ", player);
		std::cin >> playerSpot;
		Capitalize(playerSpot);
		while (!spots[playerSpot]) {
			std::printf("\n Not a valid spot. Please enter valid spot: ");
			std::cin >> playerSpot;
			Capitalize(playerSpot);
		}
		
		spots[playerSpot] = playerMark;
		updateBoard();
		clearScreen();
		if (win()) {
			wonGame(player);
			return 0;
		}
	  player = (player == 2) ? 1 : 2;
		playerMark = (player == 1) ? 'X' : 'O';
	}
} 
