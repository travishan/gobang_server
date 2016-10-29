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
	typedef function<void(int, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	Room();
	~Room();

	// 初始化玩家1,2
	bool addPlayer(const shared_ptr<Player> &player, int index);

	//初始化房间
	void initRoom();

	//执行游戏逻辑
	void frame(uint32_t dt, const SEND_FUN &send);

	//get set
	int getPlayerNum() { return playerNum; }
	void setGameState(GameState state) { gameState = state; }
	GameState getGameState() { return gameState; }
private:
	/*
	初始化棋盘
	*/
	void initBoard();

	/*
	初始化棋局相关属性
	*/
	void initAttribute();

	/*
	初始化玩家1 和 玩家2
	*/
	void initP1(const shared_ptr<Player> &player, int index);
	void initP2(const shared_ptr<Player> &player, int index);

	/*
	处理wait 的逻辑
	*/
	void waitState(const SEND_FUN &send);

	/*
	处理start 的逻辑
	*/
	void startState(const SEND_FUN &send);

	/*
	处理run 的逻辑
	*/
	void runState(const SEND_FUN &send);

	/*
	检查有无掉线玩家
	*/
	void checkDisconnect();
private:
	//玩家对象
	shared_ptr<Player> p1, p2;

	//玩家索引
	int p1Index, p2Index;

	//棋盘
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	//当前下子方
	CHESS_COLOR currentPlayer;

	//时间计时
	int lastTime;

	//当前人数
	int playerNum;

	//游戏状态
	GameState gameState;

	//时间戳
	uint32_t lastTicks;
};






#endif // !__ROOM__H__
