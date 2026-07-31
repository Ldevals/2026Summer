#include "common.h"
#include "Components.h"
#include "EventManager.h"



class Entity
{
public:
	Entity(std::string _name) : name(_name) {}

	virtual void Update(float _deltaTime) {}
	/*virtual void Input();
	virtual void Render(sf::RenderTarget& _window);*/


	void AddComponent(Components* _component);
	const std::vector<Components*>& GetComponents() const { return components; }

	template<typename T>
	T* GetComponent() const
	{
		for (Components* component : components)
			if (T* typedComponent = dynamic_cast<T*>(component))
				return typedComponent;
		return nullptr;
	}

	std::string name;
	bool isDead = false;
	bool isActive = true;
private:
	//sf::Texture texture;
	sf::Vector2f velocity;
 sf::Vector2f position;
 bool isCameraTarget = false;
	std::vector<Components*> components;
};

class ProjectileEntity : public Entity
{
public:
	ProjectileEntity(std::string _name, sf::Angle _angle, float _speed, sf::Vector2f _pos) : Entity(_name)
	{
		Init(_pos, _angle);
		speed = _speed;
		direction = sf::Vector2f(std::cos(_angle.asRadians()), std::sin(_angle.asRadians()));
	};
	void Init(sf::Vector2f _pos, sf::Angle _angle);

	void Update(float _deltaTime) override;
	void SetDirection(sf::Vector2f _direction);
	sf::Vector2f direction;
	float speed;
	float lifeTime;
	float damage;

};

class PlayerEntity : public Entity, public EventListener
{
public:
	PlayerEntity(std::string _name,sf::RenderTarget* _window) : Entity(_name), window(_window)
	{
		Init();
	}
	void Init();
	void Update(float _deltaTime) override;
	void OnEvent(Event _event) override;
	sf::Vector2f* GetPos();
private:
	sf::Vector2f pos;
	sf::RenderTarget* window;

};

class EnemyEntity : public Entity
{
public:
	EnemyEntity(std::string _name, sf::Vector2f* _playerPos) :Entity(_name), playerPos(_playerPos)
	{
		Init();
	}
	void Init();
	void Update(float _deltaTime) override;

private:
	sf::Vector2f* playerPos;
	float speed;

};
class CellEntity : public Entity
{
public:
	CellEntity(std::string _name, bool _hasCollider):Entity(_name)
	{
		Init(_hasCollider);
	}

private:
	void Init(bool _hasCollider);

};

class MainVehicleEntity : public Entity
{
public:
	MainVehicleEntity(std::string _name,sf::Vector2i _mapSize) :Entity(_name)
	{
		Init(_mapSize);
	}
	void Init(sf::Vector2i _mapSize);
	void Update(float _deltaTime) override;
private:
	float stopingPoint;
	float movingSpeed = 20;
	bool isStopped = false;
};