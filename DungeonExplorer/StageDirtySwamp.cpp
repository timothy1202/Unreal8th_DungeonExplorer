// StageDirtySwamp.cpp
#include "StageDirtySwamp.h"
#include "Character.h"
#include "RandomManager.h"
#include "LogSystem.h"
#include "GameManager.h"

StageDirtySwamp::StageDirtySwamp() : Stage(EStage::DIRTY_SWAMP){
    eventTable[1] = {"The mud is too deep. You can't move!", -10, -5}; 
    eventTable[2] = {"The smell is bad. You feel sick.", -5, -2};
    eventTable[3] = {};
    eventTable[4] = {"You found a dry path. It's easy to walk.", 0, 2};
    eventTable[5] = {"You hit the monster hiding in the mud!", 0, 5};
    eventTable[6] = {"The swamp is your home now. You feel strong!", 10, 10};
}

void StageDirtySwamp::EnterStage(){
    std::cout << TextFormat::GREEN << "========================================" << TextFormat::DEFAULT << std::endl;
    std::cout << " [ Stage : " << StageNames[EStage::DIRTY_SWAMP] << " ] " << std::endl;
    std::cout << " - Monster : Troll , Slime" << std::endl;
    // Enter Log
    std::cout << " - \"Sticky mud clings to your boots. Something is bubbling under the green water.\"" << std::endl; 
    
    // Enter event
    // Roll dice 1 ~ 6
    int rollResult = RandomManager::GetInstance().GetRange(1,6);
    StageEvent& event = eventTable[rollResult];
    LogSystem::RollDice(rollResult);
    
    Character* player = GameManager::GetInstance().getPlayer();
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
    std::cout << TextFormat::GREEN << "========================================" << TextFormat::DEFAULT << std::endl;
}

void StageDirtySwamp::RandomEvent(int chance){
    Character* player = GameManager::GetInstance().getPlayer();
    
    // chance % random event
    int eventChance = RandomManager::GetInstance().GetRange(1,100);
    if (eventChance <= chance)
    {
        StageEvent randomEvent[3] = {
            {"A huge bubble pops, and sticky mud covers your eyes!", -10, -5},
            {"Thorny vines under the water scratch your legs.", -5, -2},
            {"You found an old chest buried in the mud!", 10, 5}
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

