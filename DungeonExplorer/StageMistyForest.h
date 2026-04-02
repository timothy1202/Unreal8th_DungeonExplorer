// StageMistyForest.h
#pragma once
#include "Stage.h"

class StageMistyForest : public Stage{
public:
    StageMistyForest();
    
    void EnterStage() override;
    void RandomEvent(int chance) override;
};
