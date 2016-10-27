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
public:
	Room();
	~Room();

	// ��ʼ�����1,2
	bool addPlayer(const shared_ptr<Player> &player);
	//��ʼ������
	void initRoom();


	//ִ����Ϸ�߼�
	void runFrame();


	//get set
	
	int getPlayerNum() { return playerNum; }
private:
	//��ʼ������
	void initBoard();
	//��ʼ������������
	void initAttribute();
	//��ʼ�����
	void initP1(const shared_ptr<Player> &player);
	void initP2(const shared_ptr<Player> &player);

private:
	//��Ҷ���
	shared_ptr<Player> p1, p2;
	//����
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];
	//��ǰ���ӷ�
	CHESS_COLOR currentPlayer;
	//ʱ���ʱ
	int lastTime;
	//��ǰ����
	int playerNum;
};






#endif // !__ROOM__H__
