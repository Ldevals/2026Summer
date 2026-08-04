#include "CameraManager.h"

CameraManager* CameraManager::instance = nullptr;
sf::RenderTarget* CameraManager::window = nullptr;
//sf::RenderTarget* CameraManager::window = nullptr;

void CameraManager::CreateInstance(sf::RenderTarget* _window)
{
	if (!instance)
	{
		instance = new CameraManager();
	}
	window= _window;
}

CameraManager* CameraManager::GetInstance()
{
	return instance;
}

void CameraManager::SetTarget(sf::Vector2f* _target)
{
	target = _target;
}

void CameraManager::Update(float _dt)
{
	sf::View view(*target, sf::Vector2f(window->getSize()));
	window->setView(view);
}

sf::Vector2i CameraManager::GetScreenPos(sf::Vector2f _pos)
{
	return window->mapCoordsToPixel(_pos);
}

sf::Vector2f CameraManager::GetWorldPos(sf::Vector2i _pos)
{
	return window->mapPixelToCoords(_pos);
}
