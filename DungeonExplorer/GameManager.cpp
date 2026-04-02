#include <iostream>
#include <string>
#include "GameManager.h"
#include "Character.h"
#include "Inventory.h"
#include "Job.h"
#include "Warrior.h"

using namespace std;

// Constructor
GameManager::GameManager(): player(nullptr), playerJob(nullptr) {
	inven = new Inventory;
}

// Destructor
GameManager::~GameManager() {
	if (player != nullptr) delete player;
	if (playerJob != nullptr) delete playerJob;
}

// Create the player only if it does not exist
void GameManager::createPlayer(string name, Job* pJob) {
	playerJob = pJob;
	player = Character::GetInstance(name, *playerJob);
}

// SingleTon - Created only once
GameManager& GameManager::GetInstance() {
	static GameManager instance;
	return instance;
}