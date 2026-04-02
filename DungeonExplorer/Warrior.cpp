//Warrior.cpp

#include "Character.h"
#include "Job.h"
#include "Warrior.h"
#include <iostream>
using namespace std;

FStat Warrior::GetBaseStat() const {
	//MaxHP, HP, Attack, Defense
	return { 200, 200, 30, 5 };
}

FStat Warrior::GetLevelUpBonus() const {
	//MaxHP, HP, Attack, Defense
	return { 30, 30, 10, 5 };
}

int Warrior::SkillDamage(const Character& character) const {
	
	int SkillAttack = 30 + character.GetLevel() * 10;
	
	return SkillAttack;
}

std::string Warrior::SkillName() const {
	return "Repeating Slash !";
}

std::string Warrior::JobName() const {
	return "Warrior";
}