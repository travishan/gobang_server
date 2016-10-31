#include "Player.h"

Player::Player() :Player(0) {

}

Player::Player(uint16_t socket) :name(""), socketIndex(socket), connected(true), disconnected(false), regret(false), roomIndex(0), prepared(false){
	record.reserve(150);
}

Player::~Player() {

}

void Player::addStep(const B_POINT &p) {
	record.push_back(p);
}