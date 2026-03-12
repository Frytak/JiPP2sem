#include "./Player.hpp"
#include <algorithm>
#include <iostream>
#include <string>

Player::Player(std::string name, int maxHp) : name(name), hp(std::max(maxHp, 1)), maxHp(std::max(maxHp, 1)), level(0) {};

int Player::takeDamage(int amount) {
    int initial_hp = this->hp;
    amount = std::max(amount, 0);
    this->hp = std::max(this->hp - amount, 0);

    return initial_hp - this->hp;
}

int Player::heal(int amount) {
    int initial_hp = this->hp;
    amount = std::max(amount, 0);
    this->hp = std::min(this->hp + amount, this->maxHp);

    return this->hp - initial_hp;
}

int Player::levelUp(int amount) {
    int initial_lvl = this->level;
    this->level += std::max(amount, 0);

    return this->level - initial_lvl;
}

void Player::printStatus() const {
    std::cout << "Player { name: \"" << this->name << "\", hp: " << this->hp << ", maxHp: " << this->maxHp << ", level: " << this->level << " }" << std::endl;
}
