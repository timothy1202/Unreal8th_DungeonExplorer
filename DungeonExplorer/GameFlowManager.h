#pragma once

class GameManager;
class BattleManager;
class StageManager;
class Job;

class GameFlowManager {
private:
	GameManager& gm;
	StageManager& sManager;
	BattleManager* bManager;

public:
	GameFlowManager();

	void run();

	void setupPlayer();

	void selectNextNode();

	void battleNode();

	void storeNode();

	void bossNode();

	void CheckInventory();

	void gameOver();

	void gameClear();
};