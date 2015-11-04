#pragma once
class Negamax {
public:
	static array<int, 2> findMove(char player, char grid[8][8], long cputime);
private:
	static int negaMax(int row, int col, int depth, int alpha, int beta, char player, char grid[8][8], long cputime);
	static int negaMaxDraw(int row, int col, int depth, int alpha, int beta, char player, char grid[8][8], long cputime);
	static int evalMove(int row, int col, char player, char grid[8][8]);
};