#include "grid.h"
#include "fileIO.h"
#include "display.h"
#include "Trie.h"
#include "constants.h"
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

bool esMovimientoValido(int x, int y)
{
    if (!selectingWord)
    {
        return true;
    }
    if (directionX == 0 && directionY == 0)
    {
        directionX = x - lastX;
        directionY = y - lastY;
    }
    if (x == lastX + directionX && y == lastY + directionY)
    {
        return true;
    }

    return false;
}

char ObtenerLetras(int x, int y)
{
    return grid[y][x].getString()[0];
}

int main()
{
    if (!font.loadFromFile("arial.ttf")) // Obtiene el tipo de letra a usar
    {
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * 71, GRID_SIZE * 40), "Sopa de letras"); // Crea una ventana para abrir
    initializeGrid(window);                                                                   // Inicializa la matriz

    string textoColumna1;
    string textoColumna2;
    SeleccionarPalabras();
    vector<string> palabras = lectura();
    // Columna jugador 1
    sf::RectangleShape columna1(sf::Vector2f(266, 600));
    columna1.setFillColor(sf::Color::White);
    columna1.setPosition(0, 0);
    // Columna jugador 2
    sf::RectangleShape columna2(sf::Vector2f(534, 600));
    columna2.setFillColor(sf::Color(128, 128, 128));
    columna2.setPosition(266, 0);
    // Matriz
    sf::RectangleShape columna3(sf::Vector2f(802, 600));
    columna3.setFillColor(sf::Color::Black);
    columna3.setPosition(532, 0);
    // Texto jugador 1
    sf::Text texto1;
    texto1.setFont(font);
    texto1.setCharacterSize(20);
    texto1.setFillColor(sf::Color::Black);
    texto1.setStyle(sf::Text::Regular);
    // Texto jugador 2
    sf::Text texto2;
    texto2.setFont(font);
    texto2.setCharacterSize(20);
    texto2.setFillColor(sf::Color::Black);
    texto2.setStyle(sf::Text::Regular);
    // Palabras jugador 1
    sf::Text pala;
    pala.setFont(font);
    pala.setCharacterSize(20);
    pala.setFillColor(sf::Color::Black);
    pala.setStyle(sf::Text::Bold);
    // Palabras jugador 2
    sf::Text pala2;
    pala2.setFont(font);
    pala2.setCharacterSize(20);
    pala2.setFillColor(sf::Color::Black);
    pala2.setStyle(sf::Text::Bold);
    window.clear(sf::Color::White);
    // Seleccionar palabras jugador 1
    for (int i = 0; i < 3; ++i)
    {
        if (i < palabras.size())
        {
            textoColumna1 += palabras[i] + "\n";
        }
    }
    // Seleccionar palabras jugador 2
    for (int i = 3; i < 6; ++i)
    {
        if (i < palabras.size())
        {
            textoColumna2 += palabras[i] + "\n";
        }
    }
    // Establecer posicion
    texto1.setString(textoColumna1);
    texto1.setPosition(2, 60);
    texto2.setString(textoColumna2);
    texto2.setPosition(270, 60);
    // Establecer posicion
    pala.setString(" Jugador 1 \n Palabras a buscar:");
    pala.setPosition(90 - pala.getGlobalBounds().width / 2, 25 - pala.getGlobalBounds().height / 2);
    pala2.setString(" Jugador 2 \n Palabras a buscar:");
    pala2.setPosition(360 - pala.getGlobalBounds().width / 2, 25 - pala.getGlobalBounds().height / 2);
    // Constantes
    string palabraActual;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // obtén la posición del clic
                sf::Vector2i position = sf::Mouse::getPosition(window);
                // calcula en qué celda de la cuadrícula se hizo clic
                int gridX = (position.x - (window.getSize().x - GRID_SIZE * 33)) / 33; // se ajusta a la escala de 33x33
                int gridY = position.y / 33;
                // verifica que el clic fue dentro de la cuadrícula
                if (gridX >= 0 && gridX < GRID_SIZE && gridY >= 0 && gridY < GRID_SIZE)
                {
                    if (esMovimientoValido(gridX, gridY))
                    {
                        grid[gridY][gridX].setFillColor(sf::Color::Red);

                        if (!selectingWord)
                        {
                            selectingWord = true;
                        }
                        lastX = gridX;
                        lastY = gridY;
                        palabraActual += ObtenerLetras(gridX, gridY);
                        cout << "Palabra actual: " << palabraActual << endl;
                    }
                    else
                    {
                        selectingWord = false;
                        lastX = -1;
                        lastY = -1;
                        directionX = 0;
                        directionY = 0;
                        palabraActual.clear();
                        for (int i = 0; i < GRID_SIZE; i++)
                        {
                            for (int j = 0; j < GRID_SIZE; j++)
                            {
                                if (grid[i][j].getFillColor() == sf::Color::Red)
                                {
                                    grid[i][j].setFillColor(sf::Color::White);
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        mostrarPalabras(window, columna1, columna2, columna3, texto1, texto2, pala, pala2);

        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                window.draw(grid[i][j]);
            }
        }

        window.display();
    }

    return 0;
}
