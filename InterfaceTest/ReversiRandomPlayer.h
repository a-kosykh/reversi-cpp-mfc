#pragma once
#include "ReversiPlayer.h"

class ReversiRandomPlayer : public ReversiPlayer
{
public:
	ReversiRandomPlayer();
	virtual ~ReversiRandomPlayer();
	virtual bool MakeMove(unsigned int row, unsigned int col);
	virtual bool IsHuman();
};

