#ifndef __REFEREE__H__
#define __REFEREE__H__

#include "define.h"

class Referee
{
public:
	Referee();
	~Referee();

	CHESS_COLOR checkBoard(const CHESS_COLOR (&board)[GRID_NUM][GRID_NUM]);
private:
	int dc[8] = { 0,1,1,1,0,-1,-1,-1 }, dr[8] = { -1,-1,0,1,1,1,0,-1 };

};






#endif // !__REFEREE__H__




