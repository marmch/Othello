#include <iostream>
#include <algorithm>
#include <array>
#include <thread>
#include <string>
#include <fstream>
using namespace std;

#include "CheckMoves.h"
#include "MakeMoves.h"
#include "Negamax.h"

void printGrid(char grid[8][8]) {
	cout << "\n\n\n";
	for (int i = 1; i <= 8; i++) {
		if (i == 1)
			cout << "  | " << i;
		else if (i == 8)
			cout << " | " << i << " |";
		else
			cout << " | " << i;
	}
	cout << endl;
	cout << "--+---+---+---+---+---+---+---+---+" << endl;
	for (int i = 1; i <= 8; i++) {
		cout << i;
		for (int j = 1; j <= 8; j++) {
			cout << " | ";
			if (grid[i - 1][j - 1] == 'X') {
				cout << (char)219;
			}
			else if (grid[i - 1][j - 1] == 'O') {
				cout << 'O';
			}
			else
				cout << ' ';
			if (j == 8)
				cout << " |";
		}
		cout << endl;
		cout << "--+---+---+---+---+---+---+---+---+" << endl;
	}
	return;
}

bool makePlayerMove(char player, char grid[8][8]) {
	if (!CheckMoves::existsLegalMove(player, grid)) {
		cout << "No legal moves" << endl;
		return false;
	}
	bool legalMove = false;
	while (!legalMove) {
		if(player == 'X')
			cout << (char)219 << "'s turn. Enter legal move: ";
		else
			cout << "O's turn. Enter legal move (row col): ";
		int row, col;
		cin >> row >> col;
		row--;
		col--;
		if (CheckMoves::isLegalMove(row, col, player, grid)) {
			MakeMoves::makeMove(row, col, player, grid);
			legalMove = true;
		}
		else {
			cout << "Illegal move" << endl;
		}
	}
	return true;
}

bool makeCPUMove(char player, char grid[8][8], int cputime) {
	if (!CheckMoves::existsLegalMove(player, grid)) {
		cout << "No legal moves" << endl;
		return false;
	}
	array<int, 2> moves = Negamax::findMove(player, grid, cputime);
	cout << "\n\nMoving to (" << moves[0] + 1 << "," << moves[1] + 1 << ")" << endl;
	MakeMoves::makeMove(moves[0], moves[1], player, grid);
	return true;
}

void endGame(char grid[8][8]) {
	int numW = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (grid[i][j] == 'X')
				numW++;
		}
	}
	if (numW > 32)
		cout << (char)219 << " WON" << endl;
	else if (numW == 32)
		cout << "DRAW" << endl;
	else
		cout << "O WON" << endl;
	cout << "SCORE: " << (char)219 << "-" << numW << ", O-" << 64 - numW << endl;
}

int main() {
	char grid[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			grid[i][j] = ' ';

	grid[3][3] = 'O';
	grid[3][4] = 'X';
	grid[4][3] = 'X';
	grid[4][4] = 'O';
	bool customStart = false;

	bool validInput = false;
	while (!validInput) {
		string input;
		cout << "Load Starting position? (Y/N): ";
		cin >> input;
		if (input.compare("Y") == 0 || input.compare("N") == 0){
			if (input.compare("Y") == 0)
				customStart = true;
			validInput = true;
		}
	}

	if (customStart) {
		string line;
		ifstream myfile("board.txt");
		if (myfile.is_open())
		{
			int linenum = 0;
			while (getline(myfile, line) && linenum < 8)
			{
				if (line.size() != 8) {
					cout << "Invalid load file" << endl;
					exit(1);
				}
				for (int i = 0; i < 8; i++) {
					if (line[i] == '.')
						grid[linenum][i] = 'X';
					else if (line[i] == '*')
						grid[linenum][i] = 'O';
					else if (line[i] == '-')
						grid[linenum][i] = ' ';
					else {
						cout << "Invalid load file" << endl;
						exit(1);
					}
				}
				linenum++;
			}
			myfile.close();
		}
		else
			cout << "Could not find file" << endl;
	}

	bool AIgame = false;
	validInput = false;
	while (!validInput) {
		string input;
		cout << "AI vs AI? (Y/N): ";
		cin >> input;
		if (input.compare("Y") == 0 || input.compare("N") == 0) {
			if (input.compare("Y") == 0)
				AIgame = true;
			validInput = true;
		}
	}

	bool firstHuman = true;
	if (!AIgame) {
		validInput = false;
		while (!validInput) {
			string input;
			cout << "First player? (Player/AI): ";
			cin >> input;
			if (input.compare("Player") == 0 || input.compare("AI") == 0) {
				if (input.compare("AI") == 0)
					firstHuman = false;
				validInput = true;
			}
		}
	}

	long cputime;
	validInput = false;
	while (!validInput) {
		cout << "CPU thinking time (milliseconds): ";
		cin >> cputime;
		if (!cin) {
			cout << "Invalid entry" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		validInput = true;
	}

	if (AIgame) {
		while (true) {
			printGrid(grid);
			bool xMoved = makeCPUMove('X', grid, cputime);
			printGrid(grid);
			bool oMoved = makeCPUMove('O', grid, cputime);
			if (!xMoved && !oMoved) {
				endGame(grid);
				break;
			}
		}
	}
	else {
		if (firstHuman) {
			while (true) {
				printGrid(grid);
				bool xMoved = makePlayerMove('X', grid);
				printGrid(grid);
				bool oMoved = makeCPUMove('O', grid, cputime);
				if (!xMoved && !oMoved) {
					endGame(grid);
					break;
				}
			}
		}
		else {
			while (true) {
				printGrid(grid);
				bool xMoved = makeCPUMove('X', grid, cputime);
				printGrid(grid);
				bool oMoved = makePlayerMove('O', grid);
				if (!xMoved && !oMoved) {
					endGame(grid);
					break;
				}
			}
		}
		
	}

	cin.ignore();
	cin.ignore();

	return 0;
}