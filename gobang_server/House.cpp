#include "House.h"



House::House() :roomIndex(0), playerIndex(0) {
	initRooms();
}

House::~House() {}

void House::addPlayer(int socketIndex) {
	shared_ptr<Player> p = make_shared<Player>(Player());
	players.push_back(p);
	playerSocketMap.insert(mapPair(playerIndex, socketIndex));

	addInRoom(playerIndex);

	++playerIndex;

}

void House::addInRoom(int playerIndex) {
	int count = 0;
	while (!rooms[roomIndex]->addPlayer(players[playerIndex])) {//room初始化失败
		roomIndex = (roomIndex + 1) % ROOM_NUM;
		if (++count >= ROOM_NUM) {
			cout << "No empty room in house!!" << endl;
			return;
		}
	}
	//初始化成功，更新playerRoomMap
	playerRoomMap.insert(mapPair(playerIndex, roomIndex));
	roomIndex = (roomIndex + 1) % ROOM_NUM;
}

void House::handleRecieveData(int socketIndex, uint16_t flag, uint8_t *data, uint16_t length) {
	switch (flag) {
	case FLAG_CONN:
	{
		cout << "conn消息！" << endl;
	}
	break;
	case FLAG_PLAY:
	{
		B_POINT p = *((B_POINT*)data);

		cout << "横坐标:" << p.row << "竖坐标：" << p.col << endl;
	}
	break;
	case FLAG_QUIT:
	{

	}
	break;
	case FLAG_REGRET:
	{

	}
	break;
	}
}

/******************************

private

******************************/
void House::initRooms() {
	rooms.reserve(ROOM_NUM);
	for (int i = 0; i < ROOM_NUM; ++i) {
		shared_ptr<Room> r = make_shared<Room>(Room());
		rooms.push_back(r);
	}
}

void House::initPlayers() {
	players.reserve(PLAYER_NUM);
}