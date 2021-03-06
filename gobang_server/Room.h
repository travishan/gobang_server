#ifndef __ROOM__H__
#define __ROOM__H__


#include "MessageDefine.h"
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
	typedef function<void(uint16_t, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	Room();
	~Room();

	/*
	初始化玩家1,2
	*/
	bool addPlayer(const shared_ptr<Player> &player, uint16_t index);

	/*
	初始化房间
	*/
	void initRoom();

	/*
	清空房间
	*/
	void releaseRoom();

	/*
	执行游戏逻辑
	*/
	void frame(uint32_t dt, const SEND_FUN &send);

	/*
	走一步棋
	*/
	void playOneStep(uint16_t playerIndex, B_POINT point);

	/*获取玩家
	*/
	Player* getPlayer(uint16_t pi);
	Player* getAnotherPlayer(uint16_t pi);

	/*
	换边
	*/
	void changeSide();

	//get set
	uint16_t getPlayerNum() { return playerNum; }
	void setGameState(GameState state) { gameState = state; }
	GameState getGameState() { return gameState; }
	void setRoomIndex(uint16_t index) { roomIndex = index; }
	uint16_t getRoomIndex() { return roomIndex; }
	void setWinner(uint16_t player) { winner = player; }
	uint16_t getWinner() { return winner; }

	/*
	玩家离开
	*/
	void playerLeave(int index);

private:
	/*
	初始化棋盘
	*/
	void initBoard();

	/*
	交换双方的颜色
	*/
	void exchangeColor();

	/*
	初始化棋局相关属性
	*/
	void initAttribute(CHESS_COLOR curSide, uint16_t time);

	/*
	初始化玩家1 和 玩家2
	*/
	void initP1(const shared_ptr<Player> &player, uint16_t index);
	void initP2(const shared_ptr<Player> &player, uint16_t index);

	/*
	释放玩家
	*/
	void releasePlayer();

	/*
	处理wait 的逻辑
	*/
	void waitState();

	/*
	处理start 的逻辑
	*/
	void startState();

	/*
	处理run 的逻辑
	*/
	void runState();

	/*
	检查有无掉线玩家
	*/
	bool checkDisconnect();

	/*
	获得GameMessage
	*/
	Game_Message getGameMessage();

	/*
	获得PlayerMessage
	*/
	Player_Message getPlayerMessage(uint16_t pi);

	/*
	发送消息函数
	*/
	void sendMessage(const SEND_FUN &send);

	/*
	重新开始
	*/
	void restartInit();

private:
	/*玩家对象
	*/
	shared_ptr<Player> p1, p2;

	/*玩家索引
	*/
	uint16_t p1Index, p2Index;

	/*房间索引
	*/
	uint16_t roomIndex;

	/*棋盘
	*/
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	/*当前下子方
	*/
	uint16_t currentPlayer;

	/*时间计时
	*/
	uint16_t lastTime;

	/*当前人数
	*/
	uint16_t playerNum;

	/*游戏状态
	*/
	GameState gameState;

	/*
	时间戳  用于计算发送消息包的时间间隔
	*/
	uint32_t lastPlayerMessageTicks,lastGameMessageTicks;

	/*
	裁判对象
	*/
	Referee referee;

	/*
	胜利方
	*/
	uint16_t winner;
};






#endif // !__ROOM__H__
