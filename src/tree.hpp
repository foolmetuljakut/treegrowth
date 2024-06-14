#ifndef tree_tree_hpp
#define tree_tree_hpp

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstddef>
#include <functional>
#include <vector>

namespace tree {

class tree {
  sf::Vector2f dir;
  sf::RectangleShape line;
  std::vector<tree> twigs;
  tree() = default;

public:
  tree(float len, float angledeg, float thick, const sf::Vector2f &origin,
       const size_t &maxlevels, const size_t &level,
       std::function<size_t(size_t)> branches,
       std::function<float(size_t)> length,
       std::function<float(size_t)> thickness,
       std::function<float(size_t)> angularspread) {

    dir = sf::Vector2f{thick, len}; // upright
    line = sf::RectangleShape(dir);
    line.rotate(-angledeg);   // left turning
    line.setPosition(origin); // footpoint
    line.setFillColor(sf::Color(255, 255, 255));

    if (level == maxlevels)
      return;

    size_t n = branches(level);
    float l = length(level);
    float t = thickness(level);
    float da = angularspread(level) / (n - 1);

    twigs.reserve(n);
    auto ephi = sf::Vector2f{(float)sin(angledeg * M_PI / 180),
                             (float)cos(angledeg * M_PI / 180)},
         tphi = sf::Vector2f{(float)cos(angledeg * M_PI / 180),
                             -(float)sin(angledeg * M_PI / 180)};
    for (size_t i = 0; i <= n; i++) {
      auto totalangle = angledeg + da * ((float)i - (float)n / 2);
      auto tphip = sf::Vector2f{(float)cos(totalangle * M_PI / 180),
                                -(float)sin(totalangle * M_PI / 180)};
      auto footpoint = origin +
                       len * (float)(1 - pow((float)i / (2 * n), 1.5)) * ephi +
                       thick / 2 * tphi - t / 2 * tphip;
      twigs.emplace_back(l, totalangle, t, footpoint, maxlevels, level + 1,
                         branches, length, thickness, angularspread);
    }
  }

  void render(sf::RenderWindow &window) {
    window.draw(line);
    for (auto &twig : twigs)
      twig.render(window);
  }
};

} // namespace tree

#endif // tree_tree_hpp