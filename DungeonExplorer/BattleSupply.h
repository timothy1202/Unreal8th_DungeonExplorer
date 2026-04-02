// BattleSupply.h
#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "GameManager.h"

class Monster;

class BattleSupply{
private:
    std::vector<Monster*> spawnedList;
    std::vector<std::string> rewardList; 
    std::map<std::string, std::function<Monster*(std::string, int)>> monsterFactory; 
    Character* player = GameManager::GetInstance().getPlayer();
    BattleSupply();
public:
    static BattleSupply& GetInstance(){
        static BattleSupply instance;
        return instance;
    }
    
    BattleSupply(const BattleSupply&) = delete;
    BattleSupply operator=(const BattleSupply&) = delete;
    
    std::vector<Monster*> BattleSpawnMonster();
    Monster* SpawnBoss();
    void BattleReward();
};