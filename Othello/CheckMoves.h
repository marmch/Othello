#include <vector>
#include <array>
using namespace std;
#pragma once
class CheckMoves {
public:
	static bool isLegalMove(int row, int col, char player, char grid[8][8]);
	static bool existsLegalMove(char player, char grid[8][8]);
	static vector<array<int, 2> > listLegalMoves(char player, char grid[8][8]);
private:
	static bool bCheck(int row, int col, char player, char grid[8][8]);
	static bool uCheck(int row, int col, char player, char grid[8][8]);
	static bool rCheck(int row, int col, char player, char grid[8][8]);
	static bool lCheck(int row, int col, char player, char grid[8][8]);
	static bool brCheck(int row, int col, char player, char grid[8][8]);
	static bool blCheck(int row, int col, char player, char grid[8][8]);
	static bool urCheck(int row, int col, char player, char grid[8][8]);
	static bool ulCheck(int row, int col, char player, char grid[8][8]);
};