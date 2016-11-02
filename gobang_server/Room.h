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
	typedef function<void(uint16_t, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	Room();
	~Room();

	/*
	��ʼ�����1,2
	*/
	bool addPlayer(const shared_ptr<Player> &player, uint16_t index);

	/*
	��ʼ������
	*/
	void initRoom();

	/*
	��շ���
	*/
	void releaseRoom();

	/*
	ִ����Ϸ�߼�
	*/
	void frame(uint32_t dt, const SEND_FUN &send);

	/*
	��һ����
	*/
	void playOneStep(uint16_t playerIndex, B_POINT point);

	/*��ȡ���
	*/
	Player* getPlayer(uint16_t pi);
	Player* getAnotherPlayer(uint16_t pi);

	/*
	����
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
	����뿪
	*/
	void playerLeave(int index);

private:
	/*
	��ʼ������
	*/
	void initBoard();

	/*
	����˫������ɫ
	*/
	void exchangeColor();

	/*
	��ʼ������������
	*/
	void initAttribute(CHESS_COLOR curSide, uint16_t time);

	/*
	��ʼ�����1 �� ���2
	*/
	void initP1(const shared_ptr<Player> &player, uint16_t index);
	void initP2(const shared_ptr<Player> &player, uint16_t index);

	/*
	�ͷ����
	*/
	void releasePlayer();

	/*
	����wait ���߼�
	*/
	void waitState();

	/*
	����start ���߼�
	*/
	void startState();

	/*
	����run ���߼�
	*/
	void runState();

	/*
	������޵������
	*/
	bool checkDisconnect();

	/*
	���GameMessage
	*/
	Game_Message getGameMessage();

	/*
	���PlayerMessage
	*/
	Player_Message getPlayerMessage(uint16_t pi);

	/*
	������Ϣ����
	*/
	void sendMessage(const SEND_FUN &send);

	/*
	���¿�ʼ
	*/
	void restartInit();

private:
	/*��Ҷ���
	*/
	shared_ptr<Player> p1, p2;

	/*�������
	*/
	uint16_t p1Index, p2Index;

	/*��������
	*/
	uint16_t roomIndex;

	/*����
	*/
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];

	/*��ǰ���ӷ�
	*/
	uint16_t currentPlayer;

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

	/*
	���ж���
	*/
	Referee referee;

	/*
	ʤ����
	*/
	uint16_t winner;
};






#endif // !__ROOM__H__
