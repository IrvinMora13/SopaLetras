#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <string>

const int GRID_SIZE = 15;

sf::Text grid[GRID_SIZE][GRID_SIZE];
sf::Font font;

void initializeGrid() {
    srand(time(0));

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j].setFont(font);
            grid[i][j].setCharacterSize(24);
            grid[i][j].setFillColor(sf::Color::White);
            grid[i][j].setPosition(j * 30, i * 30);

            char randomLetter = 'A' + rand() % 26;
            grid[i][j].setString(randomLetter);
        }
    }
}

int main() {
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    initializeGrid();

    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * 30, GRID_SIZE * 30), "Sopa de letras");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                window.draw(grid[i][j]);
            }
        }
        window.display();
    }

    return 0;
}

