#pragma once
#include <string>
#include "ReversiPlayer.h"
#include "ReversiBoardMonteCarloEvaluator.h"

class ReversiComputerPlayer : public ReversiPlayer
{
public:
	ReversiComputerPlayer();
	virtual ~ReversiComputerPlayer();
	virtual bool MakeMove(unsigned int row, unsigned int col);
	virtual bool IsHuman();
};

