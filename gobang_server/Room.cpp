#include "Room.h"

Room::Room() :p1(nullptr), p2(nullptr), currentPlayer(N), lastTime(0) {

}

Room::~Room() {
	delete p1; p1 = nullptr;
	delete p2; p2 = nullptr;
}

void Room::initP1(string name, TCPsocket socket) {
	p1 = new Player(name, socket);
}
void Room::initP2(string name, TCPsocket socket) {
	p2 = new Player(name, socket);
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