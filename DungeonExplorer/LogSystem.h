//LogSystem.h
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <stack>
#include <algorithm>
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "LayoutManager.h"
#include <sstream>

#include "iomanip"


//Statistics enum
enum IntStatTypes {
	TOTAL_BATTLES,
	ATTACKS,
	DEALT_DAMAGE,
	TAKEN_DAMAGE,
	KILLED_MONSTERS,
	EARNED_MONEY,
	COLLECTED_ITEMS,
	USED_ITEMS,
	ROLLED_DICE,
	TOTAL_SPOTS,
	COUNT
};
//Statistics enum names, have to be in a same order!
static const std::string IntStatNames[IntStatTypes::COUNT] = { "Total Battles",
															"Attacks",
															"Dealt Damage",
															"Taken Damage",
															"Killed Monsters",
															"Earned Money",
															"Collected Items",
															"Used Items",
															"Rolled Dice",
															"Total Spots" };
//Text Hightlight Formats
namespace TextFormat {
	const std::string DEFAULT = "\033[0m";
	//bold, italic, underline, color
	const std::string RED = "\033[1;3;4;91m";
	const std::string GREEN = "\033[1;3;4;92m";
	const std::string YELLOW = "\033[1;3;4;93m";
	const std::string BLUE = "\033[1;3;4;94m";
	const std::string MAGENTA = "\033[1;3;4;95m";
	const std::string CYAN = "\033[1;3;4;96m";
	const std::string WHITE = "\033[1;3;4;97m";
	const std::string SPLIT_LINE = "\033[1;3;4;92m------------------------------\033[0m";
}
static std::string GetHighlightColor(const Item& i) {
	switch (i.rarity) {
	case Rarity::Common:
		return TextFormat::BLUE;
	case Rarity::Rare:
		return TextFormat::MAGENTA;
	case Rarity::Legendary:
		return TextFormat::YELLOW;
	default:
		return TextFormat::DEFAULT;
	}
}

//Log Management Class
class LogSystem {
private:
	//Singleton 
	static LogSystem& GetInstance() {
		static LogSystem Instance;
		return Instance;
	}
	LogSystem(const LogSystem&) = delete;
	LogSystem& operator=(const LogSystem&) = delete;

	//Constructor
	LogSystem() {
		//Initialize all integer statistics values
		for (int i = 0; i < IntStatTypes::COUNT; i++) Stats[i] = 0;

		//Reset LayoutManager
		LayoutManager::ResetMain();
		LayoutManager::ResetSide();
		LayoutManager::ResetLog();

	}
	//Destructor
	~LogSystem() = default;

	//Statistics variables
	int Stats[IntStatTypes::COUNT];
	std::map<std::string, int> MonstersEncountered;
	std::map<std::string, int> MonstersKilled;

	std::deque<std::string> LogDeque;
	std::deque<std::string> MainDeque;
	std::deque<std::string> SideDeque;
	
	//Push string to LogDeque
	//stringstream version
	static void PushLog(const std::stringstream& ss) {
		//push to the LogDeque
		LogSystem& LS = GetInstance();
		LS.LogDeque.push_front(ss.str());

		//erase the old one if the size is big
		if (LS.LogDeque.size() > LayoutManager::GetLogHeight() - 2) {
			LS.LogDeque.pop_back();
		}
	}
	//string version
	static void PushLog(const std::string& log) {
		//push to the LogDeque
		LogSystem& LS = GetInstance();
		LS.LogDeque.push_front(log);

		//erase the old one if the size is big
		if (LS.LogDeque.size() > LayoutManager::GetLogHeight() - 2) {
			LS.LogDeque.pop_back();
		}
	}

	//Push string to MainDeque
	//stringstream version
	static void PushMain(const std::stringstream& ss) {
		//push to the LogQueue
		LogSystem& LS = GetInstance();
		LS.MainDeque.push_front(ss.str());

		//erase the old one if the size is big
		if (LS.MainDeque.size() > LayoutManager::GetMainHeight() - 2) {
			LS.MainDeque.pop_back();
		}
	}
	//string version
	static void PushMain(const std::string& log) {
		//push to the LogQueue
		LogSystem& LS = GetInstance();
		LS.MainDeque.push_front(log);

		//erase the old one if the size is big
		if (LS.MainDeque.size() > LayoutManager::GetMainHeight() - 2) {
			LS.MainDeque.pop_back();
		}
	}
	//Push string to sideDeque
	//stringstream version
	static void PushSide(const std::stringstream& ss) {
		LogSystem& LS = GetInstance();
		LS.SideDeque.push_front(ss.str());

		//erase the old one if the size is big
		if (LS.SideDeque.size() > LayoutManager::GetSideHeight() - 2) {
			LS.SideDeque.pop_back();
		}
	}
	//string version
	static void PushSide(const std::string& log) {
		LogSystem& LS = GetInstance();
		LS.SideDeque.push_front(log);

		//erase the old one if the size is big
		if (LS.SideDeque.size() > LayoutManager::GetSideHeight() - 2) {
			LS.SideDeque.pop_back();
		}
	}

	//update to LayoutManager LogBuffer
	static void PushToLogBuffer(const std::deque<std::string>& Deque) {
		LayoutManager::ResetLog();
		std::vector<std::string> Content;
		for (auto line = Deque.rbegin(); line != Deque.rend(); line++) {
			Content.push_back(*line);
		}
		LayoutManager::UpdateLog(Content, 0, 0);
	}

	//update to LayoutManager MainBuffer
	static void PushToMainBuffer(const std::deque<std::string>& Deque) {
		LayoutManager::ResetMain();
		std::vector<std::string> Content;
		for (auto line = Deque.rbegin(); line != Deque.rend(); line++) {
			Content.push_back(*line);
		}
		LayoutManager::UpdateMain(Content, 0, 0);
	}

	//update to LayoutManager SideBuffer
	static void PushToSideBuffer(const std::deque<std::string>& Deque) {
		LayoutManager::ResetSide();
		std::vector<std::string> Content;
		for (auto line = Deque.rbegin(); line != Deque.rend(); line++) {
			Content.push_back(*line);
		}
		LayoutManager::UpdateSide(Content, 0, 0);
	}
	//print message separation line in the console
	static std::string PrintLine() {
		std::stringstream SS;
		//std::cout << TextFormat::GREEN << "------------------------------" << TextFormat::DEFAULT << std::endl;
		SS << TextFormat::GREEN << "------------------------------" << TextFormat::DEFAULT;
		return SS.str();
	}

	static void UpdateFrame() {
		LayoutManager::ClearWindow();
		LayoutManager::PrintFrame();
	}
public:
	static void CreateCharacter(std::string PlayerName, std::string JobName) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;
		SS << ">>> " << TextFormat::GREEN << PlayerName << ", The " << JobName << TextFormat::DEFAULT << " enters the dungeon...";
		LS.PushLog(SS);
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();
	}

	static void EnterBattle(const std::vector<Monster*>& monsters) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;
		LS.PushLog(">>> The player is entering for a battle!");

		SS.str("");
		SS << "-> " << TextFormat::RED;
		for (int i = 0; i < monsters.size(); i++) {
			std::string MonsterName = monsters[i]->getName();
			LS.MonstersEncountered[MonsterName.substr(0, MonsterName.find(' '))]++;
			if (i == 0) {
				SS << monsters[i]->getName();
				continue;
			}
			if (i == monsters.size() - 1) {
				SS << ", and " << monsters[i]->getName();
				break;
			}
			SS << ", " << monsters[i]->getName();
		}
		SS <<TextFormat::DEFAULT << (monsters.size() > 1 ? " are" : " is") << " preparing for a battle!";
		LS.PushLog(SS);
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		LS.Stats[IntStatTypes::TOTAL_BATTLES]++;
	}

	static void AttackMonster(Monster* monster, int Damage) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;

		SS.str("");
		SS << ">>> The player attacks the monster " << TextFormat::RED << monster->getName() << TextFormat::DEFAULT << "!";
		LS.PushLog(SS);

		SS.str("");
		SS << "-> The Monster has taken " << Damage << " damage!";
		LS.PushLog(SS);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		LS.Stats[IntStatTypes::ATTACKS]++;
		LS.Stats[IntStatTypes::DEALT_DAMAGE] += Damage;
	}

	static void AttackPlayer(Monster* monster, int Damage) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;
		SS.str("");
		SS << ">>> The monster " << TextFormat::RED << monster->getName() << TextFormat::DEFAULT << " attacks the player!";
		LS.PushLog(SS);

		SS.str("");
		SS << "-> The player has taken " << TextFormat::RED << Damage << TextFormat::DEFAULT << " damage!";
		LS.PushLog(SS);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();
		
		LS.Stats[IntStatTypes::TAKEN_DAMAGE] += Damage;
	}

	static void UseSkill(Monster* monster, std::string SkillText, int Damage) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;
		LS.PushLog(">>> The player casts a skill!");

		SS.str("");
		SS << "-> " << TextFormat::MAGENTA << SkillText << TextFormat::DEFAULT << "!";
		LS.PushLog(SS);

		SS.str("");
		SS << "-> The Monster has taken " << TextFormat::RED << Damage << TextFormat::DEFAULT << " damage!";
		LS.PushLog(SS);
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		GetInstance().Stats[IntStatTypes::ATTACKS]++;
		GetInstance().Stats[IntStatTypes::DEALT_DAMAGE] += Damage;
	}

	static void KillMonster(Monster* monster) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;
		SS.str("");
		SS << ">>> The player has defeated the monster " << TextFormat::RED << monster->getName() << TextFormat::DEFAULT << "!";
		LS.PushLog(SS);
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		std::string MonsterName = monster->getName();
		LS.MonstersKilled[MonsterName.substr(0, MonsterName.find(' '))]++;
	}

	static void GetReward(int Exp, int Gold, const std::vector<Item>& Items) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;
		LS.PushLog(">>> The player gets the rewards!");

		SS.str("");
		SS << "-> Earend experience point: " << TextFormat::CYAN << Exp << TextFormat::DEFAULT << std::string(5, ' ') << "-> Earned gold: " << TextFormat::YELLOW << Gold << TextFormat::DEFAULT;
		LS.PushLog(SS);
		if (!Items.empty()) {
			for (const Item& i : Items) {
				SS.str("");
				SS << "-> Collected an item: " << GetHighlightColor(i) << i.name << TextFormat::DEFAULT;
				LS.PushLog(SS);
			}
		}
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		LS.Stats[IntStatTypes::COLLECTED_ITEMS] += Items.size();
		LS.Stats[IntStatTypes::EARNED_MONEY] += Gold;
	}

	static void BuyItem(const Item& item) {	//Change needed if statistics counts each item separately.
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;

		SS << ">>> The player Bought the item " << GetHighlightColor(item) << item.name << TextFormat::DEFAULT << "!";
		LS.PushLog(SS);
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		LS.Stats[IntStatTypes::COLLECTED_ITEMS]++;
	}

	static void UseItem(const Item& item) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;
		SS << ">>> The player used the item " << GetHighlightColor(item) << item.name << TextFormat::DEFAULT << "!";
		LS.PushLog(SS);
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		LS.Stats[IntStatTypes::USED_ITEMS]++;
	}

	static void ShowItems(const std::vector<Item>& Items) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;

		LS.PushMain(">>> There are some items... ");
		for (int i = 0; i < Items.size(); i++) {
			SS.str("");
			SS << "-> [" << i+1 << "] " 
				<< GetHighlightColor(Items[i]) << Items[i].name << TextFormat::DEFAULT
				<< std::string((std::max)(static_cast<int>(20 - Items[i].name.size()), 1), ' ') << (Items[i].equiped ? "(Equiped) " : "          ") << Items[i].value << " Gold(s): "
				<< Items[i].desc;
			LS.PushMain(SS);
		}
		LS.PushMain(TextFormat::SPLIT_LINE);
		PushToMainBuffer(LS.MainDeque);
		UpdateFrame();
	}

	static void PlayerDied() {	//Change needed if statistics counts each item separately.
		LogSystem& LS = LogSystem::GetInstance();
		LS.PushLog(">>> The player has defeated!");
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();
	}

	static void RollDice(int spots) {
		LogSystem& LS = LogSystem::GetInstance();
		std::stringstream SS;

		SS.str("");
		SS << ">>> Dice has rolled: " << spots;
		//LS.PushLog(SS);
		LS.PushLog(TextFormat::SPLIT_LINE);
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();

		LS.Stats[IntStatTypes::ROLLED_DICE]++;
		LS.Stats[IntStatTypes::TOTAL_SPOTS] += spots;
	}

	static void ShowStatistics() {	//Using Main Section for now
		//Clear Buffer before pushing
		LogSystem& LS = LogSystem::GetInstance();
		LS.MainDeque.clear();
		
		std::stringstream SS;
		const int Spacing = 23;
		//show int stats
		int InfoCount = 0;
		int PrevLen = 0;
		SS.str("");
		LS.PushMain(">>> Gameplay Statistics");
		for (int i = 0; i < IntStatTypes::COUNT; i++) {
			if (InfoCount == 0) {
				std::string temp = "-> " + IntStatNames[i] + ": " + std::to_string(LS.Stats[i]) + ",";
				SS << temp;
				PrevLen = temp.size();
			}
			else {
				std::string temp = "-> " + IntStatNames[i] + ": " + std::to_string(LS.Stats[i]) + ",";
				SS << std::string((std::max)(Spacing - PrevLen, 1), ' ') << temp;
				PrevLen = temp.size();
			}
			InfoCount++;
			//If more than 4 info in the line, push to the buffer
			if (InfoCount > 3) {	
				LS.PushMain(SS);
				SS.str("");
				InfoCount = 0;
			}
		}
		//push remaining info
		if (InfoCount != 0) {
			LS.PushMain(SS);
		}

		//show monster encountered
		SS.str("");
		InfoCount = 0;
		PrevLen = 0;
		LS.PushMain("--> Monsters Encountered");
		for (auto i = LS.MonstersEncountered.begin(); i != LS.MonstersEncountered.end(); i++) {
			if (InfoCount == 0) {
				std::string temp = "-> " + (*i).first + ": " + std::to_string((*i).second);
				SS << temp;
				PrevLen = temp.size();
			}
			else {
				std::string temp = "-> " + (*i).first + ": " + std::to_string((*i).second);
				SS << std::string((std::max)(Spacing - PrevLen, 1), ' ') << temp;
				PrevLen = temp.size();
			}
			InfoCount++;

			//If more than 4 info in the line, push to the buffer
			if (InfoCount > 3) {
				LS.PushMain(SS);
				SS.str("");
				InfoCount = 0;
			}
		}
		//push remaining info
		if (InfoCount != 0) {
			LS.PushMain(SS);
		}


		//show monster killed
		SS.str("");
		InfoCount = 0;
		PrevLen = 0;
		LS.PushMain("--> Monsters Killed");
		for (auto i = LS.MonstersKilled.begin(); i != LS.MonstersKilled.end(); i++) {
			if (InfoCount == 0) {
				std::string temp = "-> " + (*i).first + ": " + std::to_string((*i).second);
				SS << temp;
				PrevLen = temp.size();
			}
			else {
				std::string temp = "-> " + (*i).first + ": " + std::to_string((*i).second);
				SS << std::string((std::max)(Spacing - PrevLen, 1), ' ') << temp;
				PrevLen = temp.size();
			}
			InfoCount++;

			//If more than 4 info in the line, push to the buffer
			if (InfoCount > 3) {
				LS.PushMain(SS);
				SS.str("");
				InfoCount = 0;
			}
		}

		//push remaining info
		if (InfoCount != 0) {
			LS.PushMain(SS);
		}
		PushToMainBuffer(LS.MainDeque);
		UpdateFrame();
	}

	static void UpdateStatus() {
		LogSystem& LS = GetInstance();
		Character* player = Character::GetInstance();
		LS.SideDeque.clear();
		std::stringstream SS;

		LS.PushSide(std::string("==+==[Status]==+=="));
		//Player Name
		SS.str("");
		SS << "  Name  | " << player->GetName();
		LS.PushSide(SS);

		//Job Name
		SS.str("");
		SS << "  Job   | " << player->GetCurrentJob();
		LS.PushSide(SS);
		
		LS.PushSide(std::string("------------------"));
		//Level
		SS.str("");
		SS << "  LV    | " << player->GetLevel();
		LS.PushSide(SS);

		//Experience Point
		SS.str("");
		SS << "  EXP   | " << player->GetEXP();
		LS.PushSide(SS);
		LS.PushSide(std::string("------------------"));
		//Health Point
		SS.str("");
		SS << "  HP    | " << player->GetHP();
		LS.PushSide(SS);

		//Attack
		SS.str("");
		SS << "  ATK   | " << player->GetAttack();
		LS.PushSide(SS);

		//Defense
		SS.str("");
		SS << "  DFS   | " << player->GetDefense();
		LS.PushSide(SS);
		LS.PushSide(std::string("------------------"));
		//Gold
		SS.str("");
		SS << "  Gold  | " << player->GetGold();
		LS.PushSide(SS);

		PushToSideBuffer(LS.SideDeque);
		UpdateFrame();
	}

	static void PrintStringsOnMain(std::vector<std::string> inputs) {	//for other class to push content on the main buffer
		LogSystem& LS = GetInstance();
		for (std::string input : inputs) {
			LS.PushMain(input);
		}
		PushToMainBuffer(LS.MainDeque);
		UpdateFrame();
		Sleep(50);
	}
	static void PrintStringsOnLog(std::vector<std::string> inputs) {	//for other class to push content on the main buffer
		LogSystem& LS = GetInstance();
		for (std::string input : inputs) {
			LS.PushLog(input);
		}
		PushToLogBuffer(LS.LogDeque);
		UpdateFrame();
		Sleep(100);
	}

	static void ClearMainBuffer() {
		LogSystem& LS = GetInstance();
		LS.MainDeque.clear();
		LayoutManager::ResetMain();
		UpdateFrame();
	}

	static void ClearLogBuffer() {
		LogSystem& LS = GetInstance();
		LS.LogDeque.clear();
		LayoutManager::ResetLog();
		UpdateFrame();
	}

	static void ClearSideBuffer() {
		LogSystem& LS = GetInstance();
		LS.SideDeque.clear();
		LayoutManager::ResetSide();
		UpdateFrame();
	}
};