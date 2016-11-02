#include "House.h"



House::House() :roomIndex(0), playerIndex(0) {
	initRooms();
}

House::~House() {

}

/*
有玩家连接
*/
void House::addPlayer(uint16_t socketIndex) {
	shared_ptr<Player> p = make_shared<Player>(Player(socketIndex));
	players.push_back(p);
	socketPlayerMap.insert(mapPair(socketIndex, playerIndex));

	searchRoom(playerIndex);

	++playerIndex;

}

/*
玩家断开连接
*/
void House::disconnectPlayer(uint16_t socketIndex) {
	mapIterator it = socketPlayerMap.find(socketIndex);
	auto pIndex = it->second;
	Player *player = players.at(pIndex).get();
	if (player != nullptr) {
		uint16_t rIndex = player->getRoomIndex();
		auto room = rooms[rIndex].get();
		player->disconnect();
		room->playerLeave(pIndex);
	}
}

/*
加入房间
*/
void House::searchRoom(uint16_t playerIndex) {
	uint16_t count = 0;
	uint16_t roomHaveOnePlayerIndex = 65535;
	//首先找寻有无只有一个玩家的房间
	for (int i = 0; i < ROOM_NUM; ++i) {
		if (rooms[i]->getPlayerNum() == 1) {
			if (addInRoom(playerIndex, i)) {
				return;
			}
		}
	}
	//若所有房间都为空，则按顺序将玩家加入房间
	while (!addInRoom(playerIndex, roomIndex)) {//room初始化失败
		roomIndex = (roomIndex + 1) % ROOM_NUM;
		if (++count >= ROOM_NUM) {
			cout << "No empty room in house!!" << endl;
			return;
		}
	}
}

bool House::addInRoom(uint16_t playerIndex, uint16_t rIndex) {
	if (rooms[roomIndex]->addPlayer(players[playerIndex], playerIndex)) {
		cout << "Player " << playerIndex << " is in room " << roomIndex << endl;
		//初始化成功，更新playerRoomMap
		roomPlayerMap.insert(mapPair(roomIndex, playerIndex));
		if (rooms[roomIndex]->getPlayerNum() >= 2) {
			roomIndex = (roomIndex + 1) % ROOM_NUM;
		}
		return true;
	} else {
		return false;
	}
	//while (!) {//room初始化失败
	//	roomIndex = (roomIndex + 1) % ROOM_NUM;
	//	if (++count >= ROOM_NUM) {
	//		cout << "No empty room in house!!" << endl;
	//		return;
	//	}
	//}

}

void House::handleRecieveData(uint16_t socketIndex, uint16_t flag, uint8_t *data, uint16_t length) {
	//通过socketIndex 找到对应的palyerIndex
	//mapIterator it = find_if(playerSocketMap.begin(), playerSocketMap.end(), map_value_finder(socketIndex));
	mapIterator it = socketPlayerMap.find(socketIndex);
	if (it == socketPlayerMap.end()) {//如果没有找到则返回
		cerr << "不能通过socket找到玩家" << endl;
		return;
	}
	//找到的map第一个key为socketIndex，value为palyerIndex
	uint16_t playerIndex = it->second;
	Player *player = players.at(it->second).get();
	uint16_t rIndex = player->getRoomIndex();
	auto room = rooms[rIndex].get();
	switch (flag) {
	case FLAG_PLAY:
	{
		handlePlay(playerIndex, player, room, data, length);
	}break;
	case FLAG_ASK_REGRET:
	{

	}break;
	case FLAG_RETURN_REGRET:
	{

	}break;
	case FLAG_READY:
	{
		player->setPrepared(true);
		cout << "Player " << playerIndex << " is ready." << endl;
	}break;
	case FLAG_RESTART:
	{
		player->setPrepared(true);
		cout << "Player" << playerIndex << " want to start again." << endl;
	}break;
	}
}

/*
处理不同Flag的消息 
记得delete data！
记得delete data！
记得delete data！
*/
void House::handlePlay(uint16_t pIndex, Player *plyr, Room *room, DataType data, LengthType length) {
	B_POINT p;
	memcpy(&p, data, length);
	cout << "横坐标:" << p.row << "竖坐标：" << p.col << endl;
	room->playOneStep(pIndex, p);
	cout << "Room :" << room->getRoomIndex() << endl;
	auto plyr2 = room->getAnotherPlayer(pIndex);
	if (plyr2 == nullptr) return;
	sendFun(plyr2->getSocketIndex(), data, length, FLAG_PLAY_INFO);//发送给另外一方
	room->changeSide();
	delete data;
}


//执行一帧
void House::run() {
	uint32_t curTicks = SDL_GetTicks();
	uint32_t dt = curTicks - lastTicks;
	if (dt < 1000) {//距离上次时间不足100ms，不更新
		return;
	}
	//服务器以每秒10帧的速率更新
	frame(dt);
	lastTicks = curTicks;
}

//逻辑
void House::frame(uint32_t dt) {
	for (size_t i = 0; i < rooms.size(); ++i) {
		Room *room = rooms[i].get();
		room->frame(dt,sendFun);
	}
}

//设置可调用函数类型sendFun
void House::setSendFun(SEND_FUN sendFun) {
	this->sendFun = sendFun;
}

/******************************

private

******************************/
void House::initRooms() {
	rooms.reserve(ROOM_NUM);
	for (uint16_t i = 0; i < ROOM_NUM; ++i) {
		shared_ptr<Room> r = make_shared<Room>(Room());
		r->setRoomIndex(i);
		rooms.push_back(r);
	}
}

void House::initPlayers() {
	players.reserve(PLAYER_NUM);
}