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
	void initP1(string name, TCPsocket socket);
	void initP2(string name, TCPsocket socket);
	//��ʼ������
	void initRoom();


	//ִ����Ϸ�߼�
	void runFrame();

private:
	//��ʼ������
	void initBoard();
	//��ʼ������������
	void initAttribute();
	

private:
	//��Ҷ���
	Player *p1, *p2;
	//����
	CHESS_COLOR chessBoard[GRID_NUM][GRID_NUM];
	//��ǰ���ӷ�
	CHESS_COLOR currentPlayer;
	//ʱ���ʱ
	int lastTime;
};






#endif // !__ROOM__H__
