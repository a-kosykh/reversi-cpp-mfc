#pragma once
#include "ReversiBoard.h"
#include "ReversiRandomPlayer.h"
#include "CellType.h"

class ReversiBoardMonteCarloEvaluator
{
private:
	ReversiBoard* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int row, column;
	int startCellType;
public:
	ReversiBoardMonteCarloEvaluator(ReversiBoard* board, int numIterations, int startCellType, 
		unsigned int row, unsigned column);
	~ReversiBoardMonteCarloEvaluator();
	void EvaluteBoard();
	void Evalute();
	int GetVictories() { return numVictories; }
	int GetLosses() { return numLosses; }
	int GetDraws() { return numDraws; }
	int GetRow() { return row; }
	int GetColumn() { return column; }
};

