#include "Trie.h"
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

string palabra;
nodoTrie *raiz = nullptr;

nodoTrie *nuevoNodoTrie()
{
    nodoTrie *nodo = new nodoTrie;
    nodo->finDelaPalabra = false;
    return nodo;
}

void insertarTrie(const string &palabra)
{
    if (raiz == nullptr)
        raiz = nuevoNodoTrie();
    nodoTrie *temp = raiz;
    for (char c : palabra)
    {
        if (temp->hijo.find(c) == temp->hijo.end())
            temp->hijo[c] = nuevoNodoTrie();
        temp = temp->hijo[c];
    }

    temp->finDelaPalabra = true;
}

bool buscarTrie(const string &palabra)
{
    if (raiz == nullptr)
    {
        return false;
    }
    nodoTrie *temp = raiz;
    for (char c : palabra)
    {
        if (temp->hijo.find(c) == temp->hijo.end())
        {
            return false;
        }
        temp = temp->hijo[c];
    }
    return temp->finDelaPalabra;
}

void eliminarTrie(const string &palabra)
{
    if (raiz == nullptr)
    {
        return;
    }
    nodoTrie *temp = raiz;
    for (char c : palabra)
    {
        if (temp->hijo.find(c) == temp->hijo.end())
        {
            return;
        }
        temp = temp->hijo[c];
    }

    temp->finDelaPalabra = false;
}

vector<string> lectura()
{
    ifstream archivo;
    archivo.open("Juego.txt", ios::in);
    string palabra;
    vector<string> palabras;

    if (archivo.fail())
    {
        cout << "No se puede abrir";
        exit(1);
    }

    while (!archivo.eof())
    {
        getline(archivo, palabra);
        insertarTrie(palabra);
        palabras.push_back(palabra);
    }
    archivo.close();

    return palabras;
}

void SeleccionarPalabras(int jugadores)
{
    ifstream palabras;
    string texto;
    int num_palabras = 0;

    palabras.open("SopaPalabras.txt", ios::in); // Abrimos el archivo

    if (palabras.fail())
    { // Por si falla el archivo al abrir
        cout << "Error 501";
        exit(1);
    }

    while (palabras >> texto)
    { // Almacena el numero de palabras que existen en un archivo
        num_palabras++;
    }

    srand(time(NULL));
    int posicion = rand() % (num_palabras - 2);

    palabras.clear();
    palabras.seekg(0);
    vector<string> palabras_seleccionadas;
    for (int i = 0; i < posicion; i++)
    {
        palabras >> texto;
    }
    if(jugadores == 2){
        for (int i = 0; i < 6 && palabras >> texto; i++)
        {
            palabras_seleccionadas.push_back(texto);
        }
    }else{
       for (int i = 0; i < 3 && palabras >> texto; i++)
        {
            palabras_seleccionadas.push_back(texto);
        }
    }


    // Mezcla las palabras seleccionadas.
    std::random_shuffle(palabras_seleccionadas.begin(), palabras_seleccionadas.end());

    palabras.close();

    // Escribe las palabras seleccionadas y mezcladas en el archivo de inicio.
    ofstream inicio("Juego.txt"); // se utiliza para escribir datos en un archivo de texto.
    for (const string &palabra : palabras_seleccionadas)
    {
        inicio << palabra << endl;
    }
}