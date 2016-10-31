#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1), roomIndex(-1),
	currentPlayer(N), lastTime(0), playerNum(0),
	gameState(WAIT), lastPlayerMessageTicks(0), lastGameMessageTicks(0),
	winner(65535)
{
	initRoom();
}

Room::~Room() {}

/*
初始化玩家1 和 玩家2
*/
void Room::initP1(const shared_ptr<Player> &player, uint16_t index) {
	p1 = player;
	p1Index = index;
	p1->setColor(B);
	p1->setName("玩家1");
	p1->setRoomIndex(roomIndex);
}
void Room::initP2(const shared_ptr<Player> &player, uint16_t index) {
	p2 = player;
	p2Index = index;
	p2->setColor(W);
	p2->setName("玩家2");
	p2->setRoomIndex(roomIndex);
}

/*
初始化玩家1,2
*/
bool Room::addPlayer(const shared_ptr<Player> &player, uint16_t index) {
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

/*
初始化棋盘
*/
void Room::initBoard() {
	fillMatrix(chessBoard, N);
}

/*
初始化棋局相关属性
*/
void Room::initAttribute(CHESS_COLOR curSide,uint16_t time) {
	currentPlayer = curSide;
	lastTime = time;
	gameState = WAIT;
	playerNum = 0;
	p1Index = -1;
	p2Index = -1;
	lastPlayerMessageTicks = lastGameMessageTicks = SDL_GetTicks();
}

/*
初始化房间
*/
void Room::initRoom() {
	initBoard();
	initAttribute(-1,PLAYTIME);
}

/*
释放玩家
*/
void Room::releasePlayer() {
	p1.reset();
	p2.reset();
}

/*
清空房间
*/
void Room::releaseRoom() {
	initBoard();
	initAttribute(-1, PLAYTIME);
	releasePlayer();
}

//执行游戏逻辑
void Room::frame(uint32_t dt, const SEND_FUN &send) {
	checkDisconnect();
	switch (gameState) {
	case WAIT:
		waitState();
		break;
	case START:
		startState();
		break;
	case RUN:
		runState();
		break;
	case REGRET:
	{

	}
	break;
	case END:
		restartInit();
		break;
	}
	//发送消息
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
重新开始  修改游戏状态为start，重新初始化棋盘，清空玩家棋子记录，交换玩家的颜色，设置黑棋方为先走。
*/
void Room::restartInit() {
	if (p1->getPrepared() && p2->getPrepared()) {
		gameState = RUN;
		initBoard();
		p1->clear();
		p2->clear();
		winner = 65535;
		auto p1Color = p1->getColor();
		auto p2Color = p2->getColor();
		p1->setColor(p2Color);
		p2->setColor(p1Color);
		if (p1Color == W) {
			currentPlayer = p1Index;
		} else {
			currentPlayer = p2Index;
		}
		
	}
}

/*
获得GameMessage
*/
Game_Message Room::getGameMessage() {
	Game_Message message;
	message.gameState = gameState;
	message.curSide = currentPlayer;
	message.p1Index = p1Index;
	message.p2Index = p2Index;
	message.playerNum = playerNum;
	message.time = lastTime;
	message.winner = winner;
	return message;
}

/*
获得PlayerMessage
*/
Player_Message Room::getPlayerMessage(uint16_t pi) {
	Player_Message message;
	memset(&message, 0, sizeof(message));
	auto p = getPlayer(pi);
	if (p == nullptr) {
		return message;
	}
	message.color = p->getColor();
	message.connected = (uint16_t)p->getConnected();
	message.disconnected = (uint16_t)p->isDisconnected();
	memcpy(message.name, p->getName().c_str(), 16);
	message.regret = (uint16_t)p->getRegret();
	message.roomIndx = p->getRoomIndex();
	message.playerIndex = pi;
	message.prepared = (uint16_t)p->getPrepared();
	return message;
}

/*
处理wait 的逻辑
*/
void Room::waitState() {
	if (playerNum >= 2) {
		gameState = START;
		cout << "当前人数2人，进入开始状态" << endl;
		return;
	}
}

/*
处理start 的逻辑
*/
void Room::startState() {
	if (p1->getPrepared() && p2->getPrepared()) {//游戏开始，初始化游戏相关属性
		cout << "双方已经准备完毕，游戏即将开始" << endl;
		p1->setPrepared(false);
		p2->setPrepared(false);
		gameState = RUN;
		currentPlayer = p1Index;
		lastTime = PLAYTIME;
	}
}

/*
处理Run 的逻辑
*/
void Room::runState() {
	CHESS_COLOR winColor = referee.checkBoard(chessBoard);
	if (winColor == N) {
		return;
	}
	if (p1->getColor() == winColor) {//玩家1胜利
		winner = p1Index;
	} else if (p2->getColor() == winColor) {//玩家2胜利
		winner = p2Index;
	}
	gameState = END;

}

/*
换边
*/
void Room::changeSide() {
	if (currentPlayer == p1Index) {
		currentPlayer = p2Index;
	} else {
		currentPlayer = p1Index;
	}
}

/*
发送消息函数
*/
void Room::sendMessage(const SEND_FUN &send) {
	bool sendP = false, sendG = false;
	//计算时间戳    游戏信息 发送频率较高，玩家信息发送频率较低
	uint32_t curTicks = SDL_GetTicks();
	if (curTicks - lastPlayerMessageTicks > 50) {
		sendP = true;
		lastPlayerMessageTicks = curTicks;
	}
	if (curTicks - lastGameMessageTicks > 25) {
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
Player* Room::getPlayer(uint16_t pi) {
	Player *p = nullptr;
	if (pi == p1Index)
		p = p1.get();
	else if (pi == p2Index)
		p = p2.get();
	else
		return nullptr;
	return p;
}

Player* Room::getAnotherPlayer(uint16_t pi) {
	Player *p = nullptr;
	if (pi == p1Index)
		p = p2.get();
	else if (pi == p2Index)
		p = p1.get();
	else
		return nullptr;
	return p;
}


/*
走一步棋
*/
void Room::playOneStep(uint16_t playerIndex, B_POINT point) {
	auto player = getPlayer(playerIndex);
	auto color = player->getColor();
	chessBoard[point.row][point.col] = color;
	if (player == nullptr) return;
	player->addStep(point);
}