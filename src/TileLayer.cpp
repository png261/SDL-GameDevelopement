#include "TileLayer.h"

#include "Game.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) 
    : m_tileSize(tileSize),m_tilesets(tilesets),  m_position(0,0), m_velocity(0,0)
{
    m_numColumns = (Game::Instance()->getGameWidth() / m_tileSize);
    m_numRows = (Game::Instance()->getGameHeight() / m_tileSize);
}

void TileLayer::update() {
    m_velocity.setX(0.01);
    m_position += m_velocity;
}

void TileLayer::render() {
    int x, y, x2, y2 = 0;
    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;

    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;
    

    for(int i = 0; i < m_numRows; i++) {
        for(int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i + y][j + x];
            if(id == 0) {
                continue;
            }

            Tileset tileset = getTilesetByID(id);

            TextureManager::Instance()->drawTile(tileset.name, 2, 2, (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, m_tileSize, (id - tileset.firstGridID) / tileset.numColumns, (id - tileset.firstGridID) % tileset.numColumns, Game::Instance()->getRenderer());
        }; 
    }
}

Tileset TileLayer::getTilesetByID(int tileID) { 
    for(int i = 0; i < m_tilesets.size() - 1; i++) {
        if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
            return m_tilesets[i];
        }
    }

    return m_tilesets.back();
}
