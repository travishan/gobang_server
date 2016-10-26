#include "Referee.h"



Referee::Referee() {

}


Referee::~Referee() {}


CHESS_COLOR Referee::checkBoard(const CHESS_COLOR(&board)[GRID_NUM][GRID_NUM]) {
	for (int row = 0; row < 15; ++row) {
		for (int col = 0; col < 15; ++col) {
			CHESS_COLOR midColor = board[row][col];
			if (midColor == N) {
				continue;
			}
			for (int k = 0; k < 4; ++k) {
				int row1 = row, col1 = col, row2 = row, col2 = col, count = 0;
				bool stop1 = false, stop2 = false;
				for (int i = 0; i < 5; ++i) {
					row1 += dr[k], col1 += dc[k];
					row2 += dr[k + 4], col2 += dc[k + 4];
					if (row1 <= 14 && row1 > 0 && col1 <= 14 && col1 > 0 && !stop1) {
						if (board[row1][col1] == midColor) {
							++count;
						} else {
							stop1 = true;
						}
					}
					if (row2 <= 14 && row2 > 0 && col2 <= 14 && col2 > 0 && !stop2) {
						if (board[row2][col2] == midColor) {
							++count;
						} else {
							stop2 = true;
						}
					}
					if (count == 4) {
						return midColor;
					}
				}
			}
		}
	}
	return N;
}