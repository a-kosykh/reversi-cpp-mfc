#pragma once
#include "ReversiBoard.h"
#include "ReversiPlayer.h"

class ReversiManager
{
private:
	ReversiBoard* board;
	ReversiPlayer* player1;
	ReversiPlayer* player2;
	ReversiPlayer* currentPlayer;
	bool isGameFinished_ = false;
public:
	ReversiManager();
	bool Initialize();
	void ShowBoard();
	void MakeMove();
	bool isGameFinished();
	virtual ~ReversiManager();
};

