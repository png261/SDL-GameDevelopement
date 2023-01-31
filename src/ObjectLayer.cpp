#include "ObjectLayer.h"

void ObjectLayer::update() {
    for (auto &object : m_gameObjects) {
        object->update();
    }
}

void ObjectLayer::render() {
    for (auto &object : m_gameObjects) {
        object->draw();
    }
}
