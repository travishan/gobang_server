#include "House.h"



House::House() :roomIndex(0), playerIndex(0) {
	initRooms();
}

House::~House() {

}

/*
有玩家连接
*/
void House::addPlayer(int socketIndex) {
	shared_ptr<Player> p = make_shared<Player>(Player(socketIndex));
	players.push_back(p);
	socketPlayerMap.insert(mapPair(socketIndex, playerIndex));

	addInRoom(playerIndex);

	++playerIndex;

}

/*
玩家断开连接
*/
void House::disconnectPlayer(int socketIndex) {
	mapIterator it = socketPlayerMap.find(socketIndex);
	if (it != socketPlayerMap.end()) {
		players.at(it->second)->disconnect();
	}
}


void House::addInRoom(int playerIndex) {
	int count = 0;
	while (!rooms[roomIndex]->addPlayer(players[playerIndex], playerIndex)) {//room初始化失败
		roomIndex = (roomIndex + 1) % ROOM_NUM;
		if (++count >= ROOM_NUM) {
			cout << "No empty room in house!!" << endl;
			return;
		}
	}
	cout << "玩家" << playerIndex << "成功加入" << roomIndex << "房间" << endl;
	//初始化成功，更新playerRoomMap
	roomPlayerMap.insert(mapPair(roomIndex, playerIndex));
	if (rooms[roomIndex]->getPlayerNum() >= 2) {
		roomIndex = (roomIndex + 1) % ROOM_NUM;
	}
}

void House::handleRecieveData(int socketIndex, uint16_t flag, uint8_t *data, uint16_t length) {
	//通过socketIndex 找到对应的palyerIndex
	//mapIterator it = find_if(playerSocketMap.begin(), playerSocketMap.end(), map_value_finder(socketIndex));
	mapIterator it = socketPlayerMap.find(socketIndex);
	if (it == socketPlayerMap.end()) {//如果没有找到则返回
		cout << "不能通过socket找到玩家" << endl;
		return;
	}
	//找到的map第一个key为palyerIndex，value为socketIndex
	Player *player = players.at(it->first).get();
	int rIndex = player->getRoomIndex();
	switch (flag) {
	case FLAG_PLAY:
	{
		B_POINT p = *((B_POINT*)data);
		cout << "横坐标:" << p.row << "竖坐标：" << p.col << endl;
	}break;
	case FLAG_ASK_REGRET:
	{

	}break;
	case FLAG_RETURN_REGRET:
	{

	}break;
	}
}

//执行一帧
void House::run() {
	uint32_t curTicks = SDL_GetTicks();
	uint32_t dt = curTicks - lastTicks;
	if (dt < 50) {//距离上次时间不足50ms，不更新
		return;
	}
	//服务器以每秒20帧的速率更新
	frame(dt);
}

//逻辑
void House::frame(uint32_t dt) {
	for (int i = 0; i < rooms.size(); ++i) {
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
	for (int i = 0; i < ROOM_NUM; ++i) {
		shared_ptr<Room> r = make_shared<Room>(Room());
		rooms.push_back(r);
	}
}

void House::initPlayers() {
	players.reserve(PLAYER_NUM);
}