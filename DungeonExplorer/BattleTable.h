// BattleTable.h
#pragma once
#include "StageManager.h"
#include "RandomManager.h"
#include <map>
#include <string>
#include <vector>

struct MonsterReward{
    int minGold;
    int maxGold;
    int itemId;
    float dropRate; 
};

class BattleTable{
public:
    // TODO:CPP 
    inline static std::map<EStage, std::vector<std::string>> stageTable = {
        { DARK_CAVE,{"Goblin", "Orc"}},
        { DIRTY_SWAMP, {"Troll", "Slime"}},
        { MISTY_FOREST, {"Goblin", "Orc", "Troll", "Slime"}}
    };
    
    inline static std::map<std::string, MonsterReward> rewardTable ={
        {"Goblin",{50, 100, 101, 0.5f}},
        {"Orc",{100, 150, 103, 0.3f}},
        {"Troll", {200, 250, 202, 0.1f}},
        {"Slime",{100,130, 301, 0.8f}}
    };
    
    static const std::vector<std::string>& GetMonsterToStage(EStage stage){
        auto it = stageTable.find(stage);
        if (it != stageTable.end()) return it->second;
        
        static const std::vector<std::string> emptyVector;
        return emptyVector;
    }
    static const MonsterReward& GetRewardToMonster(std::string monster){
        auto it = rewardTable.find(monster);
        if (it != rewardTable.end()) return it->second;
        
        return {0, 0, 0, 0};
    }
};