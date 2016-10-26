#include "Player.h"


Player::Player(const string &name, TCPsocket socket) :name(name), socket(socket), connected(false), regret(false) {
	record.reserve(150);
}

Player::~Player() {

}

void Player::addStep(const B_POINT &p) {
	record.push_back(p);
}