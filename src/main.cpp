
#include "lsystem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char** argv) {

    LSystem lsystem;
    lsystem.setInitialCondition("^");
    lsystem.addRule("^^", "^[+^,-^]^");
    lsystem.addRule("^", "^^");

    std::cout << lsystem.currentState() << std::endl;
    for (size_t i = 0; i < 10; i++) {
        lsystem.iterate();
        std::cout << lsystem.currentState() << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(1280, 800), "tree sim");
    window.setVerticalSyncEnabled(true);
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    // escape just passes through to closed event
                    if (event.key.code != sf::Keyboard::Escape)
                        break;
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear();
        lsystem.render(window);
        window.display();
    }

    return 0;
}