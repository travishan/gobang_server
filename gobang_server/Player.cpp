#include "Player.h"

Player::Player() :Player("") {

}

Player::Player(const string &name) :name(name), socketIndex(0), connected(false), regret(false), roomIndex(0){
	record.reserve(150);
}

Player::~Player() {

}

void Player::addStep(const B_POINT &p) {
	record.push_back(p);
}