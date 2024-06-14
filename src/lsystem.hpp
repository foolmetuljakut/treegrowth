#pragma once

#include <SFML/Graphics.hpp>

#include <exception>
#include <map>
#include <sstream>
#include <string>

class LSystem {
    std::string state;
    std::map<std::string, std::string> rules;

public:
    void setInitialCondition(const std::string& init);
    void addRule(const std::string& symbol, const std::string& mapping);
    void iterate();
    void render(sf::RenderWindow& window);
    std::string currentState();
};