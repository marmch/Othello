#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

#include "CheckMoves.h"

vector<array<int, 2> > CheckMoves::listLegalMoves(char player, char grid[8][8]) {
	vector<array<int, 2> > moves;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isLegalMove(i, j, player, grid)) {
				array<int, 2> coord = { i,j };
				moves.push_back(coord);
				//cout << i + 1 << "," << j + 1 << endl;
			}
		}
	}
	return moves;
}

bool CheckMoves::existsLegalMove(char player, char grid[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isLegalMove(i, j, player, grid))
				return true;
		}
	}
	return false;
}

bool CheckMoves::isLegalMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row][col] != ' ')
		return false;
	if (row == 0) {
		if (col == 0) {
			return (bCheck(row, col, player, grid) || rCheck(row, col, player, grid) ||
				brCheck(row, col, player, grid));
		}
		else if (col == 7) {
			return (bCheck(row, col, player, grid) || lCheck(row, col, player, grid) ||
				blCheck(row, col, player, grid));
		}
		else {
			return (bCheck(row, col, player, grid) || lCheck(row, col, player, grid) || rCheck(row, col, player, grid) ||
				blCheck(row, col, player, grid) || brCheck(row, col, player, grid));
		}
	}
	else if (row == 7) {
		if (col == 0) {
			return (uCheck(row, col, player, grid) || rCheck(row, col, player, grid) ||
				urCheck(row, col, player, grid));
		}
		else if (col == 7) {
			return (uCheck(row, col, player, grid) || lCheck(row, col, player, grid) ||
				ulCheck(row, col, player, grid));
		}
		else {
			return (uCheck(row, col, player, grid) || lCheck(row, col, player, grid) || rCheck(row, col, player, grid) ||
				ulCheck(row, col, player, grid) || urCheck(row, col, player, grid));
		}
	}
	else if (col == 0) {
		return (bCheck(row, col, player, grid) || uCheck(row, col, player, grid) || rCheck(row, col, player, grid) ||
			brCheck(row, col, player, grid) || urCheck(row, col, player, grid));
	}
	else if (col == 7) {
		return (bCheck(row, col, player, grid) || uCheck(row, col, player, grid) || lCheck(row, col, player, grid) ||
			blCheck(row, col, player, grid) || ulCheck(row, col, player, grid));
	}
	else {
		return (bCheck(row, col, player, grid) || uCheck(row, col, player, grid) || lCheck(row, col, player, grid) || rCheck(row, col, player, grid) ||
			blCheck(row, col, player, grid) || brCheck(row, col, player, grid) || ulCheck(row, col, player, grid) || urCheck(row, col, player, grid));
	}
}
bool CheckMoves::bCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row + 1][col] == ' ' || grid[row + 1][col] == player)
		return false;
	else {
		for (int i = row + 2; i < 8; i++) {
			if (grid[i][col] == ' ')
				return false;
			if (grid[i][col] == player)
				return true;
		}
		return false;
	}
}
bool CheckMoves::uCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row - 1][col] == ' ' || grid[row - 1][col] == player)
		return false;
	else {
		for (int i = row - 2; i >= 0; i--) {
			if (grid[i][col] == ' ')
				return false;
			if (grid[i][col] == player)
				return true;
		}
		return false;
	}
}
bool CheckMoves::lCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row][col - 1] == ' ' || grid[row][col - 1] == player)
		return false;
	else {
		for (int i = col - 2; i >= 0; i--) {
			if (grid[row][i] == ' ')
				return false;
			if (grid[row][i] == player)
				return true;
		}
		return false;
	}
}
bool CheckMoves::rCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row][col + 1] == ' ' || grid[row][col + 1] == player)
		return false;
	else {
		for (int i = col + 2; i < 8; i++) {
			if (grid[row][i] == ' ')
				return false;
			if (grid[row][i] == player)
				return true;
		}
		return false;
	}
}
bool CheckMoves::blCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row + 1][col - 1] == ' ' || grid[row + 1][col - 1] == player)
		return false;
	else {
		for (int i = 0; i < min(6 - row, col - 1); i++) {
			if (grid[row + 2 + i][col - 2 - i] == ' ')
				return false;
			if (grid[row + 2 + i][col - 2 - i] == player)
				return true;
		}
		return false;
	}
}
bool CheckMoves::brCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row + 1][col + 1] == ' ' || grid[row + 1][col + 1] == player)
		return false;
	else {
		for (int i = 0; i < min(6 - row, 6 - col); i++) {
			if (grid[row + 2 + i][col + 2 + i] == ' ')
				return false;
			if (grid[row + 2 + i][col + 2 + i] == player)
				return true;
		}
		return false;
	}
}
bool CheckMoves::ulCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row - 1][col - 1] == ' ' || grid[row - 1][col - 1] == player)
		return false;
	else {
		for (int i = 0; i < min(row - 1, col - 1); i++) {
			if (grid[row - 2 - i][col - 2 - i] == ' ')
				return false;
			if (grid[row - 2 - i][col - 2 - i] == player)
				return true;
		}
		return false;
	}
}
bool CheckMoves::urCheck(int row, int col, char player, char grid[8][8]) {
	if (grid[row - 1][col + 1] == ' ' || grid[row - 1][col + 1] == player)
		return false;
	else {
		for (int i = 0; i < min(row - 1, 6 - col); i++) {
			if (grid[row - 2 - i][col + 2 + i] == ' ')
				return false;
			if (grid[row - 2 - i][col + 2 + i] == player)
				return true;
		}
		return false;
	}
}