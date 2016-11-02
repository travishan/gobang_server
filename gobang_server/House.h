#ifndef __HOUSE__H__
#define __HOUSE__H__

#include "define.h"
#include "MessageDefine.h"
#include "Player.h"
#include "Room.h"


#define ROOM_NUM 50
#define PLAYER_NUM 100


class House
{
	typedef uint16_t PLAYER_INDEX;
	typedef uint16_t ROOM_INDEX;
	typedef uint16_t SOCKET_INDEX;
	typedef pair<uint16_t, uint16_t> mapPair;
	typedef map<uint16_t, uint16_t>::iterator mapIterator;
	typedef function<void(uint16_t, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	House();
	~House();

	/*
	有玩家连接
	*/
	void addPlayer(uint16_t socketIndex);

	/*
	玩家断开连接
	*/
	void disconnectPlayer(uint16_t socketIndex);

	/*
	加入房间
	*/
	void searchRoom(uint16_t playerIndex);
	bool addInRoom(uint16_t playerIndex, uint16_t rIndex);

	/*
	处理消息
	*/
	void handleRecieveData(uint16_t socketIndex, uint16_t flag, uint8_t* data, uint16_t length);
	
	/*
	设置可调用函数类型sendFun
	*/
	void setSendFun(SEND_FUN sendFun);

	/*
	执行一帧
	*/
	void run();
private:
	/*
	逻辑
	*/
	void frame(uint32_t dt);

	/*
	初始化room vector
	*/
	void initRooms();

	/*
	初始化玩家vector
	*/
	void initPlayers();

	/*
	处理不同Flag的消息
	*/
	void handlePlay(uint16_t pIndex, Player *plyr, Room *room, DataType data, LengthType length);

	/*
	通过value查找key  内部类
	*/
	class map_value_finder
	{
	public:
		map_value_finder(uint16_t value) :map_value(value) {}
		bool operator()(const map<uint16_t,uint16_t>::value_type &pair) {
			return pair.second == map_value;
		}
	private:
		uint16_t map_value;
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



