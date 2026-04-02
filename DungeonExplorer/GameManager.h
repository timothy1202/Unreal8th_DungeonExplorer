#pragma once
#include <string>

class Character;
class Inventory;
class Job;

class GameManager {
private:
	GameManager();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	Character* player;
	Inventory* inven;
	Job* playerJob;

	bool isGameClear = false;
public:
	static GameManager& GetInstance();

	~GameManager();

	void createPlayer(std::string name = "player", Job* playerJob = nullptr);

	Character* getPlayer() { return player; }
	Inventory* getInventory() { return inven; }
	Job* getPlayerJob() { return playerJob; }
	bool getIsGameClear() { return isGameClear; }

	void setGameClear() { isGameClear = true; }
};