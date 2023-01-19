#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include <vector>
#include <string>

#include "tinyxml2.h"
#include "GameObject.h"

using namespace tinyxml2;

class StateParser {
    public:
        bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
    private:
        void parseObjects(XMLElement* pStateRoot, std::vector<GameObject*> *pObjects);
        void parseTextures(XMLElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};

#endif
