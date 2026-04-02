#include "AttackStrategy.h"

int NormalAttack::calculateDamage(int atk,int armor) {
	const float K = 30.0f;

	float damageReduction = K / (K + static_cast<float>(armor));

	auto& gen = MakeRandom::getGenerator();

	float diceValue = RollDice::useDice(1, 6);
	diceValue = (diceValue < 4) ? 1 : 1.2;

	int minDmg = atk * diceValue * 0.35;
	int maxDmg = atk * diceValue * 0.4;
	if (minDmg <= 0) minDmg = 1;
	if (maxDmg <= 0) maxDmg = 1;
	std::uniform_int_distribution<int> dmgDist(minDmg, maxDmg);
	return dmgDist(gen)*damageReduction;
}

int SpecialAttack::calculateDamage(int atk,int armor) {
	const float K = 30.0f;

	float damageReduction = K / (K + static_cast<float>(armor));

	auto& gen = MakeRandom::getGenerator();

	float diceValue = RollDice::useDice(1, 6);
	diceValue = (diceValue < 4) ? 1 : 1.2;

	int minDmg = atk * diceValue * 0.7;
	int maxDmg = atk * diceValue * 0.8;
	if (minDmg <= 0) minDmg = 1;
	if (maxDmg <= 0) maxDmg = 1;
	std::uniform_int_distribution<int> dmgDist(minDmg, maxDmg);
	return dmgDist(gen)*damageReduction;
}