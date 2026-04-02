#include "Goblin.h"
#include <iostream>
#include "AttackStrategy.h"
std::string Goblin::getName() {
	return name;
}

int Goblin::getHealth() {
	return health;
}

int Goblin::getAttack() {
	return attack;
}

void Goblin::takeDamage(int damage) {
	int getDamage = health - damage;
	if (getDamage <= 0) health = 0;
	else health = getDamage;
}

int Goblin::Attack(int armor) {
	if (!attackStrategy) return 0;
	int dmg = attackStrategy->calculateDamage(attack,armor);
	std::cout << dmg << std::endl;
	return dmg;
}

void Goblin::SetStrategy(std::unique_ptr<AttackStrategy> attackStrategy) {
	this->attackStrategy = move(attackStrategy);
}