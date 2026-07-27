#pragma once
#include "common.h"

class Entity;
class Player;

class Engine
{
public:
	static bool CreateInstance();
	bool Initialize(sf::RenderTarget* _window);

	void Inputs(const std::vector<sf::Event>& _events, sf::Vector2i _mousePos);
	void Update(const float _deltaTime);
	void Render(sf::RenderTarget& _rt);

	const std::vector<Entity*>& GetEntities() const { return m_entities; }
	static Engine* GetInstance();


private:
	Engine() {};
	static Engine* instance;
	std::vector<Entity*> m_entities;
};
