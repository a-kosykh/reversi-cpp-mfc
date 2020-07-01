#include "stdafx.h"
#include "ReversiBoard.h"


void ReversiBoard::SetCell_(unsigned int row, unsigned int col, int type)
{
	cells[row][col].type = type;
}

void ReversiBoard::UpdatePossibleMoves_(int playerType, int opponentType)
{
	for (unsigned int i = 0; i < boardSize; ++i) {
		for (unsigned int j = 0; j < boardSize; ++j) {
			
			if (cells[i][j].type != CELL_EMPTY) {
				continue;
			}
			
			std::vector<std::pair<int, int>> upCellsToInvert = _checkUpCells(i, j, playerType, opponentType);
			std::vector<std::pair<int, int>> downCellsToInvert = _checkDownCells(i, j, playerType, opponentType);
			std::vector<std::pair<int, int>> leftCellsToInvert = _checkLeftCells(i, j, playerType, opponentType);
			std::vector<std::pair<int, int>> rightCellsToInvert = _checkRightCells(i, j, playerType, opponentType);
			std::vector<std::pair<int, int>> upLeftCellsToInvert = _checkUpLeftCells(i, j, playerType, opponentType);
			std::vector<std::pair<int, int>> upRightCellsToInvert = _checkUpRightCells(i, j, playerType, opponentType);
			std::vector<std::pair<int, int>> downLeftCellsToInvert = _checkDownLeftCells(i, j, playerType, opponentType);
			std::vector<std::pair<int, int>> downRightCellsToInvert = _checkDownRightCells(i, j, playerType, opponentType);
			
			std::vector<std::pair<int, int>> allCellsToInvert;
			allCellsToInvert.reserve(upCellsToInvert.size() + downCellsToInvert.size() + leftCellsToInvert.size() + rightCellsToInvert.size() + 
				upLeftCellsToInvert.size() + upRightCellsToInvert.size() + downLeftCellsToInvert.size() + downRightCellsToInvert.size());
			allCellsToInvert.insert(allCellsToInvert.end(), upCellsToInvert.begin(), upCellsToInvert.end());
			allCellsToInvert.insert(allCellsToInvert.end(), downCellsToInvert.begin(), downCellsToInvert.end());
			allCellsToInvert.insert(allCellsToInvert.end(), leftCellsToInvert.begin(), leftCellsToInvert.end());
			allCellsToInvert.insert(allCellsToInvert.end(), rightCellsToInvert.begin(), rightCellsToInvert.end());
			allCellsToInvert.insert(allCellsToInvert.end(), upLeftCellsToInvert.begin(), upLeftCellsToInvert.end());
			allCellsToInvert.insert(allCellsToInvert.end(), upRightCellsToInvert.begin(), upRightCellsToInvert.end());
			allCellsToInvert.insert(allCellsToInvert.end(), downLeftCellsToInvert.begin(), downLeftCellsToInvert.end());
			allCellsToInvert.insert(allCellsToInvert.end(), downRightCellsToInvert.begin(), downRightCellsToInvert.end());

			if (allCellsToInvert.size() == 0) {
				continue;
			}
			_possibleMoves.emplace((i * this->boardSize + j), allCellsToInvert);
		}
	}
}

std::vector<std::pair<int, int>> ReversiBoard::_checkUpCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = row - 1; i >= 0; --i) {
		if (i == row - 1) {
			if (cells[i][col].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, col));
				foundCloseOppo = true;
			}
		}
		if (i < row - 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i < row - 1 && foundCloseOppo) {
			if (cells[i][col].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, col));
				continue;
			}
			if (cells[i][col].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[i][col].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}

	return cellsToInvert;
}

std::vector<std::pair<int, int>> ReversiBoard::_checkDownCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = row + 1; i < boardSize; ++i) {
		if (i == row + 1) {
			if (cells[i][col].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, col));
				foundCloseOppo = true;
			}
		}
		if (i > row + 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i > row + 1 && foundCloseOppo) {
			if (cells[i][col].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, col));
				continue;
			}
			if (cells[i][col].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[i][col].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}
	return cellsToInvert;
}

std::vector<std::pair<int, int>> ReversiBoard::_checkRightCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = col + 1; i < boardSize; ++i) {
		if (i == col + 1) {
			if (cells[row][i].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(row, i));
				foundCloseOppo = true;
			}
		}
		if (i > col + 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i > col + 1 && foundCloseOppo) {
			if (cells[row][i].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(row, i));
				continue;
			}
			if (cells[row][i].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[row][i].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}

	return cellsToInvert;
}

std::vector<std::pair<int, int>> ReversiBoard::_checkLeftCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = col - 1; i >= 0; --i) {
		if (i == col - 1) {
			if (cells[row][i].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(row, i));
				foundCloseOppo = true;
			}
		}
		if (i < col - 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i < col - 1 && foundCloseOppo) {
			if (cells[row][i].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(row, i));
				continue;
			}
			if (cells[row][i].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[row][i].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}
	return cellsToInvert;
}

std::vector<std::pair<int, int>> ReversiBoard::_checkUpLeftCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = row - 1, j = col - 1; (i >= 0 && j >= 0); --i, --j) {
		if (i == row - 1 && j == col - 1) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				foundCloseOppo = true;
			}
		}
		if (i < row - 1 && j < col - 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i < row - 1 && j < col - 1 && foundCloseOppo) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				continue;
			}
			if (cells[i][j].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[i][j].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}
	return cellsToInvert;
}

std::vector<std::pair<int, int>> ReversiBoard::_checkUpRightCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = row - 1, j = col + 1; (i >= 0 && j < boardSize); --i, ++j) {
		if (i == row - 1 && j == col + 1) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				foundCloseOppo = true;
			}
		}
		if (i < row - 1 && j > col + 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i < row - 1 && j > col + 1 && foundCloseOppo) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				continue;
			}
			if (cells[i][j].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[i][j].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}
	return cellsToInvert;
}

std::vector<std::pair<int, int>> ReversiBoard::_checkDownLeftCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = row + 1, j = col - 1; (i < boardSize && j >= 0); ++i, --j) {
		if (i == row + 1 && j == col - 1) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				foundCloseOppo = true;
			}
		}
		if (i > row + 1 && j < col - 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i > row + 1 && j < col - 1 && foundCloseOppo) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				continue;
			}
			if (cells[i][j].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[i][j].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}
	return cellsToInvert;
}

std::vector<std::pair<int, int>> ReversiBoard::_checkDownRightCells(unsigned int row, unsigned int col, int playerType, int oppoType)
{
	std::vector<std::pair<int, int>> cellsToInvert;
	bool validMove = false;
	bool foundCloseOppo = false;

	for (int i = row + 1, j = col + 1; (i < boardSize && j < boardSize); ++i, ++j) {
		if (i == row + 1 && j == col + 1) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				foundCloseOppo = true;
			}
		}
		if (i > row + 1 && j > col + 1 && !foundCloseOppo) {
			cellsToInvert.clear();
			break;
		}
		if (i > row + 1 && j > col + 1 && foundCloseOppo) {
			if (cells[i][j].type == oppoType) {
				cellsToInvert.push_back(std::make_pair(i, j));
				continue;
			}
			if (cells[i][j].type == CELL_EMPTY) {
				cellsToInvert.clear();
				break;
			}
			if (cells[i][j].type == playerType) {
				validMove = true;
				break;
			}
		}
	}

	if (!validMove) {
		cellsToInvert.clear();
	}
	return cellsToInvert;
}

bool ReversiBoard::CheckNoPossibleMoves_()
{
	if (!hasLegalMoves(CELL_BLACK) && !hasLegalMoves(CELL_WHITE)) {
		return true;
	}
	return false;
}

bool ReversiBoard::CheckFullBoard_()
{
	for (unsigned int i = 0; i < boardSize; ++i) {
		for (unsigned int j = 0; j < boardSize; ++j) {
			if (cells[i][j].type == CELL_EMPTY) return false;
		}
	}
	return true;
}

int ReversiBoard::GetWinner_()
{
	unsigned int wCount = 0;
	unsigned int bCount = 0;
	for (unsigned int i = 0; i < boardSize; ++i) {
		for (unsigned int j = 0; j < boardSize; ++j) {
			if (cells[i][j].type == CELL_BLACK) bCount++;
			if (cells[i][j].type == CELL_WHITE) wCount++;
		}
	}
	if (wCount > bCount) {
		return CELL_WHITE;
	}
	if (wCount < bCount) {
		return CELL_BLACK;
	}
	return 0;
}

ReversiBoard::ReversiBoard(unsigned int size)
{
	if (size % 2 == 1) {
		size = size + 1;
	}
	this->boardSize = size;
	cells = new CellType*[size];
	for (unsigned int i = 0; i < size; ++i) {
		cells[i] = new CellType[size];
	}
	for (unsigned int i = 0; i < size; ++i) {
		for (unsigned int j = 0; j < size; ++j) {
			if (i == (size / 2)) {
				if (j == ((size / 2) - 1)) cells[i][j].type = CELL_WHITE;
				else if (j == (size / 2)) cells[i][j].type = CELL_BLACK;
				else cells[i][j] = CELL_EMPTY;
			}
			else if (i == ((size / 2) - 1)) {
				if (j == ((size / 2) - 1)) cells[i][j].type = CELL_BLACK;
				else if (j == (size / 2)) cells[i][j].type = CELL_WHITE;
				else cells[i][j].type = CELL_EMPTY;
			}
			else {
				cells[i][j].type = CELL_EMPTY;
			}
		}
	}
}

ReversiBoard::ReversiBoard(ReversiBoard * board)
{
	this->boardSize = board->GetBoardSize();
	cells = new CellType*[this->boardSize];
	for (unsigned int i = 0; i < this->boardSize; ++i)
		cells[i] = new CellType[this->boardSize];
	for (unsigned int i = 0; i < this->boardSize; ++i)
		for (unsigned int j = 0; j < boardSize; ++j)
			cells[i][j] = board->cells[i][j];
}

int ReversiBoard::GetWinner()
{
	return winner;
}

unsigned int ReversiBoard::GetBoardSize()
{
	return this->boardSize;
}


bool ReversiBoard::setCell(unsigned int row, unsigned int col, int type)
{
	_possibleMoves.clear();

	int playerType = type;
	int oppoType = CELL_EMPTY;
	if (playerType == CELL_WHITE) {
		oppoType = CELL_BLACK;
	}
	else {
		oppoType = CELL_WHITE;
	}

	UpdatePossibleMoves_(playerType, oppoType);

	std::unordered_map < int, std::vector<std::pair<int, int>> >::const_iterator got = _possibleMoves.find((row * boardSize + col));
	if (got == _possibleMoves.end()) {
		return false;
	}
	else {
		_prevInverted.clear();
		for (auto i = got->second.begin(); i != got->second.end(); ++i) {
			cells[i->first][i->second].invert();
			_prevInverted.push_back((i->first * boardSize) + i->second);
		}
		cells[row][col].type = type;
		return true;
	}
}

bool ReversiBoard::setCellEmpty(unsigned int row, unsigned int ypos)
{
	SetCell_(row, ypos, CELL_EMPTY);
	return true;
}

bool ReversiBoard::setCellNoRule(unsigned int xpos, unsigned int ypos, int type)
{
	SetCell_(xpos, ypos, type);
	return true;
}

std::vector<int> ReversiBoard::GetPrevInverted()
{
	return _prevInverted;
}

bool ReversiBoard::hasLegalMoves(int type)
{
	_possibleMoves.clear();
	
	int playerType = type;
	int oppoType = CELL_EMPTY;
	if (playerType == CELL_WHITE) {
		oppoType = CELL_BLACK;
	}
	else {
		oppoType = CELL_WHITE;
	}
	
	UpdatePossibleMoves_(playerType, oppoType);
	
	if (_possibleMoves.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool ReversiBoard::checkEndCondition()
{
	if (isGameFinished) return isGameFinished;
	if (CheckNoPossibleMoves_() || CheckFullBoard_()) {
		winner = GetWinner_();
		isGameFinished = true;
		return isGameFinished;
	}
	else {
		return false;
	}
}

std::vector<int> ReversiBoard::GetPossibleMoves(int type)
{
	_possibleMoves.clear();

	int playerType = type;
	int oppoType = CELL_EMPTY;
	if (playerType == CELL_WHITE) {
		oppoType = CELL_BLACK;
	}
	else {
		oppoType = CELL_WHITE;
	}

	UpdatePossibleMoves_(playerType, oppoType);

	std::vector<int> possibleMoves;
	for (auto i = this->_possibleMoves.begin(); i != this->_possibleMoves.end(); ++i) {
		possibleMoves.push_back((*i).first);
	}

	return possibleMoves;
}

CellType ReversiBoard::GetCell(unsigned int row, unsigned int col)
{
	return cells[row][col];
}

void ReversiBoard::ClearBoard()
{
	for (unsigned int i = 0; i < boardSize; ++i) {
		for (unsigned int j = 0; j < boardSize; ++j) {
			cells[i][j].type = CELL_EMPTY;
		}
	}
}

ReversiBoard::~ReversiBoard()
{
	for (unsigned int i = 0; i < this->boardSize; ++i) {
		delete[] cells[i];
	}
	delete[] cells;


}
