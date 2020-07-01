#include "stdafx.h"
#include "ReversiBoardMonteCarloEvaluator.h"


ReversiBoardMonteCarloEvaluator::ReversiBoardMonteCarloEvaluator(ReversiBoard * board, int numIterations, int startCellType, unsigned int row, unsigned column)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numVictories = 0;
	this->numLosses = 0;
	this->row = row;
	this->column = column;
	this->startCellType = startCellType;
}

ReversiBoardMonteCarloEvaluator::~ReversiBoardMonteCarloEvaluator()
{
}

void ReversiBoardMonteCarloEvaluator::EvaluteBoard()
{
	ReversiBoard* b = new ReversiBoard(this->board);
	//b->show();
	ReversiRandomPlayer* player1 = new ReversiRandomPlayer();
	ReversiRandomPlayer* player2 = new ReversiRandomPlayer();
	ReversiRandomPlayer* currentPlayer;
	bool bGameFinished = false;

	player1->setupPlayer(L"RandomB", CELL_BLACK);
	player2->setupPlayer(L"RandomW", CELL_WHITE);
	player1->setBoard(b);
	player2->setBoard(b);
	currentPlayer = (this->startCellType == CELL_BLACK) ? player1 : player2;

	if (b->checkEndCondition()) {
		if (b->GetWinner() == 0) {
			numDraws++;
		}
		if (b->GetWinner() == CELL_BLACK) {
			numVictories++;
		}
		if (b->GetWinner() == CELL_WHITE) {
			numLosses++;
		}
		bGameFinished = true;
		delete b;
		delete player1;
		delete player2;
		return;
	}

	while (!bGameFinished) {
		bool hasLegalMoves = b->hasLegalMoves(currentPlayer->GetType());
		std::vector<int> possibleMoves = b->GetPossibleMoves(currentPlayer->GetType());
		//b->show();


		if (hasLegalMoves && (possibleMoves.size() > 0)) {
			while (!currentPlayer->MakeMove(0,0)) {}
		}

		if (b->checkEndCondition()) {
			
			//b->show();
			if (b->GetWinner() == 0) numDraws++;
			if (b->GetWinner() == player1->GetType()) numVictories++;
			if (b->GetWinner() == player2->GetType()) numLosses++;
			bGameFinished = true;
			delete b;
			delete player1;
			delete player2;
			return;
		}
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
	delete b;
	delete player1;
	delete player2;
}

void ReversiBoardMonteCarloEvaluator::Evalute()
{
	for (unsigned int i = 0; i < numGames; ++i) {
		EvaluteBoard();
	}
}
