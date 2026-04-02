#pragma once
#include "Monster.h"
#include <string>
class Orc :public Monster {
public:
	Orc(std::string name, int health, int attack, std::unique_ptr<AttackStrategy> AttackStrategy) :Monster(name, health, attack, std::move(AttackStrategy)) {};

	virtual std::string getName() override;


	virtual int getHealth() override;


	virtual int getAttack() override;


	virtual void takeDamage(int damage) override;

	virtual int Attack(int armor) override;

	virtual void SetStrategy(std::unique_ptr<AttackStrategy> attackStrategy) override;
};