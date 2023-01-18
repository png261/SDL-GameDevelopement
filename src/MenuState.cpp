#include "MenuState.h"
#include <iostream>

const std::string MenuState::s_menuID = "Menu";

void MenuState::update() {
}

void MenuState::render() {

}

bool MenuState::onEnter() {
    std::cout << "entering menustate" << std::endl;
    return true;
}

bool MenuState::onExit() {
    std::cout << "exiting menustate" << std::endl;
    return true;
}
