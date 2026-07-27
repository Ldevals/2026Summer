#include "common.h"
#include "Entity.h"

class EntityFactory
{
public:
	static void CreateInstance(std::vector<Entity*>& _entities);
	template <typename T, typename ...Args>
	Entity* CreateEntity(Args&&... args)
	{
		T* entity = new T(std::forward<Args>(args)...);
		m_entities.push_back(entity);
		return entity;
	}
	static EntityFactory* GetInstance()
	{
		return instance;
	}
private:
	EntityFactory(std::vector<Entity*>& _entities) :m_entities(_entities){};

	static EntityFactory* instance;
	std::string name;
	std::vector<Entity*>& m_entities;
};

