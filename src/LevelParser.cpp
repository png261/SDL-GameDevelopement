#include "LevelParser.h"

#include "Game.h"
#include "GameObjectFactory.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "TextureManager.h"
#include "TileLayer.h"

using namespace tinyxml2;

Level *LevelParser::parseLevel(const char *levelFile) {
    XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    Level *pLevel = new Level();
    XMLElement *pRoot = levelDocument.RootElement();

    m_tileSize = atoi(pRoot->Attribute("tilewidth"));
    m_width = atoi(pRoot->Attribute("width"));
    m_height = atoi(pRoot->Attribute("height"));

    for (XMLElement *e = pRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement *pPropertyElement = e->FirstChildElement();
                 pPropertyElement != NULL;
                 pPropertyElement = pPropertyElement->NextSiblingElement()) {
                if (pPropertyElement->Value() == std::string("property")) {
                    parseTextures(pPropertyElement);
                }
            }
        }
    }

    for (XMLElement *e = pRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    for (XMLElement *e = pRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("objectgroup") ||
            e->Value() == std::string("layer")) {
            if (e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, pLevel->getLayers());
            } else if (e->FirstChildElement()->Value() == std::string("data")) {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
            }
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement *pTilesetRoot,
                                std::vector<Tileset> *pTilesets) {
    XMLDocument tilesetDocument;
    tilesetDocument.LoadFile(
        (std::string("assets/") + pTilesetRoot->Attribute("source")).c_str());

    XMLElement *pTilesetEl = tilesetDocument.RootElement();
    XMLElement *pImagieEl = pTilesetEl->FirstChildElement();
    TextureManager::Instance()->load(
        (std::string("assets/") + pImagieEl->Attribute("source")),
        pTilesetEl->Attribute("name"), Game::Instance()->getRenderer());

    Tileset tileset;
    tileset.firstGridID = atoi(pTilesetRoot->Attribute("firstgid"));
    tileset.width = atoi(pImagieEl->Attribute("width"));
    tileset.height = atoi(pImagieEl->Attribute("height"));
    tileset.tileWidth = atoi(pTilesetEl->Attribute("tilewidth"));
    tileset.tileHeight = atoi(pTilesetEl->Attribute("tileheight"));
    tileset.spacing = atoi(pTilesetEl->Attribute("spacing"));
    tileset.margin = atoi(pTilesetEl->Attribute("margin"));
    tileset.name = pTilesetEl->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement *pTileElement,
                                 std::vector<Layer *> *pLayers,
                                 const std::vector<Tileset> *pTilesets) {
    TileLayer *pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    std::vector<std::vector<int>> data;

    std::vector<int> layerRow(m_width);
    for (int i = 0; i < m_height; i++) {
        data.push_back(layerRow);
    }

    XMLElement *pDataNode = nullptr;

    for (XMLElement *e = pTileElement->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            pDataNode = e;
        }
    }

    std::string dataText = pDataNode->GetText();

    int start = 0;

    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            int end = dataText.find(',', start);
            data[row][col] = stoi(dataText.substr(start, end - start));
            start = end + 1;
        }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(XMLElement *pTextureRoot) {
    TextureManager::Instance()->load(
        std::string("assets/") + pTextureRoot->Attribute("value"),
        pTextureRoot->Attribute("name"), Game::Instance()->getRenderer());
}

GameObject *parseObject(XMLElement *pObjectElement) {
    GameObject *pGameObject = GameObjectFactory::Instance()->create(
        pObjectElement->Attribute("class"));

    int x, y, width, height, numFrames, callbackID, animSpeed;
    std::string textureID;

    x = atoi(pObjectElement->Attribute("x"));
    y = atoi(pObjectElement->Attribute("y"));

    for (XMLElement *e = pObjectElement->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (XMLElement *property = e->FirstChildElement();
                 property != NULL; property = property->NextSiblingElement()) {
                if (property->Value() == std::string("property")) {
                    std::string propertyName = property->Attribute("name");
                    std::string propertyValue = property->Attribute("value");

                    if (propertyName == "textureWidth") {
                        width = stoi(propertyValue);
                    } else if (propertyName == "textureHeight") {
                        height = stoi(propertyValue);
                    } else if (propertyName == "numFrames") {
                        numFrames = stoi(propertyValue);
                    } else if (propertyName == "callbackID") {
                        callbackID = stoi(propertyValue);
                    } else if (propertyName == "textureID") {
                        textureID = propertyValue;
                    } else if (propertyName == "animSpeed") {
                        animSpeed = stoi(propertyValue);
                    }
                }
            }
        }
    }

    pGameObject->load(new LoaderParams(x, y, width, height, textureID,
                                       numFrames, callbackID, animSpeed));
    return pGameObject;
}

void LevelParser::parseObjectLayer(XMLElement *pObjectLayerElement,
                                   std::vector<Layer *> *pLayers) {
    ObjectLayer *pObjectLayer = new ObjectLayer();

    for (XMLElement *pObjectElement = pObjectLayerElement->FirstChildElement();
         pObjectElement != NULL;
         pObjectElement = pObjectElement->NextSiblingElement()) {
        pObjectLayer->getGameObjects()->push_back(parseObject(pObjectElement));
    }

    pLayers->push_back(pObjectLayer);
}
