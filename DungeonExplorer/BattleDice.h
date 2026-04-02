// BattleDice.h 
#pragma once
#include <string>
#include <map>
#include <vector>

struct DiceResult{
    std::string description;
    int hpDelta;
    int atkDelta;
    int missChance;
    int diceNum = 0;
};

class BattleDice{
private:
    std::map<int, std::vector<DiceResult>> eventTable;
    std::map<int, std::string> missTable;
public:
    BattleDice();
    
    DiceResult Roll();
    std::string missMessage();
};