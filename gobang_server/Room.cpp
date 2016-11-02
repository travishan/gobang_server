#include "Room.h"

Room::Room() :
	p1(nullptr), p2(nullptr), p1Index(-1), p2Index(-1), roomIndex(-1),
	currentPlayer(p1Index), lastTime(0), playerNum(0),
	gameState(WAIT), lastPlayerMessageTicks(0), lastGameMessageTicks(0),
	winner(65535) {
	initRoom();
}

Room::~Room() {}

/*
��ʼ�����1 �� ���2
*/
void Room::initP1(const shared_ptr<Player> &player, uint16_t index) {
	p1 = player;
	p1Index = index;
	p1->setColor(B);
	p1->setName("Tom");
	p1->setRoomIndex(roomIndex);
	currentPlayer = p1Index;
}
void Room::initP2(const shared_ptr<Player> &player, uint16_t index) {
	p2 = player;
	p2Index = index;
	p2->setColor(W);
	p2->setName("Jerry");
	p2->setRoomIndex(roomIndex);
}

/*
��ʼ�����1,2
*/
bool Room::addPlayer(const shared_ptr<Player> &player, uint16_t index) {
	if (p1 == nullptr) {
		initP1(player, index);
	} else if (p2 == nullptr) {
		initP2(player, index);
	} else {
		return false;
	}
	if(playerNum < 2)
		++playerNum;
	return true;
}

/*
��ʼ������
*/
void Room::initBoard() {
	fillMatrix(chessBoard, N);
	if(p1 != nullptr) p1->clear();
	if (p2 != nullptr) p2->clear();
}

/*
��ʼ������������
*/
void Room::initAttribute(CHESS_COLOR curSide, uint16_t time) {
	currentPlayer = curSide;
	lastTime = time;
	gameState = WAIT;
	playerNum = 0;
	p1Index = -1;
	p2Index = -1;
	lastPlayerMessageTicks = lastGameMessageTicks = SDL_GetTicks();
}

/*
����뿪
*/
void Room::playerLeave(int index){
	if (playerNum > 0) {
		--playerNum;
		if (p1Index == index) {
			p1.reset();
		} else if (p2Index == index) {
			p2.reset();
		}
	}
}

/*
��ʼ������
*/
void Room::initRoom() {
	initBoard();
	initAttribute(-1, PLAYTIME);
}

/*
�ͷ����
*/
void Room::releasePlayer() {
	p1.reset();
	p2.reset();
}

/*
��շ���
*/
void Room::releaseRoom() {
	initBoard();
	initAttribute(-1, PLAYTIME);
	releasePlayer();
}

/*
����˫������ɫ
*/
void Room::exchangeColor() {
	auto p1Color = p1->getColor();
	auto p2Color = p2->getColor();
	p1->setColor(p2Color);
	p2->setColor(p1Color);
	if (p1Color == W) {
		currentPlayer = p1Index;
	} else {
		currentPlayer = p2Index;
	}

	winner = 65535;
}

/*
���¿�ʼ  �޸���Ϸ״̬Ϊstart�����³�ʼ�����̣����������Ӽ�¼��������ҵ���ɫ�����ú��巽Ϊ���ߡ�
*/
void Room::restartInit() {
	if (p1 != nullptr && p1->getPrepared() &&  p2 != nullptr && p2->getPrepared()) {
		gameState = RUN;
		initBoard();
		exchangeColor();
	}
}

//ִ����Ϸ�߼�
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
		//restartInit();
		if (p1 != nullptr && p1->getPrepared() && p2 != nullptr &&p2->getPrepared()) {
			cout << "Both players are ready to start agagin." << endl;
			exchangeColor();
			//restartInit();
			gameState = START;
		}
			
		break;
	}
	//������Ϣ
	sendMessage(send);

}

/*
������޵������
*/
bool Room::checkDisconnect() {
	if ((p1 != nullptr && p1->isDisconnected()) || (p2 != nullptr && p2->isDisconnected())) {
		gameState = WAIT;
		return false;
	}
	return true;
}

/*
���GameMessage
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
���PlayerMessage
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
����wait ���߼�
*/
void Room::waitState() {
	if (playerNum >= 2) {
		gameState = START;
		cout << "There's two peoples in room " << roomIndex << " and the game will begin." << endl;
		return;
	}
}

/*
����start ���߼�
*/
void Room::startState() {
	if (!checkDisconnect())
		return;
	if (p1->getPrepared() && p2->getPrepared()) {//��Ϸ��ʼ����ʼ����Ϸ�������
		cout << "Both players are prepared, game is going to start." << endl;
		initBoard();
		p1->setPrepared(false);
		p2->setPrepared(false);
		gameState = RUN;
		//currentPlayer = p1Index;
		lastTime = PLAYTIME;
	}
}

/*
����Run ���߼�
*/
void Room::runState() {
	CHESS_COLOR winColor = referee.checkBoard(chessBoard);
	if (winColor == N) {
		return;
	}
	if (p1->getColor() == winColor) {//���1ʤ��
		winner = p1Index;
	} else if (p2->getColor() == winColor) {//���2ʤ��
		winner = p2Index;
	}
	gameState = END;
}

/*
����
*/
void Room::changeSide() {
	if (currentPlayer == p1Index) {
		currentPlayer = p2Index;
	} else {
		currentPlayer = p1Index;
	}
}

/*
������Ϣ����
*/
void Room::sendMessage(const SEND_FUN &send) {
	bool sendP = false, sendG = false;
	//����ʱ���    ��Ϸ��Ϣ ����Ƶ�ʽϸߣ������Ϣ����Ƶ�ʽϵ�
	uint32_t curTicks = SDL_GetTicks();
	if (curTicks - lastPlayerMessageTicks > 50) {
		sendP = true;
		lastPlayerMessageTicks = curTicks;
	}
	if (curTicks - lastGameMessageTicks > 25) {
		sendG = true;
		lastGameMessageTicks = curTicks;
	}
	if (sendG) {//������Ϸ��Ϣ
		//��Ϸ��Ϣ��ȡ
		Game_Message message = getGameMessage();
		if (p1 != nullptr && !p1->isDisconnected()) {
			send(p1Index, (DataType)&message, sizeof(message), FLAG_GAME_INFO);
		}
		if (p2 != nullptr && !p2->isDisconnected()) {
			send(p2Index, (DataType)&message, sizeof(message), FLAG_GAME_INFO);
		}
	}
	if (sendP) {//���������Ϣ
		//�����Ϣ��ȡ
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



/*��ȡ���
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
��һ����
*/
void Room::playOneStep(uint16_t playerIndex, B_POINT point) {
	auto player = getPlayer(playerIndex);
	auto color = player->getColor();
	chessBoard[point.row][point.col] = color;
	if (player == nullptr) return;
	player->addStep(point);
}