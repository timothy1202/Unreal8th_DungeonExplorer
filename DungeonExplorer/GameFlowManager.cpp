#include "GameFlowManager.h"
#include "GameManager.h"
#include "Character.h"
#include "LogSystem.h"
#include "BattleManager.h"
#include "StageManager.h"
#include "Job.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Archer.h"
#include "Store.h"
#include <string>
#include <iostream>

using namespace std;

vector<string> chooseAction = {
	"",
	"Choose the next Action" ,
	"1. Fight Monster",
	"2. Enter Store",
	"3. Show Inventory",
	""
};

vector<string> InvalidInput = { "is InValid Input" };

vector<string> chooseStoreAction = {
	"Select Action",
	"1. buy Item",
	"2. Sell Item",
	"3. Leave Store"
};

vector<string> checkItemEquip = {
	"",
	"Inventory Opened. Choose your next action.",
	"1. Equip Item",
	"2. Use Item",
	"3. Close Inventory"
};

vector<string> blank = { "" };

// Constructor
GameFlowManager::GameFlowManager() :
	gm(GameManager::GetInstance()), 
	bManager(nullptr), 
	sManager(StageManager::GetInstance())
	{}

// Overall game flow
void GameFlowManager::run() {
	setupPlayer();

	ItemManager::GetInstance().Initialize();

	while(!gm.getIsGameClear()) {
		if (gm.getPlayer()->GetHP() > 0) {
			selectNextNode();
		}
		else break;
	}
	
	if (gm.getIsGameClear()) gameClear();
	else gameOver();
}

// Input Player Name & create Player
void GameFlowManager::setupPlayer() {
	string name;
	vector<string> setPlayer;
	setPlayer.push_back("Welcome to Dungeon Explorer!");
	setPlayer.push_back("Let's set your Player name. ");
	LogSystem::PrintStringsOnLog(setPlayer);
	setPlayer.clear();
	cout << TextFormat::CYAN << "Input Player Name:" << TextFormat::DEFAULT;
	// Enter name allowing spces
	while (true) {
		getline(cin, name);

		//Remove leading whitespaces from the string
		size_t startBlank = name.find_first_not_of(" \t\n\r\f\v");

		// if the input contains only whitespace
		if (startBlank == string::npos) {
			LogSystem::PrintStringsOnLog(InvalidInput);
			cout << "Enter Player Name : ";
		}
		else {
			// Store the input after removing leading whitespace
			name = name.substr(startBlank);
			break;
		}
	}

	// Select Player Jobs
	string jobName;
	int jNum = 0;
	setPlayer.push_back("Select Player Job");
	setPlayer.push_back("1. Warrior");
	setPlayer.push_back("2. Wizard");
	setPlayer.push_back("3. Archer");
	LogSystem::PrintStringsOnLog(setPlayer);
	cout << TextFormat::CYAN << "Enter Job Number:" << TextFormat::DEFAULT;
	while (!(cin >> jNum)) {
		cin.clear();
		cin.ignore(1000, '\n');
		LogSystem::PrintStringsOnLog(InvalidInput);
		cout << "Enter Job Number : ";
	}
	
	Job* playerJob = nullptr;
	switch (jNum)
	{
	case 1:
		playerJob = new Warrior();
		jobName = "Warrior";
		break;
	case 2:
		playerJob = new Wizard();
		jobName = "Wizard";
		break;
	case 3:
		playerJob = new Archer();
		jobName = "Archer";
		break;
	default:
		break;
	}

	LogSystem::ClearLogBuffer();
	LogSystem::CreateCharacter(name, jobName);
	gm.createPlayer(name, playerJob);
	LogSystem::UpdateStatus();
}

// Select next path
void GameFlowManager::selectNextNode() {
	Character* player = gm.getPlayer();

	int nextNode = 0;

	while (true) {
		LogSystem::PrintStringsOnLog(chooseAction);
		cout << TextFormat::CYAN << "Select next path :" << TextFormat::DEFAULT;

		// Guard Invalid Input
		if (!(cin >> nextNode)) {
			cin.clear();
			cin.ignore(1000, '\n');
			LogSystem::PrintStringsOnLog(InvalidInput);
			continue;
		}

		if (nextNode == 1){
			battleNode();
			break;
		}
		else if (nextNode == 2) {
			storeNode();
			break;
		}
		else if (nextNode == 3) {
			CheckInventory();
			break;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		LogSystem::PrintStringsOnLog(InvalidInput);
	}
}

// Generate Monster & Battle
void GameFlowManager::battleNode() {
	LogSystem::ClearLogBuffer();
	// Initialize Stage
	EStage currentStage = sManager.GetCurrentStage();
	if (currentStage == EStage::NONE) {
		sManager.SetStage(EStage::DARK_CAVE);
		currentStage = sManager.GetCurrentStage();
	}

	int level = gm.getPlayer()->GetLevel();
	vector<string> moveStage;
	// Select Stage
	if (level <= 3) {
		if (currentStage != EStage::DARK_CAVE) {
			string move = gm.getPlayer()->GetName() + " move to the Dark Cave";
			moveStage.push_back(move);
			LogSystem::PrintStringsOnLog(moveStage);

			sManager.SetStage(EStage::DARK_CAVE);
		}
	}
	else if (level <= 6) {
		if (currentStage != EStage::DIRTY_SWAMP) {
			string move = gm.getPlayer()->GetName() + " move to the Dirty Swamp";
			moveStage.push_back(move);
			LogSystem::PrintStringsOnLog(moveStage);

			sManager.SetStage(EStage::DIRTY_SWAMP);
		}
	}
	else if (level <= 9) {
		cout << "Stage 3\n";
		if (currentStage != EStage::MISTY_FOREST) {
			string move = gm.getPlayer()->GetName() + " move to the Misty Forest";
			moveStage.push_back(move);
			LogSystem::PrintStringsOnLog(moveStage);

			sManager.SetStage(EStage::MISTY_FOREST);
		}
	}
	else if (level == 10) {
		string move = gm.getPlayer()->GetName() + " move to the Boss Room";
		bossNode();
		return;
	}

	// Start Battle
	if (bManager == nullptr) {
		bManager = &BattleManager::GetInstance();
	}
	bManager->StartBattle();
	
	// Player Level Up
	while (gm.getPlayer()->GetEXP() >= 100) {
		string job = gm.getPlayer()->GetCurrentJob();
		Job* playerJob = gm.getPlayerJob();

		if (playerJob != nullptr) {
			gm.getPlayer()->LevelUP(*playerJob);
		}
	}

	LogSystem::UpdateStatus();
}

// Enter Store
void GameFlowManager::storeNode() {
	LogSystem::ClearLogBuffer();
	LogSystem::ClearMainBuffer();
	LogSystem::PrintStringsOnMain(blank);

	vector<string> enterStore = { "Enter the Store", "Restore Player HP to full", " "};
	LogSystem::PrintStringsOnLog(enterStore);

	// Restore HP to maxHP;
	int maxHp = gm.getPlayer()->GetMaxHP();
	gm.getPlayer()->SetHP(maxHp);

	// Initialize Store
	Store store;
	store.InitializeStore();

	int selection;
	while (1) {
		LogSystem::PrintStringsOnLog(chooseStoreAction);
		cout << TextFormat::CYAN <<"Enter Choice:" << TextFormat::DEFAULT;
		cin >> selection;
		int& gold = gm.getPlayer()->GetGold();
		LogSystem::ClearLogBuffer();
		// Show Store Item & Buy Item
		if (selection == 1) {
			vector<string> buy = { "Select Action: Buy Item" };
			LogSystem::PrintStringsOnLog(buy);

			store.ShowShopMenu(gold);
			int ItemSelect;
			cout << TextFormat::CYAN << "Enter the Item Number to Buy: " << TextFormat::DEFAULT;
			cin >> ItemSelect;
			store.BuyItem(ItemSelect, gold, *gm.getInventory());
		}
		// Show Inventory & Sell Item
		else if (selection == 2) {
			vector<string> sell = { "Select Action: Sell Item" };
			LogSystem::PrintStringsOnLog(sell);

			LogSystem::ShowItems(gm.getInventory()->GetOwnedItems());
			int ItemSelect;
			cout << TextFormat::CYAN << "Enter the Item Number to Sell: " << TextFormat::DEFAULT;
			cin >> ItemSelect;
			store.SellItem(ItemSelect, gold, *gm.getInventory());
		}
		// Leave Store
		else if (selection == 3) {
			vector<string> leaveStore = { "Leave the Store", ""};
			LogSystem::PrintStringsOnLog(leaveStore);
			break;
		}

		LogSystem::UpdateStatus();
		LogSystem::ClearMainBuffer();
		LogSystem::PrintStringsOnMain(blank);
	}
}

// Generate Boss & Battle
void GameFlowManager::bossNode() {
	if (bManager == nullptr) bManager = &BattleManager::GetInstance();
	bManager->StartBossBattle();
}

void GameFlowManager::CheckInventory() {
	LogSystem::ClearLogBuffer();
	while (1) {
		LogSystem::ClearMainBuffer();
		LogSystem::ShowItems(gm.getInventory()->GetOwnedItems());

		LogSystem::PrintStringsOnLog(checkItemEquip);
		cout << TextFormat::CYAN << "Enter Choice:" << TextFormat::DEFAULT;

		int selection;
		cin >> selection;
		LogSystem::ClearLogBuffer();
		LogSystem::PrintStringsOnLog(blank);
		if(selection == 1){
			int ItemSelect;
			cout << TextFormat::CYAN << "Enter the Item Number to Equip: " << TextFormat::DEFAULT;
			cin >> ItemSelect;

			gm.getInventory()->EquipItem(ItemSelect);
		}
		else if (selection == 2) {
			gm.getInventory()->UseItem();
		}
		else if (selection == 3) {
			vector<string> CloseInven = { "Close Inventory" };
			LogSystem::PrintStringsOnLog(CloseInven);
			LogSystem::ClearMainBuffer();
			break;
		}
	}
}

void GameFlowManager::gameOver() {
	LogSystem::PlayerDied();
	LogSystem::ShowStatistics();
}

void GameFlowManager::gameClear() {
	LogSystem::ShowStatistics();
}