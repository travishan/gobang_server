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

	//���������
	void addPlayer(int socketIndex);
	//���뷿��
	void addInRoom(int playerIndex);

private:
	//��������
	void initRoom();
private:
	//�������
	vector<shared_ptr<Player>> players;
	//��������
	vector<shared_ptr<Room>> rooms;
	//player������Ӧsocket���� 
	map<PLAYER_INDEX, SOCKET_INDEX> playerSocketMap;
	//player������Ӧroom���� 
	map<PLAYER_INDEX, ROOM_INDEX> playerRoomMap;
	//��һ����������
	ROOM_INDEX roomIndex;
	//��һ���������
	PLAYER_INDEX playerIndex;
};






#endif // !__HOUSE__H__



