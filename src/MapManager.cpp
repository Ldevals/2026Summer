#include "MapManager.h"
#include "EntityFactory.h"
#include "RessourceManager.h"

MapManager* MapManager::instance = nullptr;

void MapManager::CreateInstance()
{
	if (!instance)
	{
		instance = new MapManager;
	}
}

MapManager* MapManager::GetInstance()
{
	return instance;
}

void MapManager::GenerateMap(sf::Vector2i _size)
{
	// Build a single vertex array (tilemap) instead of creating one Entity per tile.
	m_size = _size;
	const int tileSize = 32;
	m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
	m_vertices.resize(_size.x * _size.y * 6);

	// Load tileset texture (same used by CellEntity)
	m_tileset = RessourceManager::GetInstance()->LoadTexture(RESOURCES_PATH "Tileset Grass.png");

    for (int x = 0; x < _size.x; ++x)
    {
        for (int y = 0; y < _size.y; ++y)
        {
            int tileNumber = std::rand() % 64;

            int tu = tileNumber % 8;
            int tv = tileNumber / 8;

            sf::Vertex* tri = &m_vertices[(x + y * _size.x) * 6];

            // Positions
            sf::Vector2f p0(x * tileSize, y * tileSize);
            sf::Vector2f p1((x + 1) * tileSize, y * tileSize);
            sf::Vector2f p2((x + 1) * tileSize, (y + 1) * tileSize);
            sf::Vector2f p3(x * tileSize, (y + 1) * tileSize);

            // Coordonnées de texture
            sf::Vector2f t0(tu * tileSize, tv * tileSize);
            sf::Vector2f t1((tu + 1) * tileSize, tv * tileSize);
            sf::Vector2f t2((tu + 1) * tileSize, (tv + 1) * tileSize);
            sf::Vector2f t3(tu * tileSize, (tv + 1) * tileSize);

            // Triangle 1
            tri[0].position = p0;
            tri[1].position = p1;
            tri[2].position = p2;

            tri[0].texCoords = t0;
            tri[1].texCoords = t1;
            tri[2].texCoords = t2;

            // Triangle 2
            tri[3].position = p0;
            tri[4].position = p2;
            tri[5].position = p3;

            tri[3].texCoords = t0;
            tri[4].texCoords = t2;
            tri[5].texCoords = t3;
        }
    }


}
void MapManager::Render(sf::RenderTarget& _rt)
{
	if (m_tileset && !m_vertices.getVertexCount()) return;
	if (m_tileset)
	{
		sf::RenderStates states;
		states.texture = m_tileset;
		_rt.draw(m_vertices, states);
	}
}
