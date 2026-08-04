//#include "Components.h"
//#include "Entity.h"
#include "EntityFactory.h"
#include "HitboxManager.h"
#include "Components.h"
#include "RessourceManager.h"
#include "CameraManager.h"
void GraphicsComponent::Init(std::string _texturePath)
{

	texture = RessourceManager::GetInstance()->LoadTexture(_texturePath);


	sprite = new sf::Sprite(*texture);

	SetSpriteSize(sf::Vector2i(texture->getSize()));
}
sf::Sprite* GraphicsComponent::GetSprite()
{
	return sprite;
}

sf::Vector2f GraphicsComponent::GetSpritePosition()
{
	return sprite->getPosition();
}

void GraphicsComponent::SetSpriteSize(sf::Vector2i _size)
{
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), _size));
	spriteSize = _size;
	sf::Vector2f origin(spriteSize.x / 2, spriteSize.y / 2);
	sprite->setOrigin(origin);
}

void GraphicsComponent::SetPosition(sf::Vector2f _position)
{
	sprite->setPosition(_position);
}

void GraphicsComponent::Render(sf::RenderTarget& _window)
{

	sf::View view = _window.getView();

	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	sf::FloatRect visibleArea(
		center - size / 2.f,
		size
	);
	if (visibleArea.findIntersection(sprite->getGlobalBounds()))
	{
		_window.draw(*sprite);
	}
}

void AnimationComponent::Init(Entity& _entity)
{
	GraphicsComponent* temp = _entity.GetComponent<GraphicsComponent>();
	if (!temp)
	{
		std::cerr << "AnimationComponent::Init: GraphicsComponent introuvable pour l'entité " << _entity.name << std::endl;
		return;
	}
	sprite = temp->GetSprite();
	spriteSize = sprite->getTextureRect().size;
	frameTime = 0.05f;
	timer = 0.0f;
}

void AnimationComponent::Update(float _dt)
{
	timer += _dt;
	if (timer >= frameTime)
	{
		sf::IntRect newRect(sprite->getTextureRect().position, spriteSize);
		newRect.position.x += spriteSize.x;
		if (newRect.position.x >= sprite->getTexture().getSize().x)
			newRect.position.x = 0;

		sprite->setTextureRect(newRect);
		timer = 0;
	}
}

void ControllerComponent::Inputs(const std::vector<sf::Event>& _events, sf::Vector2i _mousePos)
{
	direction = { 0, 0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) direction += sf::Vector2f(0, -1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction += sf::Vector2f(0, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) direction += sf::Vector2f(-1, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction += sf::Vector2f(1, 0);

	const float directionLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (directionLength > 0.f)
		direction /= directionLength;
}

void ControllerComponent::Update(float _dt)
{
	GraphicsComponent* temp = GetEntity().GetComponent<GraphicsComponent>();
	sf::Vector2f pos = temp->GetSprite()->getPosition();
	temp->GetSprite()->setPosition(pos + speed * _dt * direction);
}

void WeaponComponent::Init(Entity& _entity)
{
	GraphicsComponent* temp = _entity.GetComponent<GraphicsComponent>();
	if (temp != nullptr)
	{
		sprite = temp->GetSprite();

	}
	else
	{
		std::cout << "couldnt find weapon sprite" << std::endl;
	}
	offset = 64;
	cooldown = 0.0f;
	sprite->setOrigin(sf::Vector2f(-offset, 0));


}

void WeaponComponent::Update(float _dt)
{
	sprite->setPosition(owner->GetComponent<GraphicsComponent>()->GetSpritePosition());
	if (cooldown > 0)
	{
		cooldown -= _dt;
	}
}

void WeaponComponent::Inputs(const std::vector<sf::Event>& _events, sf::Vector2i _mousePos)
{
	sf::Vector2f mouseWorldPos = CameraManager::GetInstance()->GetWorldPos(_mousePos);
	angle = sf::radians(angleToCursor(sf::Vector2i(mouseWorldPos))).wrapUnsigned();
	sprite->setRotation(angle);
	if (angle.asDegrees() > 90 && angle.asDegrees() < 270)
	{
		isFlipped = false;
	}
	else
	{
		isFlipped = true;

	}

	sprite->setScale(sf::Vector2f(1, -1 + isFlipped * 2));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (cooldown <= 0.0f)
		{
			sf::Vector2f direction(std::cos(angle.asRadians()), std::sin(angle.asRadians()));
			sf::Vector2f spriteSize(sprite->getTexture().getSize().x + offset, 15);



			EntityFactory::GetInstance()->CreateEntity<ProjectileEntity>("bullet", angle, 100,
				sprite->getPosition() + sf::Vector2f(spriteSize.x * direction.x, spriteSize.x * direction.y + spriteSize.y));
			cooldown = 0.2f;
		}
	}
}

float WeaponComponent::angleToCursor(sf::Vector2i _mousePos)
{

	return atan2f(_mousePos.y - sprite->getPosition().y, _mousePos.x - sprite->getPosition().x);
}

void HitboxComponent::Init()
{
	isSpriteHitbox = true;
	HitboxManager::GetInstance()->AddHitbox(this);
 isFriendlyColliding =true;
}

void HitboxComponent::Move(sf::Vector2f _correction)
{
	if (isSpriteHitbox)
	{
		GetEntity().GetComponent<GraphicsComponent>()->GetSprite()->move(_correction);
	}
}

void HitboxComponent::Update(float _dt)
{

}

sf::FloatRect HitboxComponent::GetHitbox()
{
	if (isSpriteHitbox)
	{
		return GetEntity().GetComponent<GraphicsComponent>()->GetSprite()->getGlobalBounds();
	}

	return sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f));
}

void HitboxComponent::SetFriendlyColliding(bool _isColliding)
{
	isFriendlyColliding = _isColliding;
}

bool HitboxComponent::GetFriendlyColliding()
{
	return isFriendlyColliding;
}

HitboxType HitboxComponent::GetType()
{
	return type;
}

bool HitboxComponent::GetStatic()
{
	return isStatic;
}

void HealthComponent::Damage(float _damage)
{
	health -= _damage;
	if (health <= 0.0f)
	{
		GetEntity().isDead = true;
	}
}


float HealthComponent::GetHealth()
{
 return health;
}
