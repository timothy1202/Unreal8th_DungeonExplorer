// BattleSupply.cpp
#include <iostream>
#include "BattleSupply.h"
#include "BattleTable.h"
#include "Character.h"
#include "StageManager.h"
#include "Monster.h"
#include "RandomManager.h"
#include "CreateMonster.h"
#include "ItemFactory.h"
#include "Inventory.h"
#include "LogSystem.h"
#include "SpriteManager.h"
#include <sstream>

using namespace std;

BattleSupply::BattleSupply(){
    monsterFactory["Goblin"] = CreateMonster::createGoblin;
    monsterFactory["Orc"] = CreateMonster::createOrc;
    monsterFactory["Troll"] = CreateMonster::createTroll;
    monsterFactory["Slime"] = CreateMonster::createSlime; 
}
std::vector<Monster*> BattleSupply::BattleSpawnMonster(){
    spawnedList.clear();
    // spawn monster count < suffixes 
    std::vector<std::string> suffixes = {"Spearman", "Archer", "Guard", "Scout", "Shaman"};
    RandomManager::GetInstance().ShuffleVectorString(suffixes);
    
    // Check set stage
    EStage currentStage = StageManager::GetInstance().GetCurrentStage();
    if (currentStage == EStage::NONE) return spawnedList;
    
    // Check stage spawn monster 
    std::vector<std::string> monsterPool = BattleTable::GetMonsterToStage(currentStage);
    if (monsterPool.empty()) return spawnedList; 
    
    // Monster random count 1 ~ 4
    vector<string> SpriteList = {};    //for creating Monster Sprite.
    int count = RandomManager::GetInstance().GetRange(1,4);
    for (int i = 0; i < count; ++i)
    {
        int randomIndex = RandomManager::GetInstance().GetRange(0, monsterPool.size() - 1);
        std::string findMonster = monsterPool[randomIndex];
        SpriteList.push_back(findMonster);  //Count Monster to add on the screen.
        
        // Check monster in MonsterFactory 
        auto it = monsterFactory.find(findMonster);
        if (it == monsterFactory.end())
        {
            LogSystem::PrintStringsOnLog({ "Error not found monster" });
            continue; 
        }
        
        // Create Random Monster
        std::string monsterName = findMonster + " " + suffixes[i % suffixes.size()]; // defense if i > suffixes.size()
        Monster* newMonster = it->second(monsterName, player->GetLevel());
        spawnedList.push_back(newMonster);
        // for reward
        rewardList.push_back(findMonster);
    }
    SpriteManager::SetMonsterGroup(SpriteList); //Create Monster on the screen.

    return spawnedList; 
}

Monster* BattleSupply::SpawnBoss() {
    return CreateMonster::createBoss("Death Knight", 10);
}

void BattleSupply::BattleReward(){
    std::vector<Item> getItemList;
    int totalGold = 0;
    int totalEXP = 0;
    
    for (auto m : rewardList)
    {
        MonsterReward rewardMob = BattleTable::GetRewardToMonster(m);
        
        // Get EXP
        int randomEXP = RandomManager::GetInstance().GetRange(10, 30);
        int getEXP = player->GetEXP();
        player->SetEXP(getEXP + randomEXP);
        totalEXP += randomEXP;
        
        // Create item
        Item getItem = ItemFactory::CreateItem(rewardMob.itemId);
        
        // Get Gold
        float randomChance = RandomManager::GetInstance().GetRange(0.0f, 1.0f);
        int randomGold = RandomManager::GetInstance().GetRange(rewardMob.minGold, rewardMob.maxGold);
        if (randomChance <= rewardMob.dropRate )
        {
            int playerGold = player->GetGold();
            
            player->SetGold(playerGold + randomGold);

            totalGold += randomGold;
            GameManager::GetInstance().getInventory()->AddItem(getItem);
            getItemList.push_back(getItem);
        }
        else
        {
            stringstream SS;
            SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT
                << " " << m << " dropped nothing. (" << rewardMob.dropRate * 100 << "% drop)";
            LogSystem::PrintStringsOnLog({SS.str()});
        }
    }
    LogSystem::GetReward(totalEXP, totalGold, getItemList);
    rewardList.clear();
}
