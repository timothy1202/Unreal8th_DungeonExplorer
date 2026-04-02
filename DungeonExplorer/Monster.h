#pragma once
#include <string>
#include "AttackStrategy.h"
#include <memory>
class Monster {
protected:
	std::string name;
	int health;
	int attack;
	std::unique_ptr<AttackStrategy> attackStrategy;

public:
	Monster(std::string name, int health, int attack, std::unique_ptr<AttackStrategy> attackStrategy) :name(name), health(health), attack(attack), attackStrategy(std::move(attackStrategy)) {};
	virtual std::string getName() = 0;
	virtual int getHealth() = 0;
	virtual int getAttack() = 0;
	virtual void takeDamage(int damage) = 0;
	virtual int Attack(int armor) = 0;
	virtual void SetStrategy(std::unique_ptr<AttackStrategy> attackStrategy) = 0;
	virtual ~Monster() = default;
};