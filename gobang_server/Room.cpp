#include "Room.h"

Room::Room() :p1(nullptr), p2(nullptr), currentPlayer(N), lastTime(0) {

}

Room::~Room() {
}

void Room::initP1(const shared_ptr<Player> &player) {
	p1 = player;
}
void Room::initP2(const shared_ptr<Player> &player) {
	p2 = player;
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