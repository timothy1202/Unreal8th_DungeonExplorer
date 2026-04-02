// StageDarkCave.h 
#pragma once
#include "Stage.h"

class StageDarkCave : public Stage{
public:
    StageDarkCave();
    
    void EnterStage() override;
    void RandomEvent(int chance) override;

};