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
	p1->setColor(B);
}
void Room::initP2(const shared_ptr<Player> &player, int index) {
	p2 = player;
	p2Index = index;
	p2->setColor(W);
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
		//cout << "有玩家断开连接" << endl;

	}
	break;
	}
}

/*
检查有无掉线玩家
*/
void Room::checkDisconnect() {
	if ((p1 != nullptr && p1->isDisconnected()) || (p2 != nullptr && p2->isDisconnected())) {
		gameState = END;
	}
}

/*
处理wait 的逻辑
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
处理start 的逻辑
*/
void Room::startState(const SEND_FUN &send) {
	FlagType flag = FLAG_START;

	CHESS_COLOR color = p1->getColor();//发送客户端的颜色
	LengthType length = sizeof(color);
	send(p1Index, (DataType)&color, length, flag);

	color = p2->getColor();
	length = sizeof(color);
	send(p2Index, (DataType)&color, length, flag);
}

/*
处理Run 的逻辑
*/
void Room::runState(const SEND_FUN &send) {

}
