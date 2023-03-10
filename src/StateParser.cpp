#include "StateParser.h"

#include "Game.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"

bool StateParser::parseState(const char *stateFile, std::string stateID,
                             std::vector<GameObject *> *pObjects,
                             std::vector<std::string> *pTextureIDs) {
    XMLDocument doc;
    doc.LoadFile(stateFile);

    XMLElement *pRoot = doc.RootElement();
    if (pRoot == NULL) {
        return false;
    }

    XMLElement *pStateRoot = NULL;
    for (XMLElement *e = pRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (strcmp(e->Value(), stateID.c_str()) == 0) {
            pStateRoot = e;
            break;
        }
    }

    if (pStateRoot == NULL) {
        return false;
    }

    XMLElement *pTextureRoot = 0;
    for (XMLElement *e = pStateRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (strcmp(e->Value(), "TEXTURES") == 0) {
            pTextureRoot = e;
            break;
        }
    }

    if (pTextureRoot) {
        parseTextures(pTextureRoot, pTextureIDs);
    }

    XMLElement *pObjectRoot = NULL;
    for (XMLElement *e = pStateRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        if (strcmp(e->Value(), "OBJECTS") == 0) {
            pObjectRoot = e;
            break;
        }
    }

    if (pObjectRoot) {
        parseObjects(pObjectRoot, pObjects);
    }

    return true;
}

void StateParser::parseTextures(XMLElement *pTextureRoot,
                                std::vector<std::string> *pTextureIDs) {
    for (XMLElement *e = pTextureRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        std::string fileName = e->Attribute("filename");
        std::string textureID = e->Attribute("ID");

        pTextureIDs->push_back(textureID);
        TextureManager::Instance()->load(fileName, textureID,
                                         Game::Instance()->getRenderer());
    }
}

void StateParser::parseObjects(XMLElement *pObjectRoot,
                               std::vector<GameObject *> *pObjects) {
    for (XMLElement *e = pObjectRoot->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement()) {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;

        if (e->Attribute("x")) {
            x = atoi(e->Attribute("x"));
        }
        if (e->Attribute("y")) {
            y = atoi(e->Attribute("y"));
        }
        if (e->Attribute("width")) {
            width = atoi(e->Attribute("width"));
        }
        if (e->Attribute("height")) {
            height = atoi(e->Attribute("height"));
        }
        if (e->Attribute("numFrames")) {
            numFrames = atoi(e->Attribute("numFrames"));
        }
        if (e->Attribute("callbackID")) {
            callbackID = atoi(e->Attribute("callbackID"));
        }
        if (e->Attribute("animSpeed")) {
            animSpeed = atoi(e->Attribute("animSpeed"));
        }
        if (e->Attribute("textureID")) {
            textureID = e->Attribute("textureID");
        }

        GameObject *pGameObject =
            GameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams(x, y, width, height, textureID,
                                           numFrames, callbackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
}
