#include "Entity.h"

void Entity::AddComponent(Components* _component)
{
	components.push_back(_component);
}

void ProjectileEntity::Init(sf::Vector2f _pos, sf::Angle _angle)
{
	GraphicsComponent* graph = new GraphicsComponent(*this, RESOURCES_PATH "bullet.png");
	AddComponent(graph);
	graph->GetSprite()->setPosition(_pos);
	graph->GetSprite()->setRotation(_angle);
	lifeTime = 5.0f;
	damage = 30;
	isActive = true;
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
	GraphicsComponent* graph = new GraphicsComponent(*this, RESOURCES_PATH "player_idle_01.png");
	AddComponent(graph);
	graph->SetSpriteSize(sf::Vector2i(192, 192));
	speed = 50;

	HitboxComponent* hitbox = new HitboxComponent(*this, false);
	AddComponent(hitbox);
	isActive = true;
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
	GraphicsComponent* graph = new GraphicsComponent(*this, RESOURCES_PATH "tree_01.png");
	graph->SetSpriteSize(sf::Vector2i(192, 256));
	AddComponent(graph);

	AnimationComponent* anim = new AnimationComponent(*this, 8);
	AddComponent(anim);

	ControllerComponent* controller = new ControllerComponent(*this);
	AddComponent(controller);

	HitboxComponent* hitbox = new HitboxComponent(*this, false);
	AddComponent(hitbox);

	Event event;
	event.eventType = EventType::VehicleHasArrived;
	EventManager::GetInstance()->AddListener(event, this);
	isActive = false;
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
		break;
	}

}

sf::Vector2f* PlayerEntity::GetPos()
{
	return &pos;
}

void CellEntity::Init(bool _hasCollider)
{
	GraphicsComponent* graph = new GraphicsComponent(*this, RESOURCES_PATH "Tileset Grass.png");

	graph->SetSpriteSize(sf::Vector2i(32, 32));

	sf::IntRect textureRect(sf::Vector2i(std::rand() % 8 * 32, std::rand() % 8 * 32), sf::Vector2i(32, 32));
	graph->GetSprite()->setTextureRect(textureRect);
	AddComponent(graph);
	if (_hasCollider)
	{
		//HitboxComponent* hitbox = new HitboxComponent(*this,false);
	}
	isActive = true;
}

void MainVehicleEntity::Init(sf::Vector2i _mapSize)
{
	int cellSize = 32;
	sf::Vector2f spawnPoint(_mapSize.x * cellSize / 2, _mapSize.y * cellSize);
	stopingPoint = spawnPoint.y / 2;
	GraphicsComponent* graph = new GraphicsComponent(*this, RESOURCES_PATH "vehicle.png");
	graph->GetSprite()->setPosition(spawnPoint);
	AddComponent(graph);
	HitboxComponent* hitbox = new HitboxComponent(*this, true);
	AddComponent(hitbox);
	movingSpeed = 20;
	isStopped = false;
	isActive = true;
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
		Event event;
		event.eventType = EventType::VehicleHasArrived;
		EventManager::GetInstance()->Broadcast(event);
	}
}
