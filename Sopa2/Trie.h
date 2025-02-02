#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

struct nodoTrie
{
    bool finDelaPalabra;
    std::unordered_map<char, nodoTrie *> hijo;
};

void insertarTrie(const string &palabra);
bool buscarTrie(const string &palabra);
void eliminarTrie(const string &palabra);
vector<string> lectura();
void SeleccionarPalabras(int jugadores);

#endif
