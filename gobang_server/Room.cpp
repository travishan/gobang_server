#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1),
	currentPlayer(N), lastTime(0), playerNum(0),
	gameState(WAIT), lastPlayerMessageTicks(0), lastGameMessageTicks(0)
{
	initRoom();

	lastPlayerMessageTicks = lastGameMessageTicks = SDL_GetTicks();
}

Room::~Room() {}

void Room::initP1(const shared_ptr<Player> &player, int index) {
	p1 = player;
	p1Index = index;
	p1->setColor(B);
	p1->setName("玩家1");
}
void Room::initP2(const shared_ptr<Player> &player, int index) {
	p2 = player;
	p2Index = index;
	p2->setColor(W);
	p2->setName("玩家2");
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
	sendMessage(send);
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
获得GameMessage
*/
Game_Message Room::getGameMessage() {
	Game_Message message;
	message.gameState = (uint16_t)gameState;
	message.curSide = (uint16_t)currentPlayer;
	message.p1Index = (uint16_t)p1Index;
	message.p2Index = (uint16_t)p2Index;
	message.playerNum = (uint16_t)playerNum;
	message.time = (uint16_t)lastTime;
	return message;
}

/*
获得PlayerMessage
*/
Player_Message Room::getPlayerMessage(int pi) {
	Player_Message message;
	memset(&message, 0, sizeof(message));
	auto p = getPlayer(pi);
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
处理wait 的逻辑
*/
void Room::waitState(const SEND_FUN &send) {
	if (playerNum >= 2) {
		gameState = START;
		cout << "当前人数2人，进入开始状态" << endl;
		return;
	}
}

/*
处理start 的逻辑
*/
void Room::startState(const SEND_FUN &send) {

}

/*
处理Run 的逻辑
*/
void Room::runState(const SEND_FUN &send) {

}



/*
发送消息函数
*/
void Room::sendMessage(const SEND_FUN &send) {
	bool sendP = false, sendG = false;
	//计算时间戳    游戏信息 发送频率较高，玩家信息发送频率较低
	uint32_t curTicks = SDL_GetTicks();
	if (curTicks - lastPlayerMessageTicks > 1000) {
		sendP = true;
		lastPlayerMessageTicks = curTicks;
	}
	if (curTicks - lastGameMessageTicks > 100) {
		sendG = true;
		lastGameMessageTicks = curTicks;
	}
	if (sendG) {//发送游戏信息
		//游戏信息获取
		Game_Message message = getGameMessage();
		if (p1 != nullptr && !p1->isDisconnected()) {
			send(p1Index, (DataType)&message, sizeof(message), FLAG_GAME_INFO);
		}
		if (p2 != nullptr && !p2->isDisconnected()) {
			send(p2Index, (DataType)&message, sizeof(message), FLAG_GAME_INFO);
		}
	}
	if (sendP) {//发送玩家信息
		//玩家信息获取
		Player_Message messageP1, messageP2;
		messageP1 = getPlayerMessage(p1Index);
		messageP2 = getPlayerMessage(p2Index);
		if (p1 != nullptr && !p1->isDisconnected()) {
			messageP2.yourIndex = messageP1.yourIndex = p1Index;
			send(p1Index, (DataType)&messageP1, sizeof(messageP1), FLAG_PLAYER_INFO);
			send(p1Index, (DataType)&messageP2, sizeof(messageP2), FLAG_PLAYER_INFO);
		}
		if (p2 != nullptr && !p2->isDisconnected()) {
			messageP2.yourIndex = messageP1.yourIndex = p2Index;
			send(p2Index, (DataType)&messageP1, sizeof(messageP1), FLAG_PLAYER_INFO);
			send(p2Index, (DataType)&messageP2, sizeof(messageP2), FLAG_PLAYER_INFO);
		}
	}
}



/*获取玩家
*/
Player* Room::getPlayer(int pi) {
	Player *p = nullptr;
	if (pi == p1Index)
		p = p1.get();
	else
		p = p2.get();
	return p;
}