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
	Player(uint16_t socket);
	~Player();

	//记录一步棋
	void addStep(const B_POINT &p);

	//获取棋子记录相关函数
	recordIterator begin() { return record.begin(); }
	recordIterator end() { return record.end(); }
	size_t size() { return size(); }
	void push_back(const B_POINT &b) { record.push_back(b); }
	const B_POINT &front() { return record.front(); }

	//断开连接
	void disconnect() { disconnected = true; }

	//get set 相关函数
	void setName(string n) { name = n; }
	string getName() { return name; }
	void setSocketIndex(uint16_t s) { socketIndex = s; }
	uint16_t getSocketIndex() { return socketIndex; }
	void setConnected(bool con) { connected = con; }
	bool getConnected() { return connected; }
	void setDisconnected(bool dis) { disconnected = dis; }
	bool isDisconnected() { return disconnected; }
	void setRegret(bool reg) { regret = reg; }
	bool getRegret() { return regret; }
	void setColor(CHESS_COLOR c) { color = c; }
	CHESS_COLOR getColor() { return color; }
	void setRoomIndex(uint16_t index) { roomIndex = index; }
	uint16_t getRoomIndex() { return roomIndex; }
	void setPrepared(bool pre) { prepared = pre; }
	bool getPrepared() { return prepared; }
private:
	/*玩家id
	*/
	string name;

	/*玩家的socket索引
	*/
	uint16_t socketIndex;

	/*玩家走过的棋子记录
	*/
	vector<B_POINT> record;

	/*是否连接
	*/
	bool connected;

	/*是否断开
	*/
	bool disconnected;

	/*是否悔棋
	*/
	bool regret;

	/*颜色
	*/
	CHESS_COLOR color;

	/*房间号
	*/
	uint16_t roomIndex;

	/*是否准备
	*/
	bool prepared;
};






#endif // !__PLAYER__H__

