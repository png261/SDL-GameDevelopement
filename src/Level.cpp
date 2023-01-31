#include "Level.h"

Level::Level() {}

void Level::render() {
    for (auto &layer : m_layers) {
        layer->render();
    }
}

void Level::update() {
    for (auto &layer : m_layers) {
        layer->update();
    }
}
