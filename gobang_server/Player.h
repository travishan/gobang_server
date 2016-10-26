#ifndef __PLAYER__H__
#define __PLAYER__H__

#include "define.h"

/************************

Player��
������ҵ�Socket
�¹�������
����

************************/
class Player
{
	typedef vector<B_POINT>::iterator recordIterator;
	typedef vector<B_POINT>::size_type size_t;
public:
	Player();
	Player(const string &name);
	~Player();
	//��¼һ����
	void addStep(const B_POINT &p);

	//��ȡ���Ӽ�¼��غ���
	recordIterator begin() { return record.begin(); }
	recordIterator end() { return record.end(); }
	size_t size() { return size(); }

	//get set ��غ���
	void setName(string n) { name = n; }
	string getName() {return name;}
	//void setSocket(TCPsocket s) { socket = s; }
	//TCPsocket getSocket() {return socket;}
	void setConnected(bool con) {connected = con;}
	bool getConnected() {return connected;}
	void setRegret(bool reg) {regret= reg;}
	bool getRegret() {return regret;}
	void setColor(CHESS_COLOR c) { color = c; }
	CHESS_COLOR getColor() { return color; }

private:
	//���id
	string name;
	////��ҵ�socket
	//TCPsocket socket;
	//����߹������Ӽ�¼
	vector<B_POINT> record;
	//�Ƿ�����
	bool connected;
	//�Ƿ����
	bool regret;
	//��ɫ
	CHESS_COLOR color;
};






#endif // !__PLAYER__H__

