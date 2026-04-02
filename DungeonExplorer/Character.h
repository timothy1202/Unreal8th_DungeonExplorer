//Character.h
#pragma once 

#include "Stat.h"
#include <string>


class Job;

class Character
{
public:
	static Character* GetInstance(const std::string& name, const Job& job);
	static Character* GetInstance();
	static void DestroyInstance(); //singleton instance delete

	//void displayStatus() const;
	void LevelUP(const Job& job);

	std::string GetName() const;
	std::string GetCurrentJob() const;
	int GetLevel() const;
	int GetMaxHP() const;
	//int GetMaxMP() const;
	int GetHP() const;
	//int GetMP() const;
	int GetAttack() const;
	int GetDefense() const;
	int GetEXP() const;
	int& GetGold();

	//void SetName(std::string name);
	//void SetLevel(int level);
	void SetMaxHP(int maxhp);
	void SetHP(int hp);
	void SetAttack(int attack);
	void SetDefense(int defense);
	void SetEXP(int exp);
	void SetGold(int gold);

private:
	//Singleton Pattern
	Character(const std::string& name, const Job& job); 
	Character(const Character&) = delete;
	Character& operator = (const Character&) = delete;
	
	static Character* Instance;

	std::string Name;
	std::string CurrentJob;
	int Level;
	FStat stat; //MaxHP, HP, Attack, Defense
	int EXP;
	int Gold;
};