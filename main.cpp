// Neccesary imports. 22 lines of whitespace
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <time.h>
#include <map>
#include <set>

using namespace std::chrono;

// The player and player mark
char playerMark = 'X';
short player = 1;


char board[9] = {
	// The board that's printed out
	'-', '-', '-',
	'-', '-', '-',
	'-', '-', '-'
};

std::map<std::string, char> spots = {
	// The board for inputting marks
	{"A1", board[0]},
	{"B1", board[1]},
	{"C1", board[2]},
	{"A2", board[3]},
	{"B2", board[4]},
	{"C2", board[5]},
	{"A3", board[6]},
	{"B3", board[7]},
	{"C3", board[8]},
};

void clearScreen() {
	// Clears the screen. I don't understand this lol
	system("cls");
}

int Random(int low, int high) {
	// Returns random number, that refreshes the seed every nanosecond.
	srand(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());
	return ((rand() % (high - low)) + low) + 1;
}

void Capitalize(std::string& str) {
	// Capitalizes all of the letters in a string.
	for (char& letter : str) {
		letter = toupper(letter);
	}
}

void UnCapitalize(std::string& str) {
	// UnCapitalizes all of the letters in a string.
	for (char& letter : str) {
		letter = tolower(letter);
	}
}

void printBoard(const char(&board)[9]) {
	// Prints board
	std::printf("    A   B   C\n");
	for (int i = 0; i < 8; i += 3) {
		printf("%i   %c | %c | %c\n", (i / 3 + 1), board[i], board[i + 1], board[i + 2]);
		if (i < 5)
			printf("   -----------\n");
	}
}

void updateBoard() {
	// Updates all the board spots, so it prints correctly
	const char columnLetters[] = { 'A', 'B', 'C' };
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			board[col + row * 3] = spots[columnLetters[col] + std::to_string(row + 1)];
		}
	}
}

bool horizontalWin(const char type) {
	// Checks board for horizontal wins
	int won = 0;
	int x, y;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			x = type == 'h' ? i : j;
			y = type == 'h' ? j : i;
			won -= board[x + y * 3] == 'X' ? -1 : board[x + y * 3] == 'O' ? 1 : 0;
		}
		if (abs(won) == 3) {
			return 1;
		}
		won = 0;
	}
	return 0;
}

bool diagonalWin() {
	// Checks board for wins diagonally
	int won = 0;
	for (int i = 0; i < 3; i++) {
		won -= board[i + i * 3] == 'X' ? -1 : board[i + i * 3] == 'O' ? 1 : 0;
	}
	if (abs(won) == 3) {
		return 1;
	}
	won = 0;
	for (int i = 0; i < 3; i++) {
		won -= board[i + (2 - i) * 3] == 'X' ? -1 : board[i + (2 - i) * 3] == 'O' ? 1 : 0;
	}
	if (abs(won) == 3) {
		return 1;
	}
	return 0;
}
inline bool win() {
	// If anyone has won
	if (diagonalWin() || horizontalWin('v') || horizontalWin('h')) { return 1; }
	return 0;
}

inline void wonGame(const short player) {
	// Congratulates winning player.
	printBoard(board);
	std::printf("\nGood Job Player %i, You Won!\n", player);
}

void input(std::string& playerSpot, const char* statement) {
	// Get's input with given string
	std::printf(statement, player);
	std::cin >> playerSpot;
	Capitalize(playerSpot);
}


int Competition(const std::string& playerSpot) {
	// If one player tries to take another players spot
	std::string competitionValue;

	clearScreen();
	printBoard(board);

	std::cout << "\nWould you like to enter a competition? y/n/info: ";
	std::cin >> competitionValue;
	UnCapitalize(competitionValue);

	while (1) {
		if (competitionValue == "y") {
			// Getting actual winner
			int random1 = Random(1, 6);
			int random2 = Random(1, 6);
			int showNumber;
			int wait = 1;

			// Asthetics
			for (int i = 0; i < 20; i++) {
				clearScreen();
				printBoard(board);
				showNumber = Random(1, 6);
				std::cout << "\nOffensive Player's Number: " << showNumber;
				std::this_thread::sleep_for(std::chrono::milliseconds(wait));
				wait += i * 2;
			}
			wait = 1;
			for (int i = 0; i < 20; i++) {
				clearScreen();
				printBoard(board);
				std::cout << "\nOffensive Player's Number: " << random1 << "\n\n";
				showNumber = Random(1, 6);
				std::cout << "Defensive Player's Number: " << showNumber;
				std::this_thread::sleep_for(std::chrono::milliseconds(wait));
				wait += i * 2;
			}

			// Says who won, and updates board
			clearScreen();
			std::cout << "Offensive Player's Number: " << random1 << "\n\n";
			std::cout << "Defensive Player's Number: " << random2 << "\n";

			if (random1 > random2) {
				std::cout << "\nOffensive Player Wins!\n";
				system("pause");
				spots[playerSpot] = playerMark;
				return 1;
			}
			else {
				std::cout << "\nDefensive Player Wins!\n";
				system("pause");
				spots[playerSpot] = playerMark == 'X' ? 'O' : 'X';
				return 0;
			}
		}

		// Allows the player to continue their turn
		if (competitionValue == "n") {
			return 2;
		}

		// Tells the player what happens.
		if (competitionValue == "info") {
			clearScreen();
			printBoard(board);
			std::cout << "Both players get a die rolled for them. It will be a number between 1 and 6.\n\
If the offensive players number is HIGHER than the defensive player, the offensive\n\
player gets the spot. Otherwise, they loose their turn.\n\
Would you like to enter a competition? y/n/info: ";
			std::cin >> competitionValue;
		}
	}
}

int main()
{
	std::string playerSpot;
	clearScreen();

	while (1) {
		printBoard(board);
		input(playerSpot, "\nPlayer %i, choose a spot: ");

		// If spot isn't valid
		while (!spots[playerSpot]) {
			input(playerSpot, "\nNot a valid spot. Please enter valid spot: ");
		}

		// Checks if a competition should start
		if (spots[playerSpot] != '-') {
			if (Competition(playerSpot) == 2) {
				clearScreen();
				continue;
			}
		}
		// Replaces spot
		else {
			spots[playerSpot] = playerMark;
		}

		updateBoard();
		clearScreen();

		// Checks if a player has won
		if (win()) {
			wonGame(player);
			return 0;
		}

		// Toggles player and playerMark
		player = (player == 2) ? 1 : 2;
		playerMark = (player == 1) ? 'X' : 'O';
	}
}
