
#include "tree.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char **argv) {

  tree::tree t(
      400, 180, 20, sf::Vector2f{640, 800}, 4, 1,
      [](size_t l) { return 2 + l; },
      [](size_t l) { return 200.0f / pow(l, 1.5); },
      [](size_t l) { return 10.0f / l; },
      [](size_t l) { return 160.0f * pow((float)l / 4, 0.5f); });

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
    t.render(window);
    window.display();
  }

  return 0;
}