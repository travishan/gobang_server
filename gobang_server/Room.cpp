#include "Room.h"

Room::Room() :p1(nullptr), p2(nullptr), currentPlayer(N), lastTime(0), playerNum(0){

}

Room::~Room() {
}

void Room::initP1(const shared_ptr<Player> &player) {
	p1 = player;
}
void Room::initP2(const shared_ptr<Player> &player) {
	p2 = player;
}

bool Room::addPlayer(const shared_ptr<Player> &player) { 
	if (playerNum == 0) {
		initP1(player);
	} else if (playerNum == 1) {
		initP2(player);
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




void Room::runFrame() {

}