#ifndef __HOUSE__H__
#define __HOUSE__H__

#include "define.h"
#include "Player.h"
#include "Room.h"


#define ROOM_NUM 10

class House
{
	typedef pair<int, shared_ptr<Player>> mapPair;
public:
	House();
	~House();

	//���������
	void initPlayer(int socketIndex);
	//��������
	void initRoom();
private:
	//�������
	vector<shared_ptr<Player>> players;
	//��������
	vector<shared_ptr<Room>> rooms;
	//socket������ӦPlayer��map
	map<int, shared_ptr<Player>> playerSocketMap;
	//�����������ӦPlayer��map
	map<int, shared_ptr<Player>> playerRoomMap;
	//��ǰ����
	int roomIndex;
};






#endif // !__HOUSE__H__



