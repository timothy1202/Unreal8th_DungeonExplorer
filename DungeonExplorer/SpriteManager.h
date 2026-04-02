#pragma once
#include "LayoutManager.h"
#include "string.h"
#include <vector>
#include <sstream>



class SpriteManager {
private:
	struct MonstAnimStruct {
		std::vector<std::string> Sprite;
		int X;
		int Y;
		MonstAnimStruct(std::vector<std::string> sprite, int x, int y) : Sprite(sprite), X(x), Y(y) { }
		MonstAnimStruct() : Sprite({""}), X(0), Y(0) {}
	};
	static SpriteManager& GetInstance() {
		static SpriteManager Instance;
		return Instance;
	}
	SpriteManager() {
		Monsters = std::vector<MonstAnimStruct>(0);
		Status = std::vector<int>(0);
	}

	std::vector<MonstAnimStruct> Monsters;//0:None(Dead),1:Goblin, 2:Orc, 3:Troll, 4:Slime, 5:Boss
	std::vector<int> Status;//0:dead, 1:default, 2: Attacking the player, 3:Attacked by player
	//Attack Motions
	std::vector<std::string> SP_Attack1 = {			"\033[91m    / \033[0m",
													"\033[91m  /// \033[0m",
													"\033[91m  /   \033[0m",
													"",
													""};

	std::vector<std::string> SP_Attack2 = {			"\033[91m    / \033[0m",
													"\033[91m  /// \033[0m",
													"\033[91m///// \033[0m",
													"\033[91m///   \033[0m" 
													"\033[91m/     \033[0m"};

	std::vector<std::string> SP_Attack3 = {			"",
													"",
													"\033[91m  /   \033[0m",
													"\033[91m /    \033[0m",
													"\033[91m//    \033[0m", };

	std::vector<std::string> SP_Attack4 = {			"",
													"",
													"",
													"\033[91m /    \033[0m",
													"\033[91m/     \033[0m" };

	std::vector<std::string> SP_Attack5 = { };

	std::vector<std::vector<std::string>> SP_Attack = { SP_Attack1, SP_Attack2, SP_Attack3, SP_Attack4, SP_Attack5};

	//Monster Sprites, +6 index for each side(ANSI)
	std::vector<std::string> SP_Goblin = {	"\033[92m     /----\\   \033[0m",	//Green Gobline
											"\033[92m@ <<<@_ @  >>> \033[0m",
											"\033[92m @  \\_^__/    \033[0m",
											"\033[92m  &  /  \\\\   \033[0m",
											"\033[92m   \\\\ x  \\& \033[0m",
											"\033[92m    \\\\___/ _ \033[0m",
											"\033[92m   /__/  \\__\\\033[0m"};

	std::vector<std::string> SP_Orc = {		"\033[95m\\>  /----\\   \033[0m",	//Magenta Orc
											"\033[95m\\> #@_ @  #   \033[0m",
											"\033[95m \\> \\;-;_/   \033[0m",
											"\033[95m  &  /  \\\\   \033[0m",
											"\033[95m   \\/ @  \\\\&\033[0m",
											"\033[95m    \\\\___/ _ \033[0m",
											"\033[95m   /__/  \\__\\\033[0m" };

	std::vector<std::string> SP_Troll = {   "\033[94m    /----\\    \033[0m",	//Blue Troll
											"\033[94m   (@_ @  )    \033[0m",
											"\033[94m   _\\###_/_   \033[0m",
											"\033[94m  / /    \\ \\ \033[0m",
											"\033[94m @% \\ x  \\ %@\033[0m",
											"\033[94m   _\\___/ _    \033[0m",
											"\033[94m  /__/  \\__\\ \033[0m" };

	std::vector<std::string> SP_Slime = {	"\033[92m     _/|^^^\\  \033[0m",	//Green Slime
											"\033[92m   _/  |_   \@@\033[0m",
											"\033[92m _/@  @  \\_ @@\033[0m",
											"\033[92m/   ^      \\  \033[0m",
											"\033[92m\\__________/  \033[0m" };

	std::vector<std::string> SP_Boss = {	"\033[93m/    /_-_\\    \033[0m",	//Yellow Boss
											"\033[93m||  /@||@ \\   \033[0m",
											"\033[93m{\\ \\_\\---_/_\033[0m",
											"\033[93m  \\//#===#--- \033[0m",
											"\033[93m  @%  |==|   | \033[0m",
											"\033[93m    \\ ### \\_/\033[0m",
											"\033[93m   /##/  \\##\\\033[0m" };

	std::vector<std::string> SP_MonsterAttack = {	"\033[91m \\/ /\\  /\\/ /\033[0m",
													"\033[91m  \\/  \\/  \\/ \033[0m" };

	//create image for the MainBuffer based on the Animation Status
	static void GenerateSpriteBuffer() {
		SpriteManager& SM = GetInstance();

		//Add monster to the main buffer in reversed order (not to be affacted by index change in the process)
		LayoutManager::ResetMain();
		for (int i = SM.Monsters.size() - 1; i >= 0; i--) {
			if (SM.Status[i] == 1) {	//When the monster is alive
				LayoutManager::UpdateMain(SM.Monsters[i].Sprite, SM.Monsters[i].X, SM.Monsters[i].Y);
			}
			if (SM.Status[i] == 2) {	//When the monster is attacking
				LayoutManager::UpdateMain(SM.Monsters[i].Sprite, SM.Monsters[i].X, SM.Monsters[i].Y + 2);
				LayoutManager::UpdateMain(SM.SP_MonsterAttack, SM.Monsters[i].X, SM.Monsters[i].Y + 9);
			}
		}
		LayoutManager::ClearWindow();
		LayoutManager::PrintFrame();
		Sleep(200);
	}

	//create image for the MainBuffer based on the Animation Status
	static void GenerateAttackedBuffer() {
		SpriteManager& SM = GetInstance();
		//repeat 5 times for the attack sprites
		for (int atk = 0; atk < SM.SP_Attack.size(); atk++) {
			//Add monster to the main buffer in reversed order (not to be affacted by index change in the process)
			LayoutManager::ResetMain();
			for (int i = SM.Monsters.size() - 1; i >= 0; i--) {
				if (SM.Status[i] == 1) {	//When the monster is alive
					LayoutManager::UpdateMain(SM.Monsters[i].Sprite, SM.Monsters[i].X, SM.Monsters[i].Y);
				}
				if (SM.Status[i] == 3) {	//When the monster is attacking
					LayoutManager::UpdateMain(SM.Monsters[i].Sprite, SM.Monsters[i].X, SM.Monsters[i].Y);
					if (!SM.SP_Attack[atk].empty()) {
						LayoutManager::UpdateMain(SM.SP_Attack[atk], SM.Monsters[i].X + 6, SM.Monsters[i].Y);
					}
				}
			}
			//std::cout << "\033[H";
			LayoutManager::ClearWindow();
			LayoutManager::PrintFrame();
			Sleep(75);
		}
	}
public:
	static void SetMonsterGroup(std::vector<std::string> NewMonsters) {
		SpriteManager& SM = GetInstance();

		//Reset Monster Group
		SM.Monsters.clear();
		SM.Status.clear();

		//Set Animation structure
		int distance = (LayoutManager::GetMainLength() / NewMonsters.size());
		int origin = LayoutManager::GetMainLength() / (NewMonsters.size() + 1);
		SM.Monsters = std::vector<MonstAnimStruct>(NewMonsters.size());
		for (int i = 0; i < NewMonsters.size(); i++) {
			if(NewMonsters[i] == "Goblin") SM.Monsters[i] = MonstAnimStruct(SM.SP_Goblin, origin + distance * i - 14, 1);
			else if (NewMonsters[i] == "Orc") SM.Monsters[i] = MonstAnimStruct(SM.SP_Orc, origin + distance * i - 14, 1);
			else if (NewMonsters[i] == "Troll") SM.Monsters[i] = MonstAnimStruct(SM.SP_Troll, origin + distance * i - 14, 1);
			else if (NewMonsters[i] == "Slime") SM.Monsters[i] = MonstAnimStruct(SM.SP_Slime, origin + distance * i - 14, 1);
			else if (NewMonsters[i] == "Boss") SM.Monsters[i] = MonstAnimStruct(SM.SP_Boss, origin + distance * i - 14, 1);
		}
		SM.Status = std::vector<int>(NewMonsters.size(), 1);
		GenerateSpriteBuffer();
	}

	//change Monster's sprite status and update the main buffer
	static void SetMonsterStatus(std::vector<int> NewStatus) {
		//set the status and reset non-target monsters' status
		SpriteManager& SM = GetInstance();
		bool isAttacking = false;
		for (int i = 0; i < SM.Status.size(); i++) {
			//if not dead, update status
			if (SM.Status[i] != 0) {
				SM.Status[i] = NewStatus[i];
				if (NewStatus[i] == 3) {
					isAttacking = true;
				}
				
			}
		}

		//Generate Buffer depending on the status
		if (isAttacking) {	//when player attacks
			GenerateAttackedBuffer();
		}
		else {	//else
			GenerateSpriteBuffer();
		}
	}
};

/*
static void PrintAll() {
		SpriteManager& SM = GetInstance();
		for (std::string temp : SM.SP_Slime) {
			std::cout << temp << std::endl;
		}

		for (std::string temp : SM.SP_Goblin) {
			std::cout << temp << std::endl;
		}

		for (std::string temp : SM.SP_Orc) {
			std::cout << temp << std::endl;
		}

		for (std::string temp : SM.SP_Troll) {
			std::cout << temp << std::endl;
		}

		for (std::string temp : SM.SP_Boss) {
			std::cout << temp << std::endl;
		}

		for (std::string temp : SM.SP_MonsterAttack) {
			std::cout << temp << std::endl;
		}
	}*/