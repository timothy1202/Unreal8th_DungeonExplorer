#include "Troll.h"
#include <iostream>
#include "AttackStrategy.h"
std::string Troll::getName() {
	return name;
}

int Troll::getHealth() {
	return health;
}

int Troll::getAttack() {
	return attack;
}

void Troll::takeDamage(int damage) {
	int getDamage = health - damage;
	if (getDamage <= 0) health = 0;
	else health = getDamage;
}

int Troll::Attack(int armor) {
	if (!attackStrategy) return 0;
	int dmg = attackStrategy->calculateDamage(attack,armor);

	return dmg;
}

void Troll::SetStrategy(std::unique_ptr<AttackStrategy> attackStrategy) {
	this->attackStrategy = move(attackStrategy);
}