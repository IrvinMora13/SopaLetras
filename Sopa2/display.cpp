#include "display.h"

void mostrarPalabras(sf::RenderWindow &ventana, sf::RectangleShape &columna1, sf::RectangleShape &columna2, sf::Text &texto, sf::Text &pala)
{
    ventana.draw(columna1);
    ventana.draw(columna2);
    ventana.draw(pala);
    ventana.draw(texto);
}

