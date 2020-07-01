#include "stdafx.h"
#include "ReversiComputerPlayer.h"



ReversiComputerPlayer::ReversiComputerPlayer()
{
}


ReversiComputerPlayer::~ReversiComputerPlayer()
{
}

bool ReversiComputerPlayer::MakeMove(unsigned int row, unsigned int col)
{
	std::cout << "Компьютер думает...: " << std::endl;

	std::vector<ReversiBoardMonteCarloEvaluator*> evaluators;
	
	std::vector<int> possibleMoves = this->board->GetPossibleMoves(this->cellType);
	for (auto i = possibleMoves.begin(); i != possibleMoves.end(); ++i) {
		int _row = *i / (int)(this->board->GetBoardSize());
		int _column = *i % (int)(this->board->GetBoardSize());
		
		if (this->board->setCell(_row, _column, this->cellType)) {
			//this->board->show();
			evaluators.push_back(new ReversiBoardMonteCarloEvaluator(this->board, 50,
				(this->cellType == CELL_BLACK) ? CELL_BLACK : CELL_WHITE, _row, _column));
			std::vector<int> prevInverted = this->board->GetPrevInverted();
			this->board->setCellEmpty(_row, _column);
			for (auto j = prevInverted.begin(); j != prevInverted.end(); ++j) {
				this->board->setCellNoRule((*j / this->board->GetBoardSize()), (*j % this->board->GetBoardSize()), 
					(this->cellType == CELL_BLACK) ? CELL_WHITE : CELL_BLACK);
			}
		}
	}

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++) {
		(*evaluator)->Evalute();
	}

	int biggestVictories = -1;

	for (auto i = evaluators.begin(); i != evaluators.end(); ++i) {
		if (this->cellType == CELL_BLACK) {
			if ((*i)->GetVictories() > biggestVictories)
				biggestVictories = (*i)->GetVictories();
		}
		else {
			if ((*i)->GetLosses() > biggestVictories)
				biggestVictories = (*i)->GetLosses();
		}
	}

	std::vector<ReversiBoardMonteCarloEvaluator*> biggestWinEvaluators;
	for (auto i = evaluators.begin(); i != evaluators.end(); ++i) {
		int numVictories;
		if (this->cellType == CELL_BLACK)
			numVictories = (*i)->GetVictories();
		else
			numVictories = (*i)->GetLosses();
		if (numVictories == biggestVictories)
			biggestWinEvaluators.push_back((*i));
	}

	this->board->setCell(biggestWinEvaluators[0]->GetRow(), biggestWinEvaluators[0]->GetColumn(), this->cellType);
	for (auto i = evaluators.begin(); i != evaluators.end(); ++i) {
		delete (*i);
	}
	evaluators.clear();
	biggestWinEvaluators.clear();
	return true;
}

bool ReversiComputerPlayer::IsHuman()
{
	return false;
}
