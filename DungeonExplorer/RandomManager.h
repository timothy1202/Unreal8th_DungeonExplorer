// RandomManager.h
#pragma once
#include <random>

class RandomManager{
private:
    std::mt19937 gen;
    RandomManager(){
        std::random_device rd;
        gen.seed(rd());
    }

public:
    static RandomManager& GetInstance(){
        static RandomManager instance;
        return instance;
    }
    
    RandomManager(const RandomManager&) = delete;
    RandomManager operator=(const RandomManager&) = delete;
    
    int GetRange(int min, int max){
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }
    
    float GetRange(float min, float max){
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }
    
    void ShuffleVectorString(std::vector<std::string>& target){
        if (target.empty()) return; 
        std::shuffle(target.begin(), target.end(), gen);
    }
};