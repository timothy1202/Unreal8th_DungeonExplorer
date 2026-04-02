// StageManager.h 
#pragma once
#include <memory>
#include "Stage.h"

class StageManager{
private:
    std::unique_ptr<Stage> currentStage;
    StageManager() = default;

public:
    static StageManager& GetInstance(){
        static StageManager instance;
        return instance;
    }
    
    StageManager(const StageManager&) = delete;
    StageManager operator=(const StageManager&) = delete;
    
    void EnterStageEvent();
    void RunRandomEvent(int chance);
    
    void SetStage(EStage stageType);
    EStage GetCurrentStage();
};