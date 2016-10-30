#ifndef __ROOM__H__
#define __ROOM__H__


#include "MessageDefine.h"
#include "Player.h"
#include "Referee.h"


#define PLAYTIME 30

/***************************

Room��
����ÿһ�����ڶ�ս�������Ϣ����ǰ������Ϣ�� �Լ�ӵ�в����࣬�����жϾ��ơ�


****************************/
class Room
{
	friend class Referee;
	typedef function<void(int, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	Room();
	~Room();

	// ��ʼ�����1,2
	bool addPlayer(const shared_ptr<Player> &player, int index);

	//��ʼ������
	void initRoom();

	//ִ����Ϸ�߼�
	void frame(uint32_t dt, const SEND_FUN &send);

	//get set
	int getPlayerNum() { return playerNum; }
	void setGameState(GameState state) { gameState = state; }
	GameState getGameState() { return gameState; }
private:
	/*
	��ʼ������
	*/
	void initBoard();

	/*
	��ʼ������������
	*/
	void initAttribute();

	/*
	��ʼ�����1 �� ���2
	*/
	void initP1(const shared_ptr<Player> &player, int index);
	void initP2(const shared_ptr<Player> &player, int index);

	/*
	����wait ���߼�
	*/
	void waitState(const SEND_FUN &send);

	/*
	����start ���߼�
	*/
	void startState(const SEND_FUN &send);

	/*
	����run ���߼�
	*/
	void runState(const SEND_FUN &send);

	/*
	������޵������
	*/
	void checkDisconnect();

	/*
	���GameMessage
	*/
	Game_Message getGameMessage();

	/*
	���PlayerMessage
	*/
	Player_Message getPlayerMessage(int pi);

	/*
	������Ϣ����
	*/
	void sendMessage(const SEND_FUN &send);

	/*��ȡ���
	*/
	Player* getPlayer(int pi);

private:
	/*��Ҷ���
	*/
	shared_ptr<Player> p1, p2;

	/*�������
	*/
	uint16_t p1Index, p2Index;

	/*����
	*/
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	/*��ǰ���ӷ�
	*/
	CHESS_COLOR currentPlayer;

	/*ʱ���ʱ
	*/
	uint16_t lastTime;

	/*��ǰ����
	*/
	uint16_t playerNum;

	/*��Ϸ״̬
	*/
	GameState gameState;

	/*
	ʱ���  ���ڼ��㷢����Ϣ����ʱ����
	*/
	uint32_t lastPlayerMessageTicks,lastGameMessageTicks;
};






#endif // !__ROOM__H__
