#pragma once
#include <string>
#include "ReversiPlayer.h"

class ReversiHumanPlayer : public ReversiPlayer
{
public:
	ReversiHumanPlayer();
	virtual ~ReversiHumanPlayer();
	virtual bool MakeMove(unsigned int row, unsigned int col);
	virtual bool IsHuman();
};

