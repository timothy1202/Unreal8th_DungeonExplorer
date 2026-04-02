#include "RollDice.h"

int RollDice::useDice(int num,int spots ) {
	auto& gen = MakeRandom::getGenerator();
	std::uniform_int_distribution<int> dice(1, spots);
	int diceValue = 0;

	for (int i = 0; i < num; ++i) {
		diceValue += dice(gen);
	}

	return diceValue;
}