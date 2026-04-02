// StageDirtySwamp.h 
#pragma once
#include "Stage.h"

class StageDirtySwamp : public Stage{
public:
    StageDirtySwamp();
    
    void EnterStage() override;
    void RandomEvent(int chance) override;
};
