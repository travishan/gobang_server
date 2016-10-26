#include "Player.h"

Player::Player() :Player("") {

}

Player::Player(const string &name) :name(name), connected(false), regret(false) {
	record.reserve(150);
}

Player::~Player() {

}

void Player::addStep(const B_POINT &p) {
	record.push_back(p);
}