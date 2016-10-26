#ifndef __PLAYER__H__
#define __PLAYER__H__

#include "define.h"

/************************

Player类
保存玩家的Socket
下过的棋子
名字

************************/
class Player
{
	typedef vector<B_POINT>::iterator recordIterator;
	typedef vector<B_POINT>::size_type size_t;
public:
	Player();
	Player(const string &name);
	~Player();
	//记录一步棋
	void addStep(const B_POINT &p);

	//获取棋子记录相关函数
	recordIterator begin() { return record.begin(); }
	recordIterator end() { return record.end(); }
	size_t size() { return size(); }

	//get set 相关函数
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
	//玩家id
	string name;
	////玩家的socket
	//TCPsocket socket;
	//玩家走过的棋子记录
	vector<B_POINT> record;
	//是否连接
	bool connected;
	//是否悔棋
	bool regret;
	//颜色
	CHESS_COLOR color;
};






#endif // !__PLAYER__H__

