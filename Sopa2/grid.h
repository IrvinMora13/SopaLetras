#ifndef GRID_H
#define GRID_H
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

extern sf::Text grid[GRID_SIZE][GRID_SIZE];
extern sf::Font font;

void initializeGrid(sf::RenderWindow &window);

#endif

