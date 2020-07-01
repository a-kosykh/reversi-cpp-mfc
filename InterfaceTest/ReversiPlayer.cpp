#include "stdafx.h"
#include "ReversiPlayer.h"





ReversiPlayer::ReversiPlayer()
{
}


ReversiPlayer::~ReversiPlayer()
{
	this->board = nullptr;
}

void ReversiPlayer::setupPlayer(CString name, int CellType)
{
	this->name = name;
	this->cellType = CellType;
}

int ReversiPlayer::GetType()
{
	return cellType;
}

void ReversiPlayer::setBoard(ReversiBoard * board)
{
	this->board = board;
}

CString ReversiPlayer::GetName()
{
	return name;
}
