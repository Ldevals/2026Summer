#pragma once
#include "common.h"


class CameraManager
{
public:
	static void CreateInstance(sf::RenderTarget* _window);
	static CameraManager* GetInstance();
	
	void SetTarget(sf::Vector2f* _target);
	void Update(float _dt);

	sf::Vector2i GetScreenPos(sf::Vector2f _pos);
	sf::Vector2f GetWorldPos(sf::Vector2i _pos);
	void GetWorldPos(sf::Vector2f _pos);
private:
	CameraManager() {};

	static CameraManager* instance;
	sf::Vector2f* target;
	static sf::RenderTarget* window;
};