#include "Orc.h"
#include <iostream>
#include "AttackStrategy.h"
std::string Orc::getName() {
	return name;
}

int Orc::getHealth() {
	return health;
}

int Orc::getAttack() {
	return attack;
}

void Orc::takeDamage(int damage) {
	int getDamage = health - damage;
	if (getDamage <= 0) health = 0;
	else health = getDamage;
}

int Orc::Attack(int armor) {
	if (!attackStrategy) return 0;
	int dmg = attackStrategy->calculateDamage(attack,armor);

	return dmg;
}

void Orc::SetStrategy(std::unique_ptr<AttackStrategy> attackStrategy) {
	this->attackStrategy = move(attackStrategy);
}