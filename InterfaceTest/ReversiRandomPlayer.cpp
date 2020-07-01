#include "stdafx.h"
#include "ReversiRandomPlayer.h"



ReversiRandomPlayer::ReversiRandomPlayer()
{
}


ReversiRandomPlayer::~ReversiRandomPlayer()
{
}

bool ReversiRandomPlayer::MakeMove(unsigned int r, unsigned int c)
{
	unsigned int row, col;
	std::vector<int> possibleMoves = this->board->GetPossibleMoves(this->cellType);
	if (possibleMoves.size() == 0) return false;

	int randomMove = possibleMoves.at(rand() % possibleMoves.size());
	int _row = randomMove / (int)(this->board->GetBoardSize());
	int _column = randomMove % (int)(this->board->GetBoardSize());


	return board->setCell(_row, _column, this->cellType);
}

bool ReversiRandomPlayer::IsHuman()
{
	return false;
}
