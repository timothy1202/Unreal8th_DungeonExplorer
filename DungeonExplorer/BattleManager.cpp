// BattleManager.cpp
#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "StageManager.h"
#include "RandomManager.h"
#include "BattleSupply.h"
#include "LogSystem.h"
#include "inventory.h"
#include "Job.h"
#include "SpriteManager.h"
#include <iostream>

using namespace std;

void BattleManager::StartBattle(){
    // Random monster spawn 
    std::vector<Monster*> m = BattleSupply::GetInstance().BattleSpawnMonster();
    // first Turn Roll Dice
    diceResult = diceRoll.Roll();
    ApplyDiceResult(diceResult);
    // std::cout << "[Spawn] Spawn monsters!" << std::endl;
    LogSystem::EnterBattle(m);
    bool isWin = AutoBattle(m);
    // End battle, stage random event.
    StageManager::GetInstance().RunRandomEvent(20);
    
    
    if (isWin && c.GetHP() > 0)
    {
        stringstream SS;
        SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " Kill all monster! win character!!!";
        LogSystem::PrintStringsOnLog({ SS.str() });
        // Reward 
        BattleSupply::GetInstance().BattleReward(); 
        // buff effect end
        Inventory* inv = GameManager::GetInstance().getInventory();
        inv->SetTempAtkBuff(0);
    }
    // Delete new monsters
    for (Monster* monsters : m)
    {
        if (monsters != nullptr)
        {
            delete monsters;
            monsters = nullptr;
        }
    }
}

bool BattleManager::AutoBattle(std::vector<Monster*>& m){
    stringstream SS;
    vector<string> Input = {};
    turnCount = 1;
    while (c.GetHP() > 0)
    {
        // Set attack target && Check die monster
        Monster* target = nullptr;
        int index = 0;  //for setting monsters' sprite
        for (auto monster : m)
        {
            if (monster->getHealth() > 0)
            {
                target = monster;
                break;
            }
            index++;
        }
        // Check die all monsters -> Win 
        if (target == nullptr)
            break;
        
        SS.str("");
        SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT  << " Turn count : " << turnCount;
        Input.push_back(SS.str());
        
        // Check alive monster
        int aliveCount = 0;
        for (auto monsters : m) { if (monsters != nullptr && monsters->getHealth() > 0) { aliveCount++; } }
        
        SS.str("");
        SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " Alive Monsters count : " << aliveCount << std::endl;
        Input.push_back(SS.str());
        LogSystem::PrintStringsOnLog({ SS.str() });
        Input.clear();
        Sleep(500);
        
        UsePotionToPer(0.4f);
        
        PlayerTurn(m, target, index);
        MonstersTurn(m);
        ++turnCount;
    }
    return c.GetHP() > 0;
}

bool BattleManager::PlayerTurn(std::vector<Monster*>& m, Monster*& target, int index){
    stringstream SS;
    std::vector<Monster*> killedMonster;
    // Check miss 
    int randomResult = RandomManager::GetInstance().GetRange(1, 100);
    if (randomResult <= diceResult.missChance)
    {
        SS.str("");
        SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " Miss!!  \"" << diceRoll.missMessage() << "\"";
        LogSystem::PrintStringsOnLog({ SS.str() });
    }
    // Player attack monster(target)
    else if (turnCount % 3 != 0)
    {
        target->takeDamage(c.GetAttack());
        LogSystem::AttackMonster(target, c.GetAttack());
        vector<int> MonsterStatus(m.size(), 1);
        MonsterStatus[index] = 3;
        SpriteManager::SetMonsterStatus(MonsterStatus);
        if (target != nullptr && target->getHealth() <= 0)
        {
            LogSystem::KillMonster(target);
            MonsterStatus = vector<int>(m.size(), 1);
            MonsterStatus[index] = 0;
            SpriteManager::SetMonsterStatus(MonsterStatus);
            killedMonster.push_back(target);

            target = nullptr;
        }
    }
    // 3 Turn use skill
    else if (turnCount % 3 == 0)
    {
        Job* playerJob = GameManager::GetInstance().getPlayerJob();
        int skillDamage = playerJob->SkillDamage(c);
        
        // Skill All monster attack
        LogSystem::UseSkill(target, playerJob->SkillName(), skillDamage);
        vector<int> MonsterStatus(m.size(), 3);
        SpriteManager::SetMonsterStatus(MonsterStatus);
        MonsterStatus = vector<int>(m.size(), 1);
        int i = 0; //monster sprite index
        for (auto& monsters : m)
        {
            if (monsters->getHealth() > 0)
            {
                // Job Damage
                monsters->takeDamage(skillDamage);
                // if Kill monster
                if (monsters->getHealth() <= 0){
                    killedMonster.push_back(monsters);
                    MonsterStatus[i] = 0;
                }
            }
            i++;
        }
        SpriteManager::SetMonsterStatus(MonsterStatus);
        
    }
    // if kill monsters message
    if (!killedMonster.empty())
    {
        for (auto& killMonster : killedMonster)
        {
            LogSystem::KillMonster(killMonster);
        }
    }
    return true;
}

void BattleManager::MonstersTurn(std::vector<Monster*>& m){
    int index = 0;
    for (auto monsters : m)
    {
        if (monsters->getHealth() > 0)
        {
            int monsterDamage = monsters->Attack(c.GetDefense());
            //if (c.GetDefense() > monsterDamage)
            //{
            //    LogSystem::AttackPlayer(monsters, 0);

            //    //handle sprites
            //    vector<int> MonsterStatus(m.size(), 1);
            //    MonsterStatus[index] = 2;
            //    SpriteManager::SetMonsterStatus(MonsterStatus);
            //    
            //    // Miss message
            //    stringstream SS;
            //    SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
            //    << " Your high defense blocked the attack!! ";
            //    LogSystem::PrintStringsOnLog({SS.str()});
            //    
            //} 
            if (monsterDamage==0)
            {
                LogSystem::AttackPlayer(monsters, 0);

                //handle sprites
                vector<int> MonsterStatus(m.size(), 1);
                MonsterStatus[index] = 2;
                SpriteManager::SetMonsterStatus(MonsterStatus);

                // Miss message
                stringstream SS;
                SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT
                    << " Your high defense blocked the attack!! ";
                LogSystem::PrintStringsOnLog({ SS.str() });

            }
            else
            {
                int resultDamage = monsterDamage;
                c.SetHP(c.GetHP() - resultDamage);
                LogSystem::AttackPlayer(monsters, resultDamage);

                //handle sprites
                vector<int> MonsterStatus(m.size(), 1);
                MonsterStatus[index] = 2;
                SpriteManager::SetMonsterStatus(MonsterStatus);
            }
        }
        index++;
    }
}

void BattleManager::ApplyDiceResult(DiceResult result){
    LogSystem::RollDice(result.diceNum);
    
    // Dice description
    vector<string> Input = {};
    stringstream SS;
    SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " \"" << result.description << "\"";
    Input.push_back(SS.str());
    if (result.hpDelta != 0)
    {
        c.SetMaxHP(c.GetMaxHP() + result.hpDelta);
        
        // + Max hp message
        SS.str("");
        SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " Player hp add : " << result.hpDelta << ", Player Max hp : " << c.GetMaxHP();
        Input.push_back(SS.str());
    }
    if (result.atkDelta != 0)
    {

        c.SetAttack(c.GetAttack() + result.atkDelta);
        
        // + Character Attack Message
        SS.str("");
        SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " Player attack add : " << result.atkDelta << ", Player Atk : " << c.GetAttack();
        Input.push_back(SS.str());
    }
    if (result.missChance != 0) 
    { 
        
        // + Miss Chance message
        SS.str("");
        SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " Player miss Chance -" << result.missChance;
        Input.push_back(SS.str());
        
    }
    LogSystem::PrintStringsOnLog(Input);
}

void BattleManager::UsePotionToPer(float perHP){
    // Check Player MAX HP 30 %
    int playerHP = c.GetHP();
    int playerMaxHP = c.GetMaxHP();
    Inventory* inv = GameManager::GetInstance().getInventory();
    std::vector<Item>& findItem = GameManager::GetInstance().getInventory()->GetOwnedItems();
    
    if (playerHP <= playerMaxHP * perHP)
    {
        for (auto it = findItem.begin(); it < findItem.end(); ++it)
        {
            if (it->id == 301 || it->id == 302)
            {
                vector<string> Input = {};
                stringstream SS;
                // HP 40% message
                SS << TextFormat::RED 
                << "[System] " << c.GetName() << " HP is Only " << perHP * 100 << "% !!!!" 
                << TextFormat::DEFAULT;
                Input.push_back(SS.str());

                SS.str("");
                SS << "[System] " << c.GetName() << " HP : " << playerHP;
                Input.push_back(SS.str());

                inv->UseItem(302);
                SS.str("");
                std::cout << "[System] " << c.GetName() << " HP : " << c.GetHP() << std::endl;
                Input.push_back(SS.str());
                LogSystem::PrintStringsOnLog(Input);
                return; 
            }
        }
    }
}

void BattleManager::StartBossBattle(){
    bool isWin = 0;
    int bossTurn = 1;

    Monster* boss = BattleSupply::GetInstance().SpawnBoss();
    stringstream SS;
    SpriteManager::SetMonsterGroup({ "Boss" });

    while(c.GetHP() >  0){
        SS.str("");
        SS << "[System] Turn Count : " << bossTurn;
        LogSystem::PrintStringsOnLog({ SS.str() });
        
        UsePotionToPer(0.4f);
        
        // player turn
        if (bossTurn % 3 != 0)
        {
            boss->takeDamage(c.GetAttack());
            LogSystem::AttackMonster(boss, c.GetAttack());
            SpriteManager::SetMonsterStatus({ 3 });
        }
        // Player use skill
        else if (bossTurn % 3 == 0)
        {
            Job* playerJob = GameManager::GetInstance().getPlayerJob();
            int skillDamage = playerJob->SkillDamage(c);
            boss->takeDamage(skillDamage);
            LogSystem::AttackMonster(boss, skillDamage);
            SpriteManager::SetMonsterStatus({ 3 });
        }
        
        // Check alive boss
        if (boss->getHealth() <= 0)
        {
            isWin = 1;
            break;
        }
        
        // boss turn
        if (bossTurn % 3 != 0)
        {
            boss->SetStrategy(std::make_unique<NormalAttack>());
            int bossDamage = boss->getAttack();
            if (c.GetDefense() > bossDamage)
            {
                LogSystem::AttackPlayer(boss, 0);
                SpriteManager::SetMonsterStatus({ 2 });
                SS.str("");
                SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
                << " Your high defense blocked the attack!! ";
                LogSystem::PrintStringsOnLog({ SS.str() });
            }   
            else
            {
                int resultDamage = bossDamage - c.GetDefense();
                c.SetHP(c.GetHP() - resultDamage);
                LogSystem::AttackPlayer(boss, resultDamage);
                SpriteManager::SetMonsterStatus({ 2 });
            }
        }
        // boss skill
        else if (bossTurn % 3 == 0)
        {
            boss->SetStrategy(std::make_unique<SpecialAttack>());
            int bossSkillDamage = boss->getAttack();
            if (c.GetDefense() > bossSkillDamage)
            {
                LogSystem::AttackPlayer(boss, 0);
                SpriteManager::SetMonsterStatus({ 2 });
                
                SS.str("");
                SS << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
                << " Your high defense blocked the attack!! ";
                LogSystem::PrintStringsOnLog({ SS.str() });
            }   
            else
            {
                int resultDamage = bossSkillDamage - c.GetDefense();
                
                // useSKill Log
                vector<string> Input;
                Input.push_back(">>> The BOSS casts a skill!");
                SS.str("");
                SS << "-> " << TextFormat::MAGENTA << "Feel my power!" << TextFormat::DEFAULT << "!" << std::endl;
                Input.push_back(SS.str());
                SS.str("");
                SS << "-> The Player has taken " << resultDamage << " damage!" << std::endl;
                Input.push_back(SS.str());
                LogSystem::PrintStringsOnLog(Input);
                SpriteManager::SetMonsterStatus({ 2 });
                
                c.SetHP(c.GetHP() - resultDamage);
            }
        }
        ++bossTurn;
    }
    
    // Check isWin
    if (isWin)
    {
        SpriteManager::SetMonsterStatus({ 0 });
        GameManager::GetInstance().setGameClear();
    }
}


