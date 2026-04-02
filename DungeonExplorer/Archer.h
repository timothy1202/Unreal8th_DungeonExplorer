//Archer.h
#pragma once

#include "Stat.h"

class Character;

class Job;

class Archer : public Job
{
public:
	virtual FStat GetBaseStat() const;
	virtual FStat GetLevelUpBonus() const;
	virtual int SkillDamage(const Character& character) const;
	virtual std::string SkillName() const;
	virtual std::string JobName() const;
};