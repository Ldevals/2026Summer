#pragma once

#include "common.h"

class StageDirector
{
public:
	static void CreateInstance();
	static StageDirector* GetInstance();

	void Update(float _dt);
	void SetCreditMultiplier(float _multiplier);
private:
	StageDirector() {};

	static StageDirector* instance;

	float credit;
	float creditMultiplier;

	int enemySpawnCost = 5;
};