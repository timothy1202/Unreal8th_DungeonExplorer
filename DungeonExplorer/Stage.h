// Stage.h
#pragma once
#include <string>
#include <map>

enum EStage{
    NONE = -1,
    DARK_CAVE,
    DIRTY_SWAMP,
    MISTY_FOREST,
    STAGE_COUNT  // 3
};

static const std::string StageNames[EStage::STAGE_COUNT] = {"Dark Cave",
                                                            "Dirty Swamp",
                                                            "Misty Forest"
};

struct StageEvent {
    std::string description = "Nothing happened.";
    int hpDelta = 0;
    int atkDelta = 0;
};

class Stage{
protected:
    EStage type;
    std::map<int, StageEvent> eventTable;
public:
    Stage(EStage _type) : type(_type){}
    
    virtual void EnterStage() = 0;
    virtual void RandomEvent(int chance) = 0;
    virtual ~Stage() = default;
    
    EStage GetType() const { return type; }
};