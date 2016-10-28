#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(0), p2Index(0),
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


//执行游戏逻辑
void Room::frame(uint32_t dt, const SEND_FUN &send) {
	switch (gameState) {
	case WAIT:
	{
		waitState(send);
	}
	break;
	case START:
	{

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

	}
	break;
	}
}

/*
处理wait 的逻辑
*/
void Room::waitState(const SEND_FUN &send) {
	if (playerNum >= 2) {
		gameState = START;
	}
}

/*
处理Run 的逻辑
*/
void Room::runState(const SEND_FUN &send) {

}