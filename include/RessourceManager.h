#include "common.h"



class RessourceManager
{
public:
	static void CreateInstance();
	static RessourceManager* GetInstance();

	sf::Texture* LoadTexture(std::string _path);

private:
	RessourceManager() {};

	static RessourceManager* instance;

	std::vector<std::unique_ptr<sf::Texture>> textures;
	std::vector<std::string> textureName;
	std::unordered_map<std::string,>
};