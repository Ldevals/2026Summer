#include "Entity.h"
#include "CameraManager.h"
//void Entity::AddComponent(Components* _component)
//{
//	components.push_back(_component);
//}

void Entity::UpdateCameraTarget()
{
	if (isCameraTarget)
	{
		position = GetComponent<GraphicsComponent>()->GetSprite()->getPosition();
	}
}

void ProjectileEntity::Init(sf::Vector2f _pos, sf::Angle _angle)
{
	GraphicsComponent* graph = AddComponent<GraphicsComponent>(/**this,*/ RESOURCES_PATH "bullet.png");
	//AddComponent(graph);
	HitboxComponent* hitbox = AddComponent<HitboxComponent>(/**this*/ HitboxType::Projectile, Team::Ally, false);
	//AddComponent(hitbox);
	DamageComponent* damage = AddComponent<DamageComponent>(/**this*/);
	damage->SetDamage(30);
	//AddComponent(damage);
	graph->GetSprite()->setPosition(_pos);
	graph->GetSprite()->setRotation(_angle);
	lifeTime = 5.0f;
	ProjectileEntity::damage = 30;
	isActive = true;
	isCameraTarget = false;
}

void ProjectileEntity::Update(float _deltaTime)
{
	sf::Sprite* sprite = GetComponent<GraphicsComponent>()->GetSprite();
	sprite->move(direction * speed * _deltaTime);
	lifeTime -= _deltaTime;
	if (lifeTime <= 0)
	{
		isDead = true;

	}
}

void ProjectileEntity::SetDirection(sf::Vector2f _direction)
{
	direction = _direction;
}

void EnemyEntity::Init()
{
	GraphicsComponent* graph = AddComponent<GraphicsComponent>(/**this,*/ RESOURCES_PATH "player_idle_01.png");
	//AddComponent(graph);
	graph->SetSpriteSize(sf::Vector2i(192, 192));
	speed = 50;

	HitboxComponent* hitbox = AddComponent<HitboxComponent>(/**this,*/ HitboxType::Body, Team::Enemy, false);
	//AddComponent(hitbox);

	HealthComponent* health = AddComponent<HealthComponent>(/**this,*/ 100.0f);
	//AddComponent(health);

	DamageComponent* damage = AddComponent<DamageComponent>(/**this*/);
	damage->SetDamage(30);
	//AddComponent(damage);
	isActive = true;
	isCameraTarget = false;

}

void EnemyEntity::Update(float _deltaTime)
{
	sf::Sprite* sprite = GetComponent<GraphicsComponent>()->GetSprite();

	sf::Vector2f direction(playerPos->x - sprite->getPosition().x, playerPos->y - sprite->getPosition().y);
	float length = std::sqrt(
		direction.x * direction.x +
		direction.y * direction.y
	);

	if (length > 0.f)
	{
		direction /= length;
	}
	else
	{
		direction *= 0.0f;
	}

	sprite->move(direction * speed * _deltaTime);
}

void PlayerEntity::Init()
{
	std::cout << "initPLayer" << std::endl;
	GraphicsComponent* graph = AddComponent<GraphicsComponent>(/**this*/ RESOURCES_PATH "tree_01.png");
	graph->SetSpriteSize(sf::Vector2i(192, 256));
	//AddComponent(graph);

	AnimationComponent* anim = AddComponent<AnimationComponent>(/**this*/ 8);
	//AddComponent(anim);

	ControllerComponent* controller = AddComponent<ControllerComponent>(/**this*/);
	//AddComponent(controller);

	HitboxComponent* hitbox = AddComponent<HitboxComponent>(/**this*/ HitboxType::Body, Team::Ally, false);
	//AddComponent(hitbox);

	HealthComponent* health = AddComponent<HealthComponent>(/**this,*/ 100);
	health->SetCooldownImunity(true);
	health->SetCooldownImunityTime(1.0f);
	//AddComponent(health);

	Event event;
	event.eventType = EventType::VehicleHasArrived;
	EventManager::GetInstance()->AddListener(event, this);
	isActive = false;
	isCameraTarget = false;
}

void PlayerEntity::Update(float _deltaTime)
{
	pos = GetComponent<GraphicsComponent>()->GetSprite()->getPosition();

	sf::View view(pos, sf::Vector2f(window->getSize()));
	window->setView(view);
}

void PlayerEntity::OnEvent(Event _event)
{
	switch (_event.eventType)
	{
	case EventType::VehicleHasArrived:
		isActive = true;
		isCameraTarget = true;
		GetComponent<GraphicsComponent>()->GetSprite()->setPosition({ _event.position.x - 50,_event.position.y });
		CameraManager::GetInstance()->SetTarget(&position);
		break;
	}

}

sf::Vector2f* PlayerEntity::GetPos()
{
	return &pos;
}

void CellEntity::Init(bool _hasCollider)
{
	GraphicsComponent* graph = AddComponent<GraphicsComponent>(/**this,*/ RESOURCES_PATH "Tileset Grass.png");

	graph->SetSpriteSize(sf::Vector2i(32, 32));

	sf::IntRect textureRect(sf::Vector2i(std::rand() % 8 * 32, std::rand() % 8 * 32), sf::Vector2i(32, 32));
	graph->GetSprite()->setTextureRect(textureRect);
	//AddComponent(graph);
	if (_hasCollider)
	{
		//HitboxComponent* hitbox = new HitboxComponent(*this,false);
	}
	isActive = true;
	isCameraTarget = false;

}

void MainVehicleEntity::Init(sf::Vector2i _mapSize)
{
	int cellSize = 32;
	sf::Vector2f spawnPoint(_mapSize.x * cellSize / 2, _mapSize.y * cellSize);
	stopingPoint = spawnPoint.y / 2;
	GraphicsComponent* graph = AddComponent<GraphicsComponent>(/**this,*/ RESOURCES_PATH "vehicle.png");
	graph->GetSprite()->setPosition(spawnPoint);
	//AddComponent(graph);
	HitboxComponent* hitbox = AddComponent<HitboxComponent>( HitboxType::Body, Team::Ally, true);

	HealthComponent* health = AddComponent<HealthComponent>(1000);
	health->SetCooldownImunity(true);
	health->SetCooldownImunityTime(1.0f);
	//AddComponent(hitbox);
	movingSpeed = 100;
	isStopped = false;
	isActive = true;
	isCameraTarget = true;
}

void MainVehicleEntity::Update(float _deltaTime)
{
	if (GetComponent<GraphicsComponent>()->GetSprite()->getPosition().y > stopingPoint)
	{
		GetComponent<GraphicsComponent>()->GetSprite()->move({ 0,-movingSpeed * _deltaTime });
	}
	else if (!isStopped)
	{
		isStopped = true;
		isCameraTarget = false;
		Event event;
		event.eventType = EventType::VehicleHasArrived;
		event.position = GetComponent<GraphicsComponent>()->GetSprite()->getPosition();
		EventManager::GetInstance()->Broadcast(event);
	}
}
