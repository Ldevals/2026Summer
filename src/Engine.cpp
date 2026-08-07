#include "Engine.h"
#include "EntityFactory.h"
#include "HitboxManager.h"
#include "MapManager.h"
#include "RessourceManager.h"
#include "EventManager.h"
#include "CameraManager.h"

Engine* Engine::instance = nullptr;

bool Engine::CreateInstance()
{
	if (!instance)
	{
		instance = new Engine();
		return true;
	}
	else
	{
		return false;
	}
}

bool Engine::Initialize(sf::RenderTarget* _window)
{
	EntityFactory::CreateInstance(m_entities);
	HitboxManager::CreateInstance();
	MapManager::CreateInstance();
	RessourceManager::CreateInstance();
	EventManager::CreateInstance();
	CameraManager::CreateInstance(_window);

	MapManager::GetInstance()->GenerateMap({ 20,20 });

	// TODO create 1 "Player" entity and 2 "Mob" entities.
	// Use "player_idle_01.png" (you can find it in CreajeuxEngine/WorkingDirectory) for graphics.
	Entity* playerEntity = new PlayerEntity("player", _window);
	m_entities.push_back(playerEntity);

	Entity* weaponEntity = new Entity("playerWeapon");
	m_entities.push_back(weaponEntity);


	GraphicsComponent* weaponGraph = new GraphicsComponent(*weaponEntity, RESOURCES_PATH "gun.png");
	weaponEntity->AddComponent(weaponGraph);

	WeaponComponent* weapon = new WeaponComponent(*weaponEntity, playerEntity);
	weaponEntity->AddComponent(weapon);
	weaponEntity->isCameraTarget = false;

	MainVehicleEntity* vehicle = new MainVehicleEntity("forteress", { 20,20 });
	m_entities.push_back(vehicle);
	CameraManager::GetInstance()->SetTarget(&vehicle->position);

	return true;
}

void Engine::Inputs(const std::vector<sf::Event>& _events, sf::Vector2i _mousePos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		sf::Vector2f* playerPos;
		for (Entity* entity : m_entities)
		{
			if (PlayerEntity* player = dynamic_cast<PlayerEntity*>(entity))
			{
				// entity est bien un PlayerEntity
				playerPos = player->GetPos();
			}
		}
		EntityFactory::GetInstance()->CreateEntity<EnemyEntity>("Ennemy", playerPos);
	}
	// TODO entities process inputs
	for (Entity* entity : m_entities)
	{
		for (Components* component : entity->GetComponents())
		{
			component->Inputs(_events, _mousePos);

		}
	}
}

void Engine::Update(const float _deltaTime)
{
	// TODO update entities
	for (Entity* entity : m_entities)
	{
		if (entity->isActive)
		{
			//std::cout << entity->name << std::endl;
			entity->Update(_deltaTime);
			for (Components* component : entity->GetComponents())
			{
				component->Update(_deltaTime);
			}
		}
		if (entity->isCameraTarget)
		{
			entity->UpdateCameraTarget();
		}
	}

	HitboxManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update(_deltaTime);
	
	for (int i = 0; i < m_entities.size();i++)
	{
		if (m_entities[i]->isDead)
		{
			delete m_entities[i];
			m_entities.erase(m_entities.begin() + i);
		}
	}
}

void Engine::Render(sf::RenderTarget& _rt)
{
	// TODO render entities
	MapManager::GetInstance()->Render(_rt);
	for (Entity* entity : m_entities)
	{
		if (entity->isActive)
		{
			for (Components* component : entity->GetComponents())
			{
				component->Render(_rt);
			}
		}
	}
}

Engine* Engine::GetInstance()
{
	return instance;
}
