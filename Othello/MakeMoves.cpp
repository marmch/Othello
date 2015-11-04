#include <algorithm>
using namespace std;

#include "MakeMoves.h"

void MakeMoves::makeMove(int row, int col, char player, char grid[8][8]) {
	grid[row][col] = player;
	if (row == 0) {
		if (col == 0) {
			bMove(row, col, player, grid);
			rMove(row, col, player, grid);
			brMove(row, col, player, grid);
		}
		else if (col == 7) {
			bMove(row, col, player, grid);
			lMove(row, col, player, grid);
			blMove(row, col, player, grid);
		}
		else {
			bMove(row, col, player, grid);
			lMove(row, col, player, grid);
			rMove(row, col, player, grid);
			blMove(row, col, player, grid);
			brMove(row, col, player, grid);
		}
	}
	else if (row == 7) {
		if (col == 0) {
			uMove(row, col, player, grid);
			rMove(row, col, player, grid);
			urMove(row, col, player, grid);
		}
		else if (col == 7) {
			uMove(row, col, player, grid);
			lMove(row, col, player, grid);
			ulMove(row, col, player, grid);
		}
		else {
			uMove(row, col, player, grid);
			lMove(row, col, player, grid);
			rMove(row, col, player, grid);
			ulMove(row, col, player, grid);
			urMove(row, col, player, grid);
		}
	}
	else if (col == 0) {
		bMove(row, col, player, grid);
		uMove(row, col, player, grid);
		rMove(row, col, player, grid);
		brMove(row, col, player, grid);
		urMove(row, col, player, grid);
	}
	else if (col == 7) {
		bMove(row, col, player, grid);
		uMove(row, col, player, grid);
		lMove(row, col, player, grid);
		blMove(row, col, player, grid);
		ulMove(row, col, player, grid);
	}
	else {
		bMove(row, col, player, grid);
		uMove(row, col, player, grid);
		lMove(row, col, player, grid);
		rMove(row, col, player, grid);
		blMove(row, col, player, grid);
		brMove(row, col, player, grid);
		ulMove(row, col, player, grid);
		urMove(row, col, player, grid);
	}
}
void MakeMoves::bMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row + 1][col] == ' ' || grid[row + 1][col] == player)
		return;
	for (int i = row + 2; i < 8; i++) {
		if (grid[i][col] == ' ')
			return;
		if (grid[i][col] == player) {
			for (int j = i - 1; j > row; j--)
				grid[j][col] = player;
			break;
		}
	}
}
void MakeMoves::uMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row - 1][col] == ' ' || grid[row - 1][col] == player)
		return;
	for (int i = row - 2; i >= 0; i--) {
		if (grid[i][col] == ' ')
			return;
		if (grid[i][col] == player) {
			for (int j = i + 1; j < row; j++)
				grid[j][col] = player;
			break;
		}
	}
}
void MakeMoves::lMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row][col - 1] == ' ' || grid[row][col - 1] == player)
		return;
	for (int i = col - 2; i >= 0; i--) {
		if (grid[row][i] == ' ')
			return;
		if (grid[row][i] == player) {
			for (int j = i + 1; j < col; j++)
				grid[row][j] = player;
			break;
		}
	}
}
void MakeMoves::rMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row][col + 1] == ' ' || grid[row][col + 1] == player)
		return;
	for (int i = col + 2; i < 8; i++) {
		if (grid[row][i] == ' ')
			return;
		if (grid[row][i] == player) {
			for (int j = i - 1; j > col; j--)
				grid[row][j] = player;
			break;
		}
	}
}
void MakeMoves::blMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row + 1][col - 1] == ' ' || grid[row + 1][col - 1] == player)
		return;
	for (int i = 0; i < min(6 - row, col - 1); i++) {
		if (grid[row + 2 + i][col - 2 - i] == ' ')
			return;
		if (grid[row + 2 + i][col - 2 - i] == player) {
			for (int j = i - 1; j >= -1; j--)
				grid[row + 2 + j][col - 2 - j] = player;
			break;
		}
	}
}
void MakeMoves::brMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row + 1][col + 1] == ' ' || grid[row + 1][col + 1] == player)
		return;
	for (int i = 0; i < min(6 - row, 6 - col); i++) {
		if (grid[row + 2 + i][col + 2 + i] == ' ')
			return;
		if (grid[row + 2 + i][col + 2 + i] == player) {
			for (int j = i - 1; j >= -1; j--)
				grid[row + 2 + j][col + 2 + j] = player;
			break;
		}
	}
}
void MakeMoves::ulMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row - 1][col - 1] == ' ' || grid[row - 1][col - 1] == player)
		return;
	for (int i = 0; i < min(row - 1, col - 1); i++) {
		if (grid[row - 2 - i][col - 2 - i] == ' ')
			return;
		if (grid[row - 2 - i][col - 2 - i] == player) {
			for (int j = i - 1; j >= -1; j--)
				grid[row - 2 - j][col - 2 - j] = player;
			break;
		}
	}
}
void MakeMoves::urMove(int row, int col, char player, char grid[8][8]) {
	if (grid[row - 1][col + 1] == ' ' || grid[row - 1][col + 1] == player)
		return;
	for (int i = 0; i < min(row - 1, 6 - col); i++) {
		if (grid[row - 2 - i][col + 2 + i] == ' ')
			return;
		if (grid[row - 2 - i][col + 2 + i] == player) {
			for (int j = i - 1; j >= -1; j--)
				grid[row - 2 - j][col + 2 + j] = player;
			break;
		}
	}
}