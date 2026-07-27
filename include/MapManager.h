#include "common.h"


class MapManager
{
public:
	static void CreateInstance();
	static MapManager* GetInstance();
	void GenerateMap(sf::Vector2i _size);
	void Render(sf::RenderTarget& _rt);
private:
	MapManager() {};
	static MapManager* instance;
	sf::VertexArray m_vertices;
	sf::Texture* m_tileset = nullptr;
	sf::Vector2i m_size{0,0};
};