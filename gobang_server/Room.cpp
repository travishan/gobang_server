#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1),
	currentPlayer(N), lastTime(0), playerNum(0),
	gameState(WAIT), lastTicks(0) {
	initRoom();
}

Room::~Room() {}

void Room::initP1(const shared_ptr<Player> &player, int index) {
	p1 = player;
	p1Index = index;
	p1->setColor(B);
	p1->setName("���1");
}
void Room::initP2(const shared_ptr<Player> &player, int index) {
	p2 = player;
	p2Index = index;
	p2->setColor(W);
	p2->setName("���2");
}

bool Room::addPlayer(const shared_ptr<Player> &player, int index) {
	if (playerNum == 0) {
		initP1(player, index);
	} else if (playerNum == 1) {
		initP2(player, index);
	} else {
		return false;
	}
	++playerNum;
	return true;
}

void Room::initBoard() {
	fillMatrix(chessBoard, N);
}

void Room::initAttribute() {
	currentPlayer = N;
	lastTime = PLAYTIME;
}

void Room::initRoom() {
	initBoard();
	initAttribute();
}


//ִ����Ϸ�߼�
void Room::frame(uint32_t dt, const SEND_FUN &send) {
	checkDisconnect();
	switch (gameState) {
	case WAIT:
	{
		waitState(send);
	}
	break;
	case START:
	{
		startState(send);
	}
	break;
	case RUN:
	{

	}
	break;
	case REGRET:
	{

	}
	break;
	case END:
	{
		//cout << "����ҶϿ�����" << endl;

	}
	break;
	}
}

/*
������޵������
*/
void Room::checkDisconnect() {
	if ((p1 != nullptr && p1->isDisconnected()) || (p2 != nullptr && p2->isDisconnected())) {
		gameState = END;
	}
}

/*
���waitMessage
*/
WaitMessageStruct Room::getWaitMessage(int pi) {
	WaitMessageStruct message;
	memset(&message, 0, sizeof(message));
	Player *p = nullptr;
	if (pi == p1Index) 
		p = p1.get();
	else
		p = p2.get();
	if (p == nullptr) {
		return message;
	}
	message.color = (uint16_t)p->getColor();
	message.connected = (uint16_t)p->getConnected();
	message.disconnected = (uint16_t)p->isDisconnected();
	memcpy(message.name, p->getName().c_str(), 16);
	message.regret = (uint16_t)p->getRegret();
	message.roomIndx = (uint16_t)p->getRoomIndex();
	message.playerIndex = (uint16_t)pi;
	message.prepared = (uint16_t)p->getPrepared();
	return message;
}

/*
����wait ���߼�
*/
void Room::waitState(const SEND_FUN &send) {
	if (playerNum >= 2) {
		gameState = START;
		cout << "��ǰ����2�ˣ����뿪ʼ״̬" << endl;
		return;
	}
	FlagType flag = FLAG_WAIT;
	sendPlayerMessage(send, flag);
}

/*
����start ���߼�
*/
void Room::startState(const SEND_FUN &send) {
	FlagType flag = FLAG_START;

	sendPlayerMessage(send, flag);
}

/*
����Run ���߼�
*/
void Room::runState(const SEND_FUN &send) {

}



/*
������Ϣ����
*/
void Room::sendPlayerMessage(const SEND_FUN &send, FlagType flag) {
	WaitMessageStruct messageP1, messageP2;
	messageP1 = getWaitMessage(p1Index);
	messageP2 = getWaitMessage(p2Index);

	if (p1 != nullptr && !p1->isDisconnected()) {
		messageP2.yourIndex = messageP1.yourIndex = p1Index;
		send(p1Index, (DataType)&messageP1, sizeof(messageP1), flag);
		send(p1Index, (DataType)&messageP2, sizeof(messageP2), flag);
	}
	if (p2 != nullptr && !p2->isDisconnected()) {
		messageP2.yourIndex = messageP1.yourIndex = p2Index;
		send(p2Index, (DataType)&messageP1, sizeof(messageP1), flag);
		send(p2Index, (DataType)&messageP2, sizeof(messageP2), flag);
	}
}