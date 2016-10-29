#ifndef __ROOM__H__
#define __ROOM__H__


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
private:
	//��Ҷ���
	shared_ptr<Player> p1, p2;

	//�������
	int p1Index, p2Index;

	//����
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	//��ǰ���ӷ�
	CHESS_COLOR currentPlayer;

	//ʱ���ʱ
	int lastTime;

	//��ǰ����
	int playerNum;

	//��Ϸ״̬
	GameState gameState;

	//ʱ���
	uint32_t lastTicks;
};






#endif // !__ROOM__H__
