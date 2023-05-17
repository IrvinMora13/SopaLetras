#include "grid.h"

void initializeGrid(sf::RenderWindow &window)
{
    srand(time(0));

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j].setFont(font);
            grid[i][j].setCharacterSize(25);
            grid[i][j].setFillColor(sf::Color::White);
            grid[i][j].setPosition(window.getSize().x - GRID_SIZE * 30 + j * 30, i * 30);

            char randomLetter = 'A' + rand() % 26;
            grid[i][j].setString(randomLetter);
        }
    }

}


