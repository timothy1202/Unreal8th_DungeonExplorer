#pragma once
#include <random>
class MakeRandom {
public:
	static inline std::mt19937& getGenerator() {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		return gen;
	}

};