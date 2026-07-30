#include "common.h"


class CameraManager
{
public:
	static void CreateInstance(sf::RenderTarget* _window);
	static CameraManager* GetInstance();
	
	void SetTarget(sf::Vector2f* _target);
	void Update(float _dt);
private:
	CameraManager() {};

	static CameraManager* instance;
	sf::Vector2f* target;
	sf::RenderTarget* window;
};