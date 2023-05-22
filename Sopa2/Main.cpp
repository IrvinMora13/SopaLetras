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
void lectura();

int main()
{
    if (!font.loadFromFile("arial.ttf")) // Obtiene el tipo de letra a usar
    {
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * 71, GRID_SIZE * 40), "Sopa de letras"); // Crea una ventana para abrir

    initializeGrid(window);

    vector<string> wordList = readFile("SopaPalabras.txt");
    if (wordList.size() < 6)
    {
        cout << "La lista de palabras no contiene suficientes elementos." << endl;
        return -1;
    }

    random_shuffle(wordList.begin(), wordList.end());
    vector<string> selectedWords(wordList.begin(), wordList.begin() + 6);
    writeFile("Juego.txt", selectedWords);

    vector<string> palabras = readFile("Juego.txt");
    std::string textoColumna1;
    std::string textoColumna2;


//

    lectura();

    sf::RectangleShape columna1(sf::Vector2f(266, 600));
    columna1.setFillColor(sf::Color::White);
    columna1.setPosition(0, 0);

    sf::RectangleShape columna2(sf::Vector2f(534, 600));
    columna2.setFillColor(sf::Color(128, 128, 128));
    columna2.setPosition(266, 0);

    sf::RectangleShape columna3(sf::Vector2f(802, 600));
    columna3.setFillColor(sf::Color::Black);
    columna3.setPosition(532, 0);

    sf::Text texto1;
    texto1.setFont(font);
    texto1.setCharacterSize(20);
    texto1.setFillColor(sf::Color::Black);
    texto1.setStyle(sf::Text::Regular);

    sf::Text texto2;
    texto2.setFont(font);
    texto2.setCharacterSize(20);
    texto2.setFillColor(sf::Color::Black);
    texto2.setStyle(sf::Text::Regular);

    sf::Text pala;
    pala.setFont(font);
    pala.setCharacterSize(20);
    pala.setFillColor(sf::Color::Black);
    pala.setStyle(sf::Text::Bold);

    sf::Text pala2;
    pala2.setFont(font);
    pala2.setCharacterSize(20);
    pala2.setFillColor(sf::Color::Black);
    pala2.setStyle(sf::Text::Bold);
    window.clear(sf::Color::White);
    /*
    std::string textoLista;
    for (const std::string &palabra : palabras)
    {
        textoLista += palabra + "\n";
    }
*/
    for (int i = 0; i < 3; ++i) {
        if (i < palabras.size()) {
            textoColumna1 += palabras[i] + "\n";
        }
    }

    for (int i = 3; i < 6; ++i) {
        if (i < palabras.size()) {
            textoColumna2 += palabras[i] + "\n";
        }
    }

    texto1.setString(textoColumna1);
    texto1.setPosition(2, 60);
    texto2.setString(textoColumna2);
    texto2.setPosition(270, 60);

    pala.setString(" Jugador 1 \n Palabras a buscar:");
    pala.setPosition(90 - pala.getGlobalBounds().width / 2, 25 - pala.getGlobalBounds().height / 2);
    pala2.setString(" Jugador 2 \n Palabras a buscar:");
    pala2.setPosition(360 - pala.getGlobalBounds().width / 2, 25 - pala.getGlobalBounds().height / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
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

void lectura()
{
    ifstream archivo;
    archivo.open("Juego.txt", ios::in);
    string palabra;

    if (archivo.fail())
    {
        cout << "No se puede abrir";
        exit(1);
    }

    while (!archivo.eof())
    {
        getline(archivo, palabra);
        insertarTrie(palabra);
    }
    archivo.close();
}
