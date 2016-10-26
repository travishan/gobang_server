#ifndef __ROOM__H__
#define __ROOM__H__


#include "Player.h"
#include "Referee.h"


#define PLAYTIME 30

/***************************

Room类
保存每一对正在对战的玩家信息，当前局面信息， 以及拥有裁判类，用于判断局势。


****************************/
class Room
{
	friend class Referee;
public:
	Room();
	~Room();

	// 初始化玩家1,2
	void initP1(const shared_ptr<Player> &player);
	void initP2(const shared_ptr<Player> &player);
	//初始化房间
	void initRoom();


	//执行游戏逻辑
	void runFrame();

private:
	//初始化棋盘
	void initBoard();
	//初始化棋局相关属性
	void initAttribute();
	

private:
	//玩家对象
	shared_ptr<Player> p1, p2;
	//棋盘
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];
	//当前下子方
	CHESS_COLOR currentPlayer;
	//时间计时
	int lastTime;
};






#endif // !__ROOM__H__
