#include "CreateMonster.h"

Monster* CreateMonster::createGoblin(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	int hp = 30;
	int atk = 5;

	std::uniform_int_distribution<int> hpDist(level * 30, level * 40);
	std::uniform_int_distribution<int> atkDist(level * 7, level * 8);

	hp += hpDist(gen);
	atk += atkDist(gen);
	auto normalAttack = std::make_unique<NormalAttack>();

	return new Goblin(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createOrc(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	int hp = 80;
	int atk = 5;
	std::uniform_int_distribution<int> hpDist(level * 80, level * 100);
	std::uniform_int_distribution<int> atkDist(level * 5, level * 6);

	hp += hpDist(gen);
	atk += atkDist(gen);
	auto normalAttack = std::make_unique<NormalAttack>();

	return new Orc(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createSlime(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	int hp = 20;
	int atk = 6;
	std::uniform_int_distribution<int> hpDist(level * 25, level * 35);
	std::uniform_int_distribution<int> atkDist(level * 9, level * 10);

	hp += hpDist(gen);
	atk += atkDist(gen);
	auto normalAttack = std::make_unique<NormalAttack>();

	return new Slime(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createTroll(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	int hp = 60;
	int atk = 5;
	std::uniform_int_distribution<int> hpDist(level * 70, level * 80);
	std::uniform_int_distribution<int> atkDist(level * 4, level * 5);

	hp += hpDist(gen);
	atk += atkDist(gen);
	auto normalAttack = std::make_unique<NormalAttack>();

	return new Troll(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createBoss(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	int hp = 40;
	int atk = 10;
	std::uniform_int_distribution<int> hpDist(level * 75, level * 85);
	std::uniform_int_distribution<int> atkDist(level * 10, level * 12);

	hp += hpDist(gen);
	atk += atkDist(gen);
	auto normalAttack = std::make_unique<NormalAttack>();

	return new Boss(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::create(MonsterType type, std::string name, int level) {
	switch (type) {
	case MonsterType::Goblin: return createGoblin(name, level);
	case MonsterType::Orc: return createOrc(name, level);
	case MonsterType::Slime: return createSlime(name, level);
	case MonsterType::Troll: return createTroll(name, level);
	}
}