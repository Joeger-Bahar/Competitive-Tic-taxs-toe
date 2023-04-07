// Neccesary imports. 22 lines of whitespace
#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <set>

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
	std::cout << "\033[2J\033[1;1H";
}

void Capitalize(std::string& str) {
	// Capitalizes all of the letters in a string.
	for (char& letter : str) {
		letter = toupper(letter);
	}
}

void printBoard(const char (&board)[9]) {
	std::printf("    A   B   C\n");
    for (int i = 0; i < 8; i += 3) {
        printf("%i   %c | %c | %c\n", (i / 3 + 1), board[i], board[i+1], board[i+2]);
        if (i < 5)
            printf("   -----------\n");
	}
}

void updateBoard() {
	// Updates all the board spots, so it prints correctly
  const char columnLetters[] = {'A', 'B', 'C'};
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
  if (diagonalWin() || horizontalWin('v') || horizontalWin('h')) {return 1;}
	return 0;
}

inline void wonGame(const short player) {
	printBoard(board);
	std::printf("\nGood Job Player %i, You Won!\n", player);
}

void input(std::string& playerSpot, const char* statement) {
  std::printf(statement, player);
  std::cin >> playerSpot;
  Capitalize(playerSpot);
}

int main()
{
	std::string playerSpot;
  clearScreen();
  while (1) {
		printBoard(board);
    input(playerSpot, "\nPlayer %i, choose a spot: ");
		while (!spots[playerSpot]) {
			input(playerSpot, "\nNot a valid spot. Please enter valid spot: ");
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
 
