#pragma once
#define CELL_EMPTY 0
#define CELL_BLACK 1
#define CELL_WHITE 2

// - = 0
// b = 1
// w = 2

class CellType {
private:
	
	// - = 0
	// b = 1
	// w = 2

public:
	int type;

	CellType() {
		type = CELL_EMPTY;
	}
	CellType(int _type) {
		if (type > CELL_WHITE || type < CELL_EMPTY) {
			_type = CELL_EMPTY;
		}
		type = _type;
	}
	int invert() {
		if (type == CELL_BLACK) {
			type = CELL_WHITE;
			return type;
		}
		if (type == CELL_WHITE) {
			type = CELL_BLACK;
			return type;
		}
	}

};