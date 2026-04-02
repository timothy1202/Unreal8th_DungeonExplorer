//Character.cpp

#include "Character.h"
#include "Job.h"
#include "Warrior.h"
#include "LogSystem.h"
#include <iostream>
#include <iomanip>

//constructor
Character::Character(const std::string& name, const Job& job) : Name(name), CurrentJob(job.JobName()), Level(1), stat(job.GetBaseStat()), EXP(0), Gold(0) {}


//Singleton Pattern
Character* Character::Instance = nullptr;

//instance pointer return
Character* Character::GetInstance()
{
	return Instance;
}

//Used only on first creation
Character* Character::GetInstance(const std::string& name, const Job& job)
{
	if (Instance == nullptr)
	{
		Instance = new Character(name, job);
	}
	return Instance;
}


//singleton instance delete
void Character::DestroyInstance() {
	delete Instance;
	Instance = nullptr;
}

/*
//Status View
void Character::displayStatus() const {
	std::cout << std::left;

	std::cout << std::endl;
	std::cout << "====================" << std::endl;
	std::cout << "------[Status]------" << std::endl;
	std::cout << "====================" << std::endl;
	std::cout << std::setw(8) << "Name" << "| " << Name << std::endl;
	std::cout << std::setw(8) << "Job" << "| " << CurrentJob << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << std::setw(8) << "LV" << "| " << Level << std::endl;
	std::cout << std::setw(8) << "EXP" << "| " << EXP << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << std::setw(8) << "HP" << "| " << stat.HP << " / " << stat.MaxHP << std::endl;
	std::cout << std::setw(8) << "ATK" << "| " << stat.Attack << std::endl;
	std::cout << std::setw(8) << "DFS" << "| " << stat.Defense << std::endl;
	std::cout << "---------------------" << std::endl;
	std::cout << std::setw(8) << "Gold" << "| " << Gold << std::endl;
	std::cout << "=====================" << std::endl;
}
*/

//Level UP
void Character::LevelUP(const Job& job) {
	// if already at max level
	if (Level >= 10) {
		std::cout << "Can't LevelUp anymore...\n";
		return;
	}
	else if (EXP >= 100) {
		++Level;
		EXP = EXP - 100;

		stat.MaxHP += job.GetLevelUpBonus().MaxHP;
		stat.HP = stat.MaxHP;
		stat.Attack += job.GetLevelUpBonus().Attack;
		stat.Defense += job.GetLevelUpBonus().Defense;

		std::cout << "level Up!!\nCurrent Level: " << Level << "\n";
		std::cout << "restored your HP to full\n\n";
	}
	else {
		std::cout << "Not enough experience to level up.\n";
	}
}


//Getter
std::string Character::GetName() const { return Name; }
std::string Character::GetCurrentJob() const { return CurrentJob; }
int Character::GetLevel() const { return Level; }
int Character::GetMaxHP() const { return stat.MaxHP; }
//int Character::GetMaxMP() const { return MaxMP; }
int Character::GetHP() const { return stat.HP; }
//int Character::GetMP() const { return MP; }
int Character::GetAttack() const { return stat.Attack; }
int Character::GetDefense() const { return stat.Defense; }
int Character::GetEXP() const { return EXP; }
int& Character::GetGold() { return Gold; }


//Setter
/*
void Character::SetName(std::string name) {
	Name = name;
}

void Character::SetLevel(int level) {
	//level underflow prevention
	if (level < 1) {
		level = 1;
	}
	if (Level < level) {
		Level = level;
	}
}
*/
void Character::SetMaxHP(int maxhp) {
	if (maxhp < 0) {
		maxhp = 0;
	}
	stat.MaxHP = maxhp;
	if (stat.MaxHP < stat.HP) {
		stat.HP = stat.MaxHP;
	}
	LogSystem::UpdateStatus();
}

void Character::SetHP(int hp) {
	//HP underflow/overflow prevention
	if (hp < 0) {
		hp = 0;
	}
	else if (stat.MaxHP < hp) {
		hp = stat.MaxHP;
	}
	stat.HP = hp;
	LogSystem::UpdateStatus();
}

void Character::SetAttack(int attack) {
	stat.Attack = attack;
	LogSystem::UpdateStatus();
}

void Character::SetDefense(int defense) {
	stat.Defense = defense;
	LogSystem::UpdateStatus();
}

void Character::SetEXP(int exp) {
	EXP = exp;
	LogSystem::UpdateStatus();
}

void Character::SetGold(int gold) {
	if (gold < 0) {
		gold = 0;
	}
	Gold = gold;
	LogSystem::UpdateStatus();
}