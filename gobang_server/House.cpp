#include "House.h"



House::House() :roomIndex(0), playerIndex(0) {
	initRoom();
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


/******************************

private

******************************/
void House::initRoom() {
	rooms.reserve(ROOM_NUM);
	for (int i = 0; i < rooms.size(); ++i) {
		shared_ptr<Room> r = make_shared<Room>(Room());
		rooms.push_back(r);
	}
}