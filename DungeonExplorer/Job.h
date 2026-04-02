//Job.h
#pragma once

#include "Stat.h"
//#include "Character.h"

class Character;

class Job {
public:
	virtual FStat GetBaseStat() const = 0;
	virtual FStat GetLevelUpBonus() const = 0;
	virtual int SkillDamage(const Character& character) const = 0;
	virtual std::string SkillName() const = 0;
	virtual std::string JobName() const = 0;
};