#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1),
	currentPlayer(N), lastTime(0), playerNum(0),
	gameState(WAIT), lastTicks(0) {

}

Room::~Room() {}

void Room::initP1(const shared_ptr<Player> &player, int index) {
	p1 = player;
	p1Index = index;
}
void Room::initP2(const shared_ptr<Player> &player, int index) {
	p2 = player;
	p2Index = index;
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
	initRoom();
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
����wait ���߼�
*/
void Room::waitState(const SEND_FUN &send) {
	if (playerNum >= 2) {
		gameState = START;
		return;
	}
	FlagType flag = FLAG_WAIT;
	LengthType length = 0;
	DataType data = nullptr;
	if (p1 != nullptr && !p1->isDisconnected()) {
		send(p1Index, data, length, flag);
	}
	if (p2 != nullptr && !p2->isDisconnected()) {
		send(p2Index, data, length, flag);
	}
}

/*
����start ���߼�
*/
void Room::startState(const SEND_FUN &send) {
	FlagType flag = FLAG_START;

	if (p1 != nullptr && !p1->isDisconnected()) {
		send(p1Index, nullptr, 0, flag);
	}
	if (p2 != nullptr && !p2->isDisconnected()) {
		send(p2Index, nullptr, 0, flag);
	}
}

/*
����Run ���߼�
*/
void Room::runState(const SEND_FUN &send) {

}
