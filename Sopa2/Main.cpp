#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
const int GRID_SIZE = 15;

sf::Text grid[GRID_SIZE][GRID_SIZE];
sf::Font font;

void mostrarPalabras(sf::RenderWindow &ventana, sf::RectangleShape &columna1, sf::RectangleShape &columna2, sf::Text &texto, sf::Text &pala);
void initializeGrid(sf::RenderWindow &window) // Añade window como argumento
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

int main()
{
    if (!font.loadFromFile("arial.ttf"))
    {
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * 50, GRID_SIZE * 50), "Sopa de letras");

    initializeGrid(window);
    sf::RectangleShape columna1(sf::Vector2f(266, 600));
    columna1.setFillColor(sf::Color::White);
    columna1.setPosition(0, 0);

    sf::RectangleShape columna2(sf::Vector2f(534, 600));
    columna2.setFillColor(sf::Color::Black);
    columna2.setPosition(266, 0);

    sf::Text texto;
    texto.setFont(font);
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::Black);
    texto.setStyle(sf::Text::Regular);

    sf::Text pala;
    pala.setFont(font);
    pala.setCharacterSize(20);
    pala.setFillColor(sf::Color::Black);
    pala.setStyle(sf::Text::Bold);

    // Configuración del texto
    sf::Font fuente;
    if (!fuente.loadFromFile("arial.ttf"))
    {
        std::cout << "Error al cargar la fuente." << std::endl;
    }

    window.clear(sf::Color::White);

    // Lectura de palabras desde un archivo
    std::ifstream archivo("Juego.txt");
    std::string palabra;
    std::vector<std::string> palabras;

    if (archivo.is_open())
    {
        while (archivo >> palabra)
        {
            palabras.push_back(palabra);
        }
        archivo.close();
    }
    else
    {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    // Construir el texto de la lista de palabras
    std::string textoLista;
    for (const std::string &palabra : palabras)
    {
        textoLista += palabra + "\n";
    }

    // Establecer el contenido del texto y su posición en la columna 2
    texto.setString(textoLista);
    texto.setPosition(2, 30);

    pala.setString("Palabras a buscar:");
    pala.setPosition(90 - pala.getGlobalBounds().width / 2, 10 - pala.getGlobalBounds().height / 2);

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

        mostrarPalabras(window, columna1, columna2, texto, pala);

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

void mostrarPalabras(sf::RenderWindow &ventana, sf::RectangleShape &columna1, sf::RectangleShape &columna2, sf::Text &texto, sf::Text &pala)
{
    ventana.draw(columna1);
    ventana.draw(columna2);
    ventana.draw(pala);
    ventana.draw(texto);
}
