//Wizard.cpp

#include "Character.h"
#include "Job.h"
#include "Wizard.h"
#include <iostream>
using namespace std;

FStat Wizard::GetBaseStat() const {
	//MaxHP, HP, Attack
	return { 100, 100, 50, 3 };
}

FStat Wizard::GetLevelUpBonus() const {
	//MaxHP, HP, Attack
	return { 15, 15, 23, 3 };
}

int Wizard::SkillDamage(const Character& character) const {

	int SkillAttack = 60 + character.GetLevel() * 30;

	return SkillAttack;
}

std::string Wizard::SkillName() const {
	return "Fireball !";
}

std::string Wizard::JobName() const {
	return "Wizard";
}
