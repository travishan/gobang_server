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
	���������
	*/
	void addPlayer(uint16_t socketIndex);

	/*
	��ҶϿ�����
	*/
	void disconnectPlayer(uint16_t socketIndex);

	/*
	���뷿��
	*/
	void searchRoom(uint16_t playerIndex);
	bool addInRoom(uint16_t playerIndex, uint16_t rIndex);

	/*
	������Ϣ
	*/
	void handleRecieveData(uint16_t socketIndex, uint16_t flag, uint8_t* data, uint16_t length);
	
	/*
	���ÿɵ��ú�������sendFun
	*/
	void setSendFun(SEND_FUN sendFun);

	/*
	ִ��һ֡
	*/
	void run();
private:
	/*
	�߼�
	*/
	void frame(uint32_t dt);

	/*
	��ʼ��room vector
	*/
	void initRooms();

	/*
	��ʼ�����vector
	*/
	void initPlayers();

	/*
	����ͬFlag����Ϣ
	*/
	void handlePlay(uint16_t pIndex, Player *plyr, Room *room, DataType data, LengthType length);

	/*
	ͨ��value����key  �ڲ���
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



