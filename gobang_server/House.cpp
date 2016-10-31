#include "House.h"



House::House() :roomIndex(0), playerIndex(0) {
	initRooms();
}

House::~House() {

}

/*
���������
*/
void House::addPlayer(uint16_t socketIndex) {
	shared_ptr<Player> p = make_shared<Player>(Player(socketIndex));
	players.push_back(p);
	socketPlayerMap.insert(mapPair(socketIndex, playerIndex));

	addInRoom(playerIndex);

	++playerIndex;

}

/*
��ҶϿ�����
*/
void House::disconnectPlayer(uint16_t socketIndex) {
	mapIterator it = socketPlayerMap.find(socketIndex);
	if (it != socketPlayerMap.end()) {
		players.at(it->second)->disconnect();
	}
}


void House::addInRoom(uint16_t playerIndex) {
	uint16_t count = 0;
	while (!rooms[roomIndex]->addPlayer(players[playerIndex], playerIndex)) {//room��ʼ��ʧ��
		roomIndex = (roomIndex + 1) % ROOM_NUM;
		if (++count >= ROOM_NUM) {
			cout << "No empty room in house!!" << endl;
			return;
		}
	}
	cout << "���" << playerIndex << "�ɹ�����" << roomIndex << "����" << endl;
	//��ʼ���ɹ�������playerRoomMap
	roomPlayerMap.insert(mapPair(roomIndex, playerIndex));
	if (rooms[roomIndex]->getPlayerNum() >= 2) {
		roomIndex = (roomIndex + 1) % ROOM_NUM;
	}
}

void House::handleRecieveData(uint16_t socketIndex, uint16_t flag, uint8_t *data, uint16_t length) {
	//ͨ��socketIndex �ҵ���Ӧ��palyerIndex
	//mapIterator it = find_if(playerSocketMap.begin(), playerSocketMap.end(), map_value_finder(socketIndex));
	mapIterator it = socketPlayerMap.find(socketIndex);
	if (it == socketPlayerMap.end()) {//���û���ҵ��򷵻�
		cerr << "����ͨ��socket�ҵ����" << endl;
		return;
	}
	//�ҵ���map��һ��keyΪsocketIndex��valueΪpalyerIndex
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
		cout << "���" << playerIndex << "׼������" << endl;
	}break;
	}
}

/*
����ͬFlag����Ϣ 
�ǵ�delete data��
�ǵ�delete data��
�ǵ�delete data��
*/
void House::handlePlay(uint16_t pIndex, Player *plyr, Room *room, DataType data, LengthType length) {
	B_POINT p;
	memcpy(&p, data, length);
	cout << "������:" << p.row << "�����꣺" << p.col << endl;
	room->playOneStep(pIndex, p);
	cout << "Room :" << room->getRoomIndex() << endl;
	auto plyr2 = room->getAnotherPlayer(pIndex);
	if (plyr2 == nullptr) return;
	sendFun(plyr2->getSocketIndex(), data, length, FLAG_PLAY_INFO);//���͸�����һ��
	room->changeSide();
	delete data;
}


//ִ��һ֡
void House::run() {
	uint32_t curTicks = SDL_GetTicks();
	uint32_t dt = curTicks - lastTicks;
	if (dt < 1000) {//�����ϴ�ʱ�䲻��100ms��������
		return;
	}
	//��������ÿ��10֡�����ʸ���
	frame(dt);
	lastTicks = curTicks;
}

//�߼�
void House::frame(uint32_t dt) {
	for (size_t i = 0; i < rooms.size(); ++i) {
		Room *room = rooms[i].get();
		room->frame(dt,sendFun);
	}
}

//���ÿɵ��ú�������sendFun
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