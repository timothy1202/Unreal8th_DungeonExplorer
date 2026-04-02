#include "Boss.h"
#include <iostream>
#include "AttackStrategy.h"
std::string Boss::getName() {
	return name;
}

int Boss::getHealth() {
	return health;
}

int Boss::getAttack() {
	return attack;
}

void Boss::takeDamage(int damage) {
	int getDamage = health - damage;
	if (getDamage <= 0) health = 0;
	else health = getDamage;
}

int Boss::Attack(int armor) {
	if (!attackStrategy) return 0;
	int dmg = attackStrategy->calculateDamage(attack,armor);
	std::cout << dmg << std::endl;
	return dmg;
}

void Boss::SetStrategy(std::unique_ptr<AttackStrategy> attackStrategy) {
	this->attackStrategy = move(attackStrategy);
}