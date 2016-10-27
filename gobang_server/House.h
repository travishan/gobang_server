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
public:
	House();
	~House();

	//���������
	void addPlayer(int socketIndex);
	//���뷿��
	void addInRoom(int playerIndex);
	//������Ϣ
	void handleRecieveData(int socketIndex, uint16_t flag, uint8_t* data, uint16_t length);

private:
	//��ʼ��room vector
	void initRooms();
	//��ʼ�����vector
	void initPlayers();
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



