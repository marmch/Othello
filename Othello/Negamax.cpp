#include <algorithm>
#include <vector>
#include <iostream>
#include <array>
#include <random>
#include <time.h>
using namespace std;

#include "CheckMoves.h"
#include "Negamax.h"
#include "MakeMoves.h"

array<int, 2> Negamax::findMove(char player, char grid[8][8], long cputime) {
	srand(time(0));
	vector<array<int, 2> > moves = CheckMoves::listLegalMoves(player, grid);
	int finalbestMove = -30000;
	array<int, 2> finalbestCoord;
	finalbestCoord[0] = moves[0][0];
	finalbestCoord[1] = moves[0][1];
	clock_t t = clock();
	long endtime = ((float)t) / CLOCKS_PER_SEC * 1000 + cputime;
	int depth = 0;
	while (((float)t) / CLOCKS_PER_SEC * 1000 < endtime - 50) {
		bool timeleft = true;
		array<int, 2> bestCoord;
		int bestMove = -30000;
		for (int i = 0; i < moves.size(); i++) {
			t = clock();
			if (((float)t) / CLOCKS_PER_SEC * 1000 >= endtime - 50) {
				timeleft = false;
				break;
			}
			char newGrid[8][8];
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					newGrid[i][j] = grid[i][j];
			int newMove = negaMax(moves[i][0], moves[i][1], depth, -30000, 30000, player, newGrid, endtime);
			//int newMove = negaMaxDraw(moves[i][0], moves[i][1], 3, -10000, 10000, player, newGrid);
			//cout << "Depth " << depth << ": " << moves[i][0] + 1 << "," << moves[i][1] + 1 << ": " << newMove << endl;
			if (newMove > bestMove) {
				bestMove = newMove;
				bestCoord[0] = moves[i][0];
				bestCoord[1] = moves[i][1];
			}
		}
		if (timeleft) {
			finalbestMove = bestMove;
			finalbestCoord = bestCoord;
		}
		else
			break;
		depth++;
	}
	//cout << "Depth searched: " << depth << endl;
	return finalbestCoord;
}

int Negamax::negaMax(int row, int col, int depth, int alpha, int beta, char player, char grid[8][8], long endtime) {
	clock_t t = clock();
	if (((float)t) / CLOCKS_PER_SEC * 1000 >= endtime - 50) {
		return 0;
	}
	if (depth == 0)
		return evalMove(row, col, player, grid);
	char newGrid[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			newGrid[i][j] = grid[i][j];
	char player2 = 'X';
	if (player == 'X')
		player2 = 'O';
	MakeMoves::makeMove(row, col, player, newGrid);
	vector<array<int, 2> > moves = CheckMoves::listLegalMoves(player2, newGrid);
	if (moves.size() == 0)
		return evalMove(row, col, player, grid);
	else {
		int bestMove = -30000;
		for (int i = 0; i < moves.size(); i++) {
			int newMove = negaMax(moves[i][0], moves[i][1], depth - 1, -beta, -alpha, player2, newGrid, endtime);
			if (newMove > bestMove) {
				bestMove = newMove;
			}
			if (newMove > alpha)
				alpha = newMove;
			if (alpha >= beta)
				break;
		}
		return -bestMove;
	}
}

int Negamax::negaMaxDraw(int row, int col, int depth, int alpha, int beta, char player, char grid[8][8], long endtime) {
	cout << "(" << row + 1 << "," << col + 1 << "), depth " << depth << endl;
	clock_t t = clock();
	if (((float)t) / CLOCKS_PER_SEC * 1000 >= endtime - 50) {
		cout << "TIME OUT" << endl;
		return 0;
	}
	if (depth == 0) {
		int eval = evalMove(row, col, player, grid);
		cout << "depth = 0: " << eval << endl;
		return eval;
	}
	char newGrid[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			newGrid[i][j] = grid[i][j];
	char player2 = 'X';
	if (player == 'X')
		player2 = 'O';
	MakeMoves::makeMove(row, col, player, newGrid);
	vector<array<int, 2> > moves = CheckMoves::listLegalMoves(player2, newGrid);
	if (moves.size() == 0) {
		cout << "no moves\n\n";
		return evalMove(row, col, player, grid);
	}
	else {
		cout << "(" << row + 1 << "," << col + 1 << "), alpha " << alpha << ", beta " << beta << endl;
		int bestMove = -30000;
		for (int i = 0; i < moves.size(); i++) {
			int newMove = negaMaxDraw(moves[i][0], moves[i][1], depth - 1, -beta, -alpha, player2, newGrid, endtime);
			if (newMove > bestMove) {
				bestMove = newMove;
			}
			if (newMove > alpha)
				alpha = newMove;
			cout << "(" << row + 1 << "," << col + 1 << "), alpha " << alpha << ", beta " << beta << ", move " << newMove << endl;
			if (alpha >= beta)
				break;
		}
		cout << "\n\n";
		return -bestMove;
	}
}

int Negamax::evalMove(int row, int col, char player, char grid[8][8]) {
	int value = 0;

	char player2 = 'X';
	if (player == 'X')
		player2 = 'O';
	char newGrid[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			newGrid[i][j] = grid[i][j];
	vector<array<int, 2> > p1moves = CheckMoves::listLegalMoves(player, newGrid);
	MakeMoves::makeMove(row, col, player, newGrid);
	int numMovesLeft = 0;
	int numW = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (newGrid[i][j] == player)
				numW++;
			else if (newGrid[i][j] == ' ')
				numMovesLeft++;
		}
	}
	vector<array<int, 2> > p2moves = CheckMoves::listLegalMoves(player2, newGrid);
	if (p2moves.size() == 0) {
		value += 500;
		if(numMovesLeft == 0) {
			if (numW > 32)
				return 10000 + (numW - 32) * 100;
			else if (numW < 32)
				return -10000 - (numW - 32) * 100;
			else
				return 0;
		}
	}
	else{
		if (p1moves.size() < 4) {
			value -= 2000 / (p1moves.size()*sqrt(p1moves.size()));
		}
		else {
			value -= 400 - 40*p1moves.size();
		}

		if (p2moves.size() < 4) {
			value += 500 / (p2moves.size()*sqrt(p2moves.size()));
		}
		else {
			value += 100 - 10 * p1moves.size();
		}
	}

	if (numMovesLeft > 32) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i == 0 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 0) || (i == 7 && j == 7)) {
					if (newGrid[i][j] == player)
						value += 800;
					else if (newGrid[i][j] == player2)
						value -= 800;
				}
				else if ((i == 0 || i == 7) && (newGrid[i][j + 1] == player2 && newGrid[i][j - 1] == player2) ||
					(j == 0 || j == 7) && (newGrid[i + 1][j] == player2 && newGrid[i - 1][j] == player2)) {
					if (newGrid[i][j] == player)
						value += 100;
					else if (newGrid[i][j] == player2)
						value -= 100;
				}
				else if ((i == 0 || i == 7) && (newGrid[i][j + 1] == player2 || newGrid[i][j - 1] == player2) ||
					(j == 0 || j == 7) && (newGrid[i + 1][j] == player2 || newGrid[i - 1][j] == player2)) {
					if (newGrid[i][j] == player)
						value -= 80;
					else if (newGrid[i][j] == player2)
						value += 80;
				}
				else if ((i == 0 && j == 1 && newGrid[0][0] == ' ') || (i == 1 && j == 0 && newGrid[0][0] == ' ') || (i == 1 && j == 7 && newGrid[0][7] == ' ') || (i == 0 && j == 6 && newGrid[0][7] == ' ') ||
					(i == 7 && j == 1 && newGrid[7][0] == ' ') || (i == 6 && j == 0 && newGrid[7][0] == ' ') || (i == 7 && j == 6 && newGrid[7][7] == ' ') || (i == 6 && j == 7 && newGrid[7][7] == ' ')) {
					if (newGrid[i][j] == player)
						value -= 150;
					else if (newGrid[i][j] == player2)
						value += 150;
				}
				else if ((i == 0 || i == 7) || (j == 0 || j == 7)) {
					if (newGrid[i][j] == player)
						value += 80;
					else if (newGrid[i][j] == player2)
						value -= 80;
				}
				else if ((i == 1 && j == 1 && newGrid[0][0] == ' ') || (i == 1 && j == 6 && newGrid[0][7] == ' ') || (i == 6 && j == 1 && newGrid[7][0] == ' ') || (i == 6 && j == 6 && newGrid[7][7] == ' ')) {
					if (newGrid[i][j] == player)
						value -= 600;
					else if (newGrid[i][j] == player2)
						value += 600;
				}
				else if ((i == 1 || i == 6) || (j == 1 || j == 6)) {
					if (newGrid[i][j] == player)
						value -= 25;
					else if (newGrid[i][j] == player2)
						value += 25;
				}
				else {
					if (newGrid[i][j] == player)
						value += 3;
					else if (newGrid[i][j] == player2)
						value -= 3;
				}
			}
		}
	}
	else if (numMovesLeft > 16) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i == 0 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 0) || (i == 7 && j == 7)) {
					if (newGrid[i][j] == player)
						value += 1000;
					else if (newGrid[i][j] == player2)
						value -= 1000;
				}
				else if ((i == 0 || i == 7) && (newGrid[i][j + 1] == player2 && newGrid[i][j - 1] == player2) ||
					(j == 0 || j == 7) && (newGrid[i + 1][j] == player2 && newGrid[i - 1][j] == player2)) {
					if (newGrid[i][j] == player)
						value += 150;
					else if (newGrid[i][j] == player2)
						value -= 150;
				}
				else if ((i == 0 || i == 7) && (newGrid[i][j + 1] == player2 || newGrid[i][j - 1] == player2) ||
					(j == 0 || j == 7) && (newGrid[i + 1][j] == player2 || newGrid[i - 1][j] == player2)) {
					if (newGrid[i][j] == player)
						value -= 120;
					else if (newGrid[i][j] == player2)
						value += 120;
				}
				else if ((i == 0 && j == 1 && newGrid[0][0] == ' ') || (i == 1 && j == 0 && newGrid[0][0] == ' ') || (i == 1 && j == 7 && newGrid[0][7] == ' ') || (i == 0 && j == 6 && newGrid[0][7] == ' ') ||
					(i == 7 && j == 1 && newGrid[7][0] == ' ') || (i == 6 && j == 0 && newGrid[7][0] == ' ') || (i == 7 && j == 6 && newGrid[7][7] == ' ') || (i == 6 && j == 7 && newGrid[7][7] == ' ')) {
					if (newGrid[i][j] == player)
						value -= 200;
					else if (newGrid[i][j] == player2)
						value += 200;
				}
				else if ((i == 0 || i == 7) || (j == 0 || j == 7)) {
					if (newGrid[i][j] == player)
						value += 100;
					else if (newGrid[i][j] == player2)
						value -= 100;
				}
				else if ((i == 1 && j == 1 && newGrid[0][0] == ' ') || (i == 1 && j == 6 && newGrid[0][7] == ' ') || (i == 6 && j == 1 && newGrid[7][0] == ' ') || (i == 6 && j == 6 && newGrid[7][7] == ' ')) {
					if (newGrid[i][j] == player)
						value -= 800;
					else if (newGrid[i][j] == player2)
						value += 800;
				}
				else if ((i == 1 || i == 6) || (j == 1 || j == 6)) {
					if (newGrid[i][j] == player)
						value -= 30;
					else if (newGrid[i][j] == player2)
						value += 30;
				}
				else {
					if (newGrid[i][j] == player)
						value += 10;
					else if (newGrid[i][j] == player2)
						value -= 10;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i == 0 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 0) || (i == 7 && j == 7)) {
					if (newGrid[i][j] == player)
						value += 200;
					else if (newGrid[i][j] == player2)
						value -= 200;
				}
				else if ((i == 0 || i == 7) && (newGrid[i][j + 1] == player2 && newGrid[i][j - 1] == player2) ||
					(j == 0 || j == 7) && (newGrid[i + 1][j] == player2 && newGrid[i - 1][j] == player2)) {
					if (newGrid[i][j] == player)
						value += 40;
					else if (newGrid[i][j] == player2)
						value -= 40;
				}
				else if ((i == 0 || i == 7) && (newGrid[i][j + 1] == player2 || newGrid[i][j - 1] == player2) ||
					(j == 0 || j == 7) && (newGrid[i + 1][j] == player2 || newGrid[i - 1][j] == player2)) {
					if (newGrid[i][j] == player)
						value -= 40;
					else if (newGrid[i][j] == player2)
						value += 40;
				}
				else if ((i == 0 && j == 1 && newGrid[0][0] == ' ') || (i == 1 && j == 0 && newGrid[0][0] == ' ') || (i == 1 && j == 7 && newGrid[0][7] == ' ') || (i == 0 && j == 6 && newGrid[0][7] == ' ') ||
					(i == 7 && j == 1 && newGrid[7][0] == ' ') || (i == 6 && j == 0 && newGrid[7][0] == ' ') || (i == 7 && j == 6 && newGrid[7][7] == ' ') || (i == 6 && j == 7 && newGrid[7][7] == ' ')) {
					if (newGrid[i][j] == player)
						value -= 80;
					else if (newGrid[i][j] == player2)
						value += 80;
				}
				else if ((i == 0 || i == 7) || (j == 0 || j == 7)) {
					if (newGrid[i][j] == player)
						value += 40;
					else if (newGrid[i][j] == player2)
						value -= 40;
				}
				else if ((i == 1 && j == 1 && newGrid[0][0] == ' ') || (i == 1 && j == 6 && newGrid[0][7] == ' ') || (i == 6 && j == 1 && newGrid[7][0] == ' ') || (i == 6 && j == 6 && newGrid[7][7] == ' ')) {
					if (newGrid[i][j] == player)
						value -= 100;
					else if (newGrid[i][j] == player2)
						value += 100;
				}
				else {
					if (newGrid[i][j] == player)
						value += 20;
					else if (newGrid[i][j] == player2)
						value -= 20;
				}
			}
		}
	}

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(value, (abs(value) + 10) / 5);
	value = distribution(generator);

	return value;
}