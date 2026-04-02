#include "Slime.h"
#include <iostream>
#include "AttackStrategy.h"
std::string Slime::getName() {
	return name;
}

int Slime::getHealth() {
	return health;
}

int Slime::getAttack() {
	return attack;
}

void Slime::takeDamage(int damage) {
	int getDamage = health - damage;
	if (getDamage <= 0) health = 0;
	else health = getDamage;
}

int Slime::Attack(int armor) {
	if (!attackStrategy) return 0;
	int dmg = attackStrategy->calculateDamage(attack,armor);

	return dmg;
}

void Slime::SetStrategy(std::unique_ptr<AttackStrategy> attackStrategy) {
	this->attackStrategy = move(attackStrategy);
}