#include "CameraManager.h"

CameraManager* CameraManager::instance = nullptr;

void CameraManager::CreateInstance(sf::RenderTarget* _window)
{
	if (!instance)
	{
		instance = new CameraManager();
	}
	CameraManager::window= _window;
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
