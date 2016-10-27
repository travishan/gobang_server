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
	typedef function<void(int, uint8_t*, uint16_t, uint16_t)> SEND_FUN;
public:
	House();
	~House();

	//有玩家连接
	void addPlayer(int socketIndex);
	//加入房间
	void addInRoom(int playerIndex);
	//处理消息
	void handleRecieveData(int socketIndex, uint16_t flag, uint8_t* data, uint16_t length);
	//发送消息到客户端
	void sendData();
	//设置可调用函数类型sendFun
	void setSendFun(SEND_FUN sendFun);

private:
	//初始化room vector
	void initRooms();
	//初始化玩家vector
	void initPlayers();
private:
	//玩家数组
	vector<shared_ptr<Player>> players;
	//房间数组
	vector<shared_ptr<Room>> rooms;
	//player索引对应socket索引 
	map<PLAYER_INDEX, SOCKET_INDEX> playerSocketMap;
	//player索引对应room索引 
	map<PLAYER_INDEX, ROOM_INDEX> playerRoomMap;
	//下一个房间索引
	ROOM_INDEX roomIndex;
	//下一个玩家索引
	PLAYER_INDEX playerIndex;
	//发送函数function
	SEND_FUN sendFun;
};






#endif // !__HOUSE__H__



