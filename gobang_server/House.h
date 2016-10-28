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
	���������
	*/
	void addPlayer(int socketIndex);

	/*
	��ҶϿ�����
	*/
	void disconnectPlayer(int socketIndex);

	/*
	���뷿��
	*/
	void addInRoom(int playerIndex);

	/*
	������Ϣ
	*/
	void handleRecieveData(int socketIndex, uint16_t flag, uint8_t* data, uint16_t length);
	
	/*
	���ÿɵ��ú�������sendFun
	*/
	void setSendFun(SEND_FUN sendFun);

	/*
	ִ��һ֡
	*/
	void run();
private:
	//�߼�
	void frame(uint32_t dt);

	//��ʼ��room vector
	void initRooms();

	//��ʼ�����vector
	void initPlayers();

	//ͨ��value����key  �ڲ���
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
	//�������
	vector<shared_ptr<Player>> players;

	//��������
	vector<shared_ptr<Room>> rooms;

	//socket������Ӧplayer����
	map<SOCKET_INDEX, PLAYER_INDEX> socketPlayerMap;

	//room������Ӧplayer����
	map<ROOM_INDEX, PLAYER_INDEX> roomPlayerMap;

	//��һ����������
	ROOM_INDEX roomIndex;

	//��һ���������
	PLAYER_INDEX playerIndex;

	//���ͺ���function
	SEND_FUN sendFun;

	//ʱ���
	uint32_t lastTicks;
};






#endif // !__HOUSE__H__



