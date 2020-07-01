#pragma once
#include "CellType.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

class ReversiBoard
{
private:
	void SetCell_(unsigned int xpos, unsigned int ypos, int type);
	CellType** cells;
	unsigned int boardSize;
	std::unordered_map < int, std::vector<std::pair<int, int>> > _possibleMoves;
	std::vector<int> _prevInverted;
	
	int winner = 0;
	
	void UpdatePossibleMoves_(int playerType, int opponentType);
	std::vector<std::pair<int, int>> _checkUpCells(unsigned int row, unsigned int col, int playerType, int oppoType);
	std::vector<std::pair<int, int>> _checkDownCells(unsigned int row, unsigned int col, int playerType, int oppoType);
	std::vector<std::pair<int, int>> _checkRightCells(unsigned int row, unsigned int col, int playerType, int oppoType);
	std::vector<std::pair<int, int>> _checkLeftCells(unsigned int row, unsigned int col, int playerType, int oppoType);
	std::vector<std::pair<int, int>> _checkUpLeftCells(unsigned int row, unsigned int col, int playerType, int oppoType);
	std::vector<std::pair<int, int>> _checkUpRightCells(unsigned int row, unsigned int col, int playerType, int oppoType);
	std::vector<std::pair<int, int>> _checkDownLeftCells(unsigned int row, unsigned int col, int playerType, int oppoType);
	std::vector<std::pair<int, int>> _checkDownRightCells(unsigned int row, unsigned int col, int playerType, int oppoType);

	bool CheckNoPossibleMoves_();
	bool CheckFullBoard_();
	int GetWinner_();

public:
	
	ReversiBoard(unsigned int size);
	ReversiBoard(ReversiBoard* board);
	bool isGameFinished = false;
	int GetWinner();
	unsigned int GetBoardSize();

	bool setCell(unsigned int xpos, unsigned int ypos, int type);
	bool setCellEmpty(unsigned int row, unsigned int ypos);
	bool setCellNoRule(unsigned int xpos, unsigned int ypos, int type);
	std::vector<int> GetPrevInverted();
	bool hasLegalMoves(int type);
	bool checkEndCondition();
	std::vector<int> GetPossibleMoves(int type);
	CellType GetCell(unsigned int row, unsigned int col);

	void ClearBoard();
	virtual ~ReversiBoard();
};

