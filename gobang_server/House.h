#ifndef __HOUSE__H__
#define __HOUSE__H__

#include "define.h"
#include "Player.h"
#include "Room.h"


#define ROOM_NUM 10

class House
{
	typedef int PLAYER_INDEX;
	typedef int ROOM_INDEX;
	typedef int SOCKET_INDEX;
	typedef pair<int, int> mapPair;
public:
	House();
	~House();

	//有玩家连接
	void addPlayer(int socketIndex);
	//加入房间
	void addInRoom(int playerIndex);

private:
	//创建房间
	void initRoom();
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
};






#endif // !__HOUSE__H__



