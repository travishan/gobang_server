#include "Player.h"

Player::Player() :Player(0) {

}

Player::Player(int socket) :name(""), socketIndex(socket), connected(true), disconnected(false), regret(false), roomIndex(0){
	record.reserve(150);
}

Player::~Player() {

}

void Player::addStep(const B_POINT &p) {
	record.push_back(p);
}