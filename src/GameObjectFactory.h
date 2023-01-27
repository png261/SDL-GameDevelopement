#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator {
    public:
        virtual GameObject* createGameObject() const = 0;
        virtual ~BaseCreator() {}
};

class GameObjectFactory {
    public:
        static GameObjectFactory* Instance() {
            if(s_pInstance == NULL) {
                s_pInstance = new GameObjectFactory();
            }
            return s_pInstance;
        }

        bool registerType(std::string typeID, BaseCreator* pCreator) {
            if(m_creators.find(typeID) != m_creators.end()) {
                delete pCreator;
                return false;
            }

            m_creators[typeID] = pCreator;
            return true;
        }

        GameObject* create(std::string typeID) {
            std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
            if(it == m_creators.end()) {
                SDL_Log("could not find typeID: %s", typeID.c_str());
                return NULL;  
            } 
            return it->second->createGameObject();
        }

    private:
        GameObjectFactory() {};
        static GameObjectFactory* s_pInstance;
        std::map<std::string, BaseCreator*> m_creators;
};

#endif
