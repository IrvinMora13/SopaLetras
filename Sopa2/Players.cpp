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


bool esMovimientoValido(int x, int y) {
    if (!selectingWord) {
        return true;
    }
    if (directionX == 0 && directionY == 0) {
        directionX = x - lastX;
        directionY = y - lastY;
    }
    if (x == lastX + directionX && y == lastY + directionY) {
        return true;
    }

    return false;
}

char ObtenerLetras(int x, int y) {
    return grid[y][x].getString()[0];
}

void player1(){
    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * 71, GRID_SIZE * 40), "Sopa de letras"); // Crea una ventana para abrir
    initializeGrid(window);
    string textoColumna1;
    SeleccionarPalabras();
    vector<string> palabras = lectura();
    //Columna jugador 1
    sf::RectangleShape columna1(sf::Vector2f(266, 600));
    columna1.setFillColor(sf::Color::White);
    columna1.setPosition(0, 0);
    //Matriz
    sf::RectangleShape columna3(sf::Vector2f(802, 600));
    columna3.setFillColor(sf::Color::Black);
    columna3.setPosition(532, 0);
    //Texto jugador 1
    sf::Text texto1;
    texto1.setFont(font);
    texto1.setCharacterSize(20);
    texto1.setFillColor(sf::Color::Black);
    texto1.setStyle(sf::Text::Regular);
    //Palabras jugador 1
    sf::Text pala;
    pala.setFont(font);
    pala.setCharacterSize(20);
    pala.setFillColor(sf::Color::Black);
    pala.setStyle(sf::Text::Bold);
    //Seleccionar palabras jugador 1
    for (int i = 0; i < 3; ++i) {
        if (i < palabras.size()) {
            textoColumna1 += palabras[i] + "\n";
        }
    }
    //Boton Reiniciar
    sf::RectangleShape boton(sf::Vector2f(100, 50));  // cambia las dimensiones si es necesario
    boton.setFillColor(sf::Color::White);
    boton.setPosition(window.getSize().x - 110, window.getSize().y - 60); // posiciona el botón en la esquina inferior derecha
    //Texton reiniciar
    sf::Text textoBoton;
    textoBoton.setFont(font);
    textoBoton.setString("Reiniciar");
    textoBoton.setCharacterSize(20);
    textoBoton.setFillColor(sf::Color::Black);
    textoBoton.setPosition(boton.getPosition().x + 10, boton.getPosition().y + 10);  // coloca el texto dentro del botón
    //Reloj
    sf::Clock reloj;
    float tiempoRestante = 60.0f;
    //Texto Rejol
    sf::Text textoTiempo;
    textoTiempo.setFont(font);
    textoTiempo.setCharacterSize(24);
    textoTiempo.setFillColor(sf::Color(63, 137, 202));
    textoTiempo.setPosition(700.f, 500.f);
    //Establecer posicion
    texto1.setString(textoColumna1);
    texto1.setPosition(2, 60);
    //Establecer posicion
    pala.setString(" Jugador 1 \n Palabras a buscar:");
    pala.setPosition(90 - pala.getGlobalBounds().width / 2, 25 - pala.getGlobalBounds().height / 2);
    //Constantes
    string palabraActual;
    while (window.isOpen())
    {
        float tiempoTranscurrido = reloj.getElapsedTime().asSeconds();
        tiempoRestante -= tiempoTranscurrido;
        reloj.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                // Comprueba si se hizo clic en el botón de reinicio
                if (position.x >= boton.getPosition().x && position.x <= boton.getPosition().x + boton.getSize().x &&
                    position.y >= boton.getPosition().y && position.y <= boton.getPosition().y + boton.getSize().y) {
                    // Reinicia el juego aquí
                    lastX = -1;
                    lastY = -1;
                    directionX = 0;
                    directionY = 0;
                    selectingWord = false;
                    palabraActual.clear();
                    // Restablecer colores de la cuadrícula
                    for (int i = 0; i < GRID_SIZE; i++) {
                        for (int j = 0; j < GRID_SIZE; j++) {
                            grid[i][j].setFillColor(sf::Color::White);
                        }
                    }
                    //Reiniciar palabras
                    SeleccionarPalabras();
                    palabras = lectura();
                    textoColumna1.clear();
                    for (int i = 0; i < 3; ++i) {
                        if (i < palabras.size()) {
                            textoColumna1 += palabras[i] + "\n";
                        }
                    }
                    texto1.setString(textoColumna1);
                    // Reiniciar el reloj
                    tiempoRestante = 60.0f;
                    reloj.restart();
                    initializeGrid(window);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed){
                // obtén la posición del clic
                sf::Vector2i position = sf::Mouse::getPosition(window);
                // calcula en qué celda de la cuadrícula se hizo clic
                int gridX = (position.x - (window.getSize().x - GRID_SIZE * 33)) / 33;  // se ajusta a la escala de 33x33
                int gridY = position.y / 33;
                // verifica que el clic fue dentro de la cuadrícula
                if (gridX >= 0 && gridX < GRID_SIZE && gridY >= 0 && gridY < GRID_SIZE)
                {
                    if (esMovimientoValido(gridX, gridY)) {
                        grid[gridY][gridX].setFillColor(sf::Color::Red);
                        if (!selectingWord) {
                            selectingWord = true;
                        }
                        lastX = gridX;
                        lastY = gridY;
                        palabraActual += ObtenerLetras(gridX, gridY);
                        cout << "Palabra actual: " << palabraActual << endl;
                    }
                    else {
                        selectingWord = false;
                        lastX = -1;
                        lastY = -1;
                        directionX = 0;
                        directionY = 0;
                        palabraActual.clear();
                        for (int i = 0; i < GRID_SIZE; i++) {
                            for (int j = 0; j < GRID_SIZE; j++) {
                                if (grid[i][j].getFillColor() == sf::Color::Red) {
                                    grid[i][j].setFillColor(sf::Color::White);
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        //Renderizacion de textos
        mostrarPalabras1(window, columna1, columna3, texto1, pala);
        textoTiempo.setString("Tiempo restante: " + std::to_string(static_cast<int>(tiempoRestante)));
        window.draw(textoTiempo);
        window.draw(boton);
        window.draw(textoBoton);
        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                window.draw(grid[i][j]);
            }
        }

        window.display();
    }
}

void player2(){
    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * 71, GRID_SIZE * 40), "Sopa de letras"); // Crea una ventana para abrir
    initializeGrid(window); // Inicializa la matriz
    string textoColumna1;
    string textoColumna2;
    SeleccionarPalabras();
    vector<string> palabras = lectura();
    //Columna jugador 1
    sf::RectangleShape columna1(sf::Vector2f(266, 600));
    columna1.setFillColor(sf::Color::White);
    columna1.setPosition(0, 0);
    //Columna jugador 2
    sf::RectangleShape columna2(sf::Vector2f(534, 600));
    columna2.setFillColor(sf::Color(128, 128, 128));
    columna2.setPosition(266, 0);
    //Matriz
    sf::RectangleShape columna3(sf::Vector2f(802, 600));
    columna3.setFillColor(sf::Color::Black);
    columna3.setPosition(532, 0);
    //Texto jugador 1
    sf::Text texto1;
    texto1.setFont(font);
    texto1.setCharacterSize(20);
    texto1.setFillColor(sf::Color::Black);
    texto1.setStyle(sf::Text::Regular);
    //Texto jugador 2
    sf::Text texto2;
    texto2.setFont(font);
    texto2.setCharacterSize(20);
    texto2.setFillColor(sf::Color::Black);
    texto2.setStyle(sf::Text::Regular);
    //Palabras jugador 1
    sf::Text pala;
    pala.setFont(font);
    pala.setCharacterSize(20);
    pala.setFillColor(sf::Color::Black);
    pala.setStyle(sf::Text::Bold);
    //Palabras jugador 2
    sf::Text pala2;
    pala2.setFont(font);
    pala2.setCharacterSize(20);
    pala2.setFillColor(sf::Color::Black);
    pala2.setStyle(sf::Text::Bold);
    window.clear(sf::Color::White);
    //Seleccionar palabras jugador 1
    for (int i = 0; i < 3; ++i) {
        if (i < palabras.size()) {
            textoColumna1 += palabras[i] + "\n";
        }
    }
    //Seleccionar palabras jugador 2
    for (int i = 3; i < 6; ++i) {
        if (i < palabras.size()) {
            textoColumna2 += palabras[i] + "\n";
        }
    }
    //Boton Reiniciar
    sf::RectangleShape boton(sf::Vector2f(100, 50));  // cambia las dimensiones si es necesario
    boton.setFillColor(sf::Color::White);
    boton.setPosition(window.getSize().x - 110, window.getSize().y - 60); // posiciona el botón en la esquina inferior derecha
    //Texton reiniciar
    sf::Text textoBoton;
    textoBoton.setFont(font);
    textoBoton.setString("Reiniciar");
    textoBoton.setCharacterSize(20);
    textoBoton.setFillColor(sf::Color::Black);
    textoBoton.setPosition(boton.getPosition().x + 10, boton.getPosition().y + 10);  // coloca el texto dentro del botón
    //Reloj
    sf::Clock reloj;
    float tiempoRestante = 60.0f;
    //Texto Rejol
    sf::Text textoTiempo;
    textoTiempo.setFont(font);
    textoTiempo.setCharacterSize(24);
    textoTiempo.setFillColor(sf::Color(63, 137, 202));
    textoTiempo.setPosition(700.f, 500.f);
    //Establecer posicion
    texto1.setString(textoColumna1);
    texto1.setPosition(2, 60);
    texto2.setString(textoColumna2);
    texto2.setPosition(270, 60);
    //Establecer posicion
    pala.setString(" Jugador 1 \n Palabras a buscar:");
    pala.setPosition(90 - pala.getGlobalBounds().width / 2, 25 - pala.getGlobalBounds().height / 2);
    pala2.setString(" Jugador 2 \n Palabras a buscar:");
    pala2.setPosition(360 - pala.getGlobalBounds().width / 2, 25 - pala.getGlobalBounds().height / 2);
    //Constantes
    string palabraActual;
    bool turnoJugador1 = true;
     while (window.isOpen())
    {
        float tiempoTranscurrido = reloj.getElapsedTime().asSeconds();
        tiempoRestante -= tiempoTranscurrido;
        reloj.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                // Comprueba si se hizo clic en el botón de reinicio
                if (position.x >= boton.getPosition().x && position.x <= boton.getPosition().x + boton.getSize().x &&
                    position.y >= boton.getPosition().y && position.y <= boton.getPosition().y + boton.getSize().y) {
                    // Reinicia el juego aquí
                    lastX = -1;
                    lastY = -1;
                    directionX = 0;
                    directionY = 0;
                    selectingWord = false;
                    palabraActual.clear();
                    // Restablecer colores de la cuadrícula
                    for (int i = 0; i < GRID_SIZE; i++) {
                        for (int j = 0; j < GRID_SIZE; j++) {
                            grid[i][j].setFillColor(sf::Color::White);
                        }
                    }
                    //Reiniciar palabras
                    SeleccionarPalabras();
                    palabras = lectura();
                    textoColumna1.clear();
                    textoColumna2.clear();
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
                    texto2.setString(textoColumna2);
                    // Reiniciar el reloj
                    tiempoRestante = 60.0f;
                    reloj.restart();
                    initializeGrid(window);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed){
                // obtén la posición del clic
                sf::Vector2i position = sf::Mouse::getPosition(window);
                // calcula en qué celda de la cuadrícula se hizo clic
                int gridX = (position.x - (window.getSize().x - GRID_SIZE * 33)) / 33;  // se ajusta a la escala de 33x33
                int gridY = position.y / 33;
                // verifica que el clic fue dentro de la cuadrícula
                if (gridX >= 0 && gridX < GRID_SIZE && gridY >= 0 && gridY < GRID_SIZE)
                {
                    if (esMovimientoValido(gridX, gridY)) {
                        grid[gridY][gridX].setFillColor(sf::Color::Red);

                        if (!selectingWord) {
                            selectingWord = true;
                        }
                        lastX = gridX;
                        lastY = gridY;
                        palabraActual += ObtenerLetras(gridX, gridY);
                        cout << "Palabra actual: " << palabraActual << endl;
                    }
                    else {
                        selectingWord = false;
                        lastX = -1;
                        lastY = -1;
                        directionX = 0;
                        directionY = 0;
                        palabraActual.clear();
                        for (int i = 0; i < GRID_SIZE; i++) {
                            for (int j = 0; j < GRID_SIZE; j++) {
                                if (grid[i][j].getFillColor() == sf::Color::Red) {
                                    grid[i][j].setFillColor(sf::Color::White);
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        //Cambio del texto de turno del jugador
        if (tiempoRestante <= 0) {
            if(turnoJugador1 ==true){
                turnoJugador1 = false;
            }else{
                turnoJugador1 = true;
            }
            tiempoRestante = 60.0f;
            palabraActual.clear();
        }
        sf::Text textoTurno;
        textoTurno.setFont(font);
        textoTurno.setCharacterSize(25);
        textoTurno.setFillColor(sf::Color(0, 138, 138));
        if(turnoJugador1){
            textoTurno.setString("Turno del Jugador 1");
        }else{
            textoTurno.setString("Turno del Jugador 2");
        }
        textoTurno.setPosition(690.f, 530.f);
        //Renderizacion de textos
        mostrarPalabras(window, columna1, columna2, columna3, texto1, texto2, pala, pala2);
        textoTiempo.setString("Tiempo restante: " + std::to_string(static_cast<int>(tiempoRestante)));
        window.draw(textoTiempo);
        window.draw(textoTurno);
        window.draw(boton);
        window.draw(textoBoton);
        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                window.draw(grid[i][j]);
            }
        }

        window.display();
    }
}


