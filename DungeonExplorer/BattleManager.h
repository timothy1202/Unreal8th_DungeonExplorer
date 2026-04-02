// BattleManager.h
#pragma once
#include "BattleDice.h"
#include "GameManager.h"
#include "AttackStrategy.h"

class Character;
class Monster;
static SpecialAttack specialAtk;
static NormalAttack normalAtk;

class BattleManager{
private:
    int turnCount;
    BattleDice diceRoll;
    DiceResult diceResult;
    Character& c = *GameManager::GetInstance().getPlayer();
    BattleManager() = default; 
public:
    static BattleManager& GetInstance(){
        static BattleManager instance;
        return instance;
    }
    
    BattleManager(const BattleManager&) = delete;
    BattleManager operator=(const BattleManager&) = delete;
    
    void StartBattle();   
    bool AutoBattle(std::vector<Monster*>& m);
    bool PlayerTurn(std::vector<Monster*>& m, Monster*& target, int index);
    void MonstersTurn(std::vector<Monster*>& m);
    void ApplyDiceResult(DiceResult result);
    void UsePotionToPer(float perHP);
    void StartBossBattle();
};