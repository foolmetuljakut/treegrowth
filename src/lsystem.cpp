#include "lsystem.hpp"

void LSystem::setInitialCondition(const std::string& init) {
    state = std::string(init);
}

void LSystem::addRule(const std::string& symbol, const std::string& mapping) {

    // didn't find
    if (rules.find(symbol) == rules.end()) {
        rules.insert({ symbol, mapping });
    } else {
        throw "element already exists";
    }
}

void LSystem::iterate() {

    std::stringstream newState;

    if (rules.size() == 0) {
        throw "can't iterate, no rules defined";
    }

    for (const auto& [ruleTrigger, ruleMapping] : rules) {
        size_t idx = state.find_first_of(ruleTrigger), lastIdx = 0;
        while (idx != state.npos) {
            newState << state.substr(lastIdx, idx - lastIdx);
            newState << ruleMapping;

            lastIdx = idx;
            idx = state.find_first_of(ruleTrigger, idx + ruleMapping.size());
        }
    }

    state = newState.str();
}

void LSystem::render(sf::RenderWindow& window) {}

std::string LSystem::currentState() {
    return std::string(state);
}
