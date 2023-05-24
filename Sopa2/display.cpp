#include "display.h"

void mostrarPalabras(sf::RenderWindow &ventana, sf::RectangleShape &columna1, sf::RectangleShape &columna2, sf::RectangleShape &columna3, sf::Text &texto1, sf::Text &texto2, sf::Text &pala, sf::Text &pala2)
{
    ventana.draw(columna1);
    ventana.draw(columna2);
    ventana.draw(columna3);
    ventana.draw(pala);
    ventana.draw(pala2);
    ventana.draw(texto1);
    ventana.draw(texto2);
}
void mostrarPalabras1(sf::RenderWindow &ventana, sf::RectangleShape &columna1, sf::RectangleShape &columna3, sf::Text &texto1, sf::Text &pala)
{
    ventana.draw(columna1);
    ventana.draw(columna3);
    ventana.draw(pala);
    ventana.draw(texto1);
}
