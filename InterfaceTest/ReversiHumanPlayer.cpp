#include "stdafx.h"
#include "ReversiHumanPlayer.h"



ReversiHumanPlayer::ReversiHumanPlayer()
{
}


ReversiHumanPlayer::~ReversiHumanPlayer()
{
	
}

bool ReversiHumanPlayer::MakeMove(unsigned int row, unsigned int col)
{
	return board->setCell(row, col, this->cellType);
}

bool ReversiHumanPlayer::IsHuman()
{
	return true;
}
