#ifndef __HOUSE__H__
#define __HOUSE__H__

#include "define.h"
#include "Player.h"
#include "Room.h"


#define ROOM_NUM 50
#define PLAYER_NUM 100


class House
{
	typedef int PLAYER_INDEX;
	typedef int ROOM_INDEX;
	typedef int SOCKET_INDEX;
	typedef pair<int, int> mapPair;
	typedef map<int, int>::iterator mapIterator;
	typedef function<void(int, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	House();
	~House();

	/*
	有玩家连接
	*/
	void addPlayer(int socketIndex);

	/*
	玩家断开连接
	*/
	void disconnectPlayer(int socketIndex);

	/*
	加入房间
	*/
	void addInRoom(int playerIndex);

	/*
	处理消息
	*/
	void handleRecieveData(int socketIndex, uint16_t flag, uint8_t* data, uint16_t length);
	
	/*
	设置可调用函数类型sendFun
	*/
	void setSendFun(SEND_FUN sendFun);

	/*
	执行一帧
	*/
	void run();
private:
	//逻辑
	void frame(uint32_t dt);

	//初始化room vector
	void initRooms();

	//初始化玩家vector
	void initPlayers();

	//通过value查找key  内部类
	class map_value_finder
	{
	public:
		map_value_finder(int value) :map_value(value) {}
		bool operator()(const map<int,int>::value_type &pair) {
			return pair.second == map_value;
		}
	private:
		int map_value;
	};
private:
	//玩家数组
	vector<shared_ptr<Player>> players;

	//房间数组
	vector<shared_ptr<Room>> rooms;

	//socket索引对应player索引
	map<SOCKET_INDEX, PLAYER_INDEX> socketPlayerMap;

	//room索引对应player索引
	map<ROOM_INDEX, PLAYER_INDEX> roomPlayerMap;

	//下一个房间索引
	ROOM_INDEX roomIndex;

	//下一个玩家索引
	PLAYER_INDEX playerIndex;

	//发送函数function
	SEND_FUN sendFun;

	//时间戳
	uint32_t lastTicks;
};






#endif // !__HOUSE__H__



