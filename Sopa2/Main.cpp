#include "grid.h"
#include "fileIO.h"
#include "display.h"
#include "Trie.h"
#include "constants.h"
#include "Hash.h"
#include "Players.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

sf::Text grid[GRID_SIZE][GRID_SIZE];
sf::Font font;
int lastX = -1, lastY = -1;
int directionX = 0, directionY = 0;
bool selectingWord = false;


int main()
{
    if (!font.loadFromFile("arial.ttf")) // Obtiene el tipo de letra a usar
    {
        return -1;
    }
    sf::RenderWindow menuWindow(sf::VideoMode(GRID_SIZE * 71, GRID_SIZE * 40), "Menú");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg"))
    {
        return -1; // si hay un problema al cargar el archivo, termina el programa
    }
    // Fondo Menu
    sf::Sprite backgroundSprite(backgroundTexture);
    // Ajusta el tamaño del sprite de fondo para que coincida con el tamaño de la ventana
    backgroundSprite.setScale(
        menuWindow.getSize().x / static_cast<float>(backgroundTexture.getSize().x),
        menuWindow.getSize().y / static_cast<float>(backgroundTexture.getSize().y));
    // Botones del Menu
    sf::RectangleShape singlePlayerButton(sf::Vector2f(200, 100));
    singlePlayerButton.setPosition(400, 100); // posiciona el botón en el centro de la pantalla
    sf::RectangleShape twoPlayerButton(sf::Vector2f(200, 100));
    twoPlayerButton.setPosition(400, 400); // posiciona el botón en el centro de la pantalla
    // Numero de jugadores 1
    sf::Text jugadores1;
    jugadores1.setFont(font);
    jugadores1.setCharacterSize(20);
    jugadores1.setString("1 Jugador");
    jugadores1.setFillColor(sf::Color::Black);
    jugadores1.setStyle(sf::Text::Regular);
    sf::FloatRect textRect = jugadores1.getLocalBounds();
    jugadores1.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    jugadores1.setPosition(singlePlayerButton.getPosition().x + singlePlayerButton.getSize().x / 2.0f, singlePlayerButton.getPosition().y + singlePlayerButton.getSize().y / 2.0f);

    // Numero de jugadores 2
    sf::Text jugadores2;
    jugadores2.setFont(font);
    jugadores2.setCharacterSize(20);
    jugadores2.setString("2 Jugadores");
    jugadores2.setFillColor(sf::Color::Black);
    jugadores2.setStyle(sf::Text::Regular);
    sf::FloatRect textRect2 = jugadores2.getLocalBounds();
    jugadores2.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
    jugadores2.setPosition(twoPlayerButton.getPosition().x + twoPlayerButton.getSize().x / 2.0f, twoPlayerButton.getPosition().y + twoPlayerButton.getSize().y / 2.0f);

    while (menuWindow.isOpen())
    {
        sf::Event event;
        while (menuWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                menuWindow.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i position = sf::Mouse::getPosition(menuWindow);
                // Comprobar si el botón de un jugador fue presionado
                if (position.x >= singlePlayerButton.getPosition().x &&
                    position.x <= singlePlayerButton.getPosition().x + singlePlayerButton.getSize().x &&
                    position.y >= singlePlayerButton.getPosition().y &&
                    position.y <= singlePlayerButton.getPosition().y + singlePlayerButton.getSize().y)
                {
                    menuWindow.close();
                    player1();
                }
                else if (position.x >= twoPlayerButton.getPosition().x &&
                         position.x <= twoPlayerButton.getPosition().x + twoPlayerButton.getSize().x &&
                         position.y >= twoPlayerButton.getPosition().y &&
                         position.y <= twoPlayerButton.getPosition().y + twoPlayerButton.getSize().y)
                {
                    menuWindow.close();
                    player2();
                }
            }
        }

        menuWindow.clear();
        menuWindow.draw(backgroundSprite);
        menuWindow.draw(singlePlayerButton);
        menuWindow.draw(twoPlayerButton);
        menuWindow.draw(jugadores1);
        menuWindow.draw(jugadores2);
        menuWindow.display();
    }
    return 0;
}
