#pragma once

class MakeMoves {
public:
	static void makeMove(int row, int col, char player, char grid[8][8]);
private:
	static void bMove(int row, int col, char player, char grid[8][8]);
	static void uMove(int row, int col, char player, char grid[8][8]);
	static void rMove(int row, int col, char player, char grid[8][8]);
	static void lMove(int row, int col, char player, char grid[8][8]);
	static void brMove(int row, int col, char player, char grid[8][8]);
	static void blMove(int row, int col, char player, char grid[8][8]);
	static void urMove(int row, int col, char player, char grid[8][8]);
	static void ulMove(int row, int col, char player, char grid[8][8]);
};