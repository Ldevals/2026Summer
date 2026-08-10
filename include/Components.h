#pragma once
#include "common.h"

enum ComponentType
{
	Graphic,
	Transform
};

enum HitboxType
{
	AllyDamageable, //pour les armes de melée
	EnemyDamageable, //pour les armes de melée
	AllyProjectile, // a supprimer dès la premiere collision
	EnemyProjectile,
	// a supprimer dès la premiere collision
	Body,
	Projectile
};

enum Team
{
	Ally,
	Enemy,
	Neutral
};


class Entity;
class Components
{
public:
	Components(Entity& _entity) : entity(_entity) {}
	virtual ~Components() = default;
	virtual void Update(float _deltaTime) {}
	virtual void Inputs(const std::vector<sf::Event>& _events, sf::Vector2i _mousePos) {}
	virtual void Render(sf::RenderTarget& _window) {}

	Entity& GetEntity() { return entity; }

private:
	Entity& entity;
};

class GraphicsComponent : public Components
{
public:
	GraphicsComponent(Entity& _entity, std::string _texturePath) : Components(_entity), texturePath(_texturePath)
	{
		Init(_texturePath);


	}
	void Init(std::string _texturePath);
	sf::Sprite* GetSprite();
	sf::Vector2f GetSpritePosition();

	void SetSpriteSize(sf::Vector2i _size);
	void SetPosition(sf::Vector2f _position);

	virtual void Render(sf::RenderTarget& _window) override;

private:
	std::string texturePath;
	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::Vector2i spriteSize;

};

class AnimationComponent : public Components
{
public:
	AnimationComponent(Entity& _entity, int _totalFrame) : Components(_entity), totalFrame(_totalFrame)
	{
		Init(_entity);
	}

	void Init(Entity& _entity);
	virtual void Update(float _dt) override;
private:
	sf::Sprite* sprite;
	sf::Vector2i spriteSize;
	int currentFrame;
	int totalFrame;
	float frameTime;
	float timer;
};

class ControllerComponent : public Components
{
public:
	ControllerComponent(Entity& _entity) : Components(_entity) { speed = 200; }

	virtual void Inputs(const std::vector<sf::Event>& _events, sf::Vector2i _mousePos) override;
	virtual void Update(float _dt) override;
private:
	sf::Vector2f direction;
	float speed;
};

class WeaponComponent : public Components
{
public:
	WeaponComponent(Entity& _entity, Entity* _owner) :Components(_entity)
	{
		Init(_entity);
		owner = _owner;
	}
	void Init(Entity& _entity);
	virtual void Update(float _dt) override;
	virtual void Inputs(const std::vector<sf::Event>& _events, sf::Vector2i _mousePos) override;
	float angleToCursor(sf::Vector2i _mousePos);
	//donner le paramètre en pointeur
private:
	Entity* owner;
	sf::Sprite* sprite;
	float offset;
	sf::Angle angle;

	float cooldown;

	bool isFlipped;
};

class DamageComponent : public Components
{
public:
	DamageComponent(Entity& _entity) :Components(_entity) {};
	void SetDamage(float _damage) { damage = _damage; };
	float GetDamage() { return damage; }
private:
	float damage;
};

class HitboxComponent : public Components
{
public:
	HitboxComponent(Entity& _entity, HitboxType _type,Team _team, bool _isStatic) :Components(_entity), 
		isStatic(_isStatic), type(_type), team(_team)
	{
		Init();
	};
	void Init();
	void AddHitbox(sf::Vector2f _size);
	void Move(sf::Vector2f _correction);
	void Update(float _dt) override;
	sf::FloatRect GetHitbox();
	void SetFriendlyColliding(bool _isColliding);
	bool GetFriendlyColliding();
	HitboxType GetType();
	Team GetTeam();
	bool GetStatic();
private:
	bool isSpriteHitbox;
	bool isStatic;
	bool isFriendlyColliding;
	HitboxType type;
	Team team;
};

class HealthComponent : public Components
{
public:
	HealthComponent(Entity& _entity, float _health) :Components(_entity), health(_health) ,hasCooldownDamage(false){};
	void Damage(float _damage);
	float GetHealth();
	void SetCooldownImunity(bool _hasCooldownDamage);
	void SetCooldownImunityTime(float _time);

	void Update(float _deltaTime) override;

private:
	float health;
	bool hasCooldownDamage;
	float imunityTime;
};

class ProjectileComponent : public Components
{
public:
	ProjectileComponent(Entity& _entity) : Components(_entity) {};
private:

};

class CellComponent : public Components
{
public:
	CellComponent(Entity& _entity) :Components(_entity) {}
	void Init();
private:

};