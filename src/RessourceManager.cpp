#include "RessourceManager.h"

RessourceManager* RessourceManager::instance = nullptr;

void RessourceManager::CreateInstance()
{
	if (!instance)
	{
		instance = new RessourceManager();
	}
}

RessourceManager* RessourceManager::GetInstance()
{
	return instance;
}

sf::Texture* RessourceManager::LoadTexture(std::string _path)
{
	for (int i = 0;i != textureName.size();i++)
	{
		if (textureName[i] == _path)
		{
			return textures[i].get();
		}
	}
	std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();;
	if (!tempTexture->loadFromFile(_path))
	{
		std::cout << "failed to load texture:" << _path << std::endl;
	}
	textures.push_back(std::move(tempTexture));
	tempTexture = nullptr;
	textureName.push_back(_path);
	return textures.back().get();
}
