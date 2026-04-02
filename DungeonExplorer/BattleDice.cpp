// BattleDice.cpp 
#include "BattleDice.h"
#include "RandomManager.h"

BattleDice::BattleDice(){
    // 1 Very Bad
    eventTable[1] = {
        {"You fall down! The enemy hits you hard.", -20, -5, 30}, 
        {"You are so tired. Your arms feel heavy.", -15, -7, 20}, 
        {"You are scared. You cannot move well.", -25, -3, 15}
    };
    // 2 Bad
    eventTable[2] = {
        {"Dust gets in your eyes. It hurts.", -5, -2, 10},
        {"The ground is slippery. Watch your step.", -3, -4, 10},
        {"Your hand shakes. The sword is dull.", -7, -1, 10}
    };
    // 3 Normal
    eventTable[3] = {
        {"You take a deep breath. Stay calm.", -1, 0, 5},
        {"You wait for the right moment.", 0, -1, 5},
        {"The battle goes on quietly.", -1, -1, 0}
    };
    // 4 Good
    eventTable[4] = {
        {"You find a good rhythm.", 1, 1, 0},
        {"You see a small gap in the enemy.", 2, 0, 0},
        {"Your focus is getting better.", 0, 2, 0}
    };
    // 5 Very Good
    eventTable[5] = {
        {"You feel strong! Energy flows in.", 5, 3, 0},
        {"You hit the enemy's weak point.", 3, 5, 0},
        {"Now you lead the battle.", 7, 2, 0}
    };
    // 6 Perfect
    eventTable[6] = {
        {"You are the master of this field.", 20, 10, 0}, 
        {"A perfect hit! You feel no pain.", 15, 15, 0},
        {"Your blade never misses today.", 25, 5, 0}
    };
    missTable[0] = "Bad luck! You missed.";
    missTable[1] = "Too slow! You missed.";
    missTable[2] = "Wow, that was a big miss!";
}

DiceResult BattleDice::Roll(){
    // Roll dice and random choice 3 event
    int dice = RandomManager::GetInstance().GetRange(1, 6);
    int sub = RandomManager::GetInstance().GetRange(0, 2);
    
    // diceNum update
    DiceResult result = eventTable[dice][sub];
    result.diceNum = dice;
    
    return result;
}

std::string BattleDice::missMessage(){
    int num = RandomManager::GetInstance().GetRange(0,2);
    
    return missTable[num];
}
