// StageMistyForest.cpp
#include "StageMistyForest.h"
#include "Character.h"
#include "RandomManager.h"
#include "LogSystem.h"
#include "GameManager.h"

StageMistyForest::StageMistyForest() : Stage(EStage::MISTY_FOREST){
    eventTable[1] = {"The mist is too thick. You are lost and scared.", -10, -5};
    eventTable[2] = {"The cold mist freezes your body. You feel slow.", -5, -2};
    eventTable[3] = {};
    eventTable[4] = {"The wind blows the mist away. You see the path!", 0, 2};
    eventTable[5] = {"You attacked the enemy through the white mist!", 0, 5};
    eventTable[6] = {"The mist heals your wounds. You feel pure power!", 10, 10};
}

void StageMistyForest::EnterStage(){
    std::cout << TextFormat::GREEN << "========================================" << TextFormat::DEFAULT << std::endl;
    std::cout << " [ Stage : " << StageNames[EStage::MISTY_FOREST] << " ] " << std::endl;
    std::cout << " - Monster : Goblin , Orc, Troll , Slime" << std::endl;
    // Enter Log
    std::cout << " - \"Your footsteps break the heavy silence deep inside the cave. Something is moving.\"" << std::endl; 
    
    // Enter event
    // Roll dice 1 ~ 6
    int rollResult = RandomManager::GetInstance().GetRange(1,6);
    StageEvent& event = eventTable[rollResult];
    LogSystem::RollDice(rollResult);
    
    Character* player = GameManager::GetInstance().getPlayer();
    std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " \"" << event.description << "\"\n";
    // Player HP setting
    if (event.hpDelta != 0)
    {
        int plusHP = player->GetMaxHP() + event.hpDelta;
        int beforeHP = player->GetMaxHP();
            
        player->SetMaxHP(plusHP); 
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " " << player->GetName() << " Max Hp add " << event.hpDelta << std::endl;
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " " << player->GetName() << " Max HP change. " << beforeHP << " -> " << player->GetMaxHP() << std::endl;
    }
    // Player atk setting
    if (event.atkDelta != 0)
    {
        int plusAtk = player->GetAttack() + event.atkDelta;
        int beforeAtk = player->GetAttack();
            
        player->SetAttack(plusAtk);
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " " << player->GetName() << " Attack add " << event.atkDelta << std::endl;
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " " << player->GetName() << " Attack change. " << beforeAtk << " -> " << player->GetAttack() << std::endl;
    }
    std::cout << TextFormat::GREEN << "========================================" << TextFormat::DEFAULT << std::endl;
}

void StageMistyForest::RandomEvent(int chance){
    Character* player = GameManager::GetInstance().getPlayer();
    
    // chance % random event
    int eventChance = RandomManager::GetInstance().GetRange(1,100);
    if (eventChance <= chance)
    {
        StageEvent randomEvent[3] = {
            {"You slipped on a wet rock and fell down a hill!", -10, -5},
            {"A heavy branch fell from the mist and hit your head.", -5, -3},
            {"You found a glowing herb through the thick mist.", 5, 10}
        };
        StageEvent event = randomEvent[ RandomManager::GetInstance().GetRange(0,2)];
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " \"" << event.description << "\"\n";
        if (event.hpDelta != 0)
        {
            int plusHP = player->GetMaxHP() + event.hpDelta;
            int beforeHP = player->GetMaxHP();
            
            player->SetMaxHP(plusHP); 
            std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
            << " " << player->GetName() << " Max Hp add " << event.hpDelta << std::endl;
            std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
            << " " << player->GetName() << " Max HP change. " << beforeHP << " -> " << player->GetMaxHP() << std::endl;
        }
        // Player atk setting
        if (event.atkDelta != 0)
        {
            int plusAtk = player->GetAttack() + event.atkDelta;
            int beforeAtk = player->GetAttack();
            
            player->SetAttack(plusAtk);
            std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
            << " " << player->GetName() << " Attack add " << event.atkDelta << std::endl;
            std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
            << " " << player->GetName() << " Attack change. " << beforeAtk << " -> " << player->GetAttack() << std::endl;
        }
    }
}