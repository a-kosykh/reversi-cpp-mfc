#pragma once
#include "stdafx.h"
#include "ReversiBoard.h"
class ReversiPlayer
{
protected:
	ReversiBoard* board;
	int cellType;
	CString name;
public:
	ReversiPlayer();
	virtual ~ReversiPlayer();
	void setupPlayer(CString name, int CellType);
	int GetType();
	void setBoard(ReversiBoard* board);
	virtual bool MakeMove(unsigned int row, unsigned int col) = 0;
	CString GetName();
	virtual bool IsHuman() = 0;
};

