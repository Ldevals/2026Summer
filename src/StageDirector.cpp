#include "StageDirector.h"
#include "EntityFactory.h"

StageDirector* StageDirector::instance = nullptr;

void StageDirector::CreateInstance()
{
	if (!instance)
		instance = new StageDirector();
}

StageDirector* StageDirector::GetInstance()
{
	return instance;
}

void StageDirector::Update(float _dt)
{
	credit += _dt * creditMultiplier;

	if (credit >= enemySpawnCost * 5)
	{
	//EntityFactory::GetInstance()->CreateEntity(EnemyEntity)
		EntityFactory::GetInstance()->CreateEntity<EnemyEntity>("Ennemy", playerPos);

	}
}

void StageDirector::SetCreditMultiplier(float _multiplier)
{
	creditMultiplier = _multiplier;
}
