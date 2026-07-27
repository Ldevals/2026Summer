#include "EntityFactory.h"

EntityFactory* EntityFactory::instance = nullptr;

void EntityFactory::CreateInstance(std::vector<Entity*>& _entities)
{
	if (!instance)
	{
		instance = new EntityFactory(_entities);
	}
}
