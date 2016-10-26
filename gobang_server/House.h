#ifndef __HOUSE__H__
#define __HOUSE__H__

#include "define.h"
#include "Player.h"
#include "Room.h"

class House
{
public:
	House();
	~House();

	//有玩家连接
	void initPlayer(int socketIndex);
private:
	//玩家数组
	vector<shared_ptr<Player>> players;
	//房间数组
	vector<shared_ptr<Room>> rooms;
	//socket索引对应Player的map
	map<int, shared_ptr<Player>> playerSocketMap;
	//房间号索引对应Player的map
	map<int, shared_ptr<Player>> playerRoomMap;
	//当前房间
	int roomIndex;
};






#endif // !__HOUSE__H__



