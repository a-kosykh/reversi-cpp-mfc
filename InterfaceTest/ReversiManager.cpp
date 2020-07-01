#include "stdafx.h"
#include "ReversiManager.h"
#include "ReversiHumanPlayer.h"
#include "ReversiComputerPlayer.h"


ReversiManager::ReversiManager()
{
}

bool ReversiManager::Initialize()
{
	return true;
}


void ReversiManager::ShowBoard()
{
}

void ReversiManager::MakeMove()
{
	ShowBoard();
	bool hasLegalMoves = this->board->hasLegalMoves(this->currentPlayer->GetType());
	if (!hasLegalMoves) {
		std::cout << "Нет допустимых ходов для игрока " << currentPlayer->GetName() << std::endl;
		ShowBoard();
	}
	if (hasLegalMoves) {
		while (!currentPlayer->MakeMove(0,0)) {
			std::cout << "Недопустимый ход" << std::endl;
			ShowBoard();
		}
	}

	if (this->board->checkEndCondition()) {
		if (this->board->GetWinner() == 0) {
			std::cout << "Ничья" << std::endl;
		}
		else {
			if (this->board->GetWinner() == CELL_BLACK) {
				std::cout << "Победитель: Черный фишки" << std::endl;
			}
			if (this->board->GetWinner() == CELL_WHITE) {
				std::cout << "Победитель: Белые фишки" << std::endl;
			}
		}
		this->isGameFinished_ = true;
		ShowBoard();
		return;
	}
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool ReversiManager::isGameFinished()
{
	return isGameFinished_;
}

ReversiManager::~ReversiManager()
{
	delete this->board;
	delete this->player1;
	delete this->player2;
}
