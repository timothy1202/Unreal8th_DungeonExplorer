// StageManager.cpp
#include "StageManager.h"
#include "StageDarkCave.h"
#include "StageDirtySwamp.h"
#include "StageMistyForest.h"
#include <iostream>



void StageManager::EnterStageEvent(){
    if (currentStage != nullptr)
    {
        currentStage->EnterStage();
    }
}

void StageManager::RunRandomEvent(int chance){
    if (currentStage != nullptr)
    {
        currentStage->RandomEvent(chance);
    }
    
}
    
void StageManager::SetStage(EStage stageType){
    switch (stageType)
    {
    case EStage::DARK_CAVE: 
        currentStage = std::make_unique<StageDarkCave>();
        EnterStageEvent();
        break; 
    case EStage::DIRTY_SWAMP:
        currentStage = std::make_unique<StageDirtySwamp>();
        EnterStageEvent();
        break;
    case EStage::MISTY_FOREST:
        currentStage = std::make_unique<StageMistyForest>();
        EnterStageEvent();
        break;
    }
}
EStage StageManager::GetCurrentStage(){
    if (currentStage != nullptr)
        return currentStage->GetType();
    return EStage::NONE;
}