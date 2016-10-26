#include "House.h"



House::House() :roomIndex(0) {
	initRoom();
}



House::~House() {}


void House::initPlayer(int socketIndex) {
	shared_ptr<Player> p = make_shared<Player>(new Player());
	players.push_back(p);
	playerSocketMap.insert(mapPair(socketIndex, p));
	playerRoomMap.insert(mapPair(roomIndex, p));



	
}


void House::initRoom() {
	rooms.reserve(ROOM_NUM);
	for (int i = 0; i < rooms.size(); ++i) {
		shared_ptr<Room> r = make_shared<Room>(new Room());
		rooms.push_back(r);
	}
}