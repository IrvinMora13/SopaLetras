#include "Trie.h"
#include <iostream>
#include <unordered_map>
#include<stdlib.h>
#include<string.h>
#include <string>


using namespace std;

string palabra;
nodoTrie* raiz = nullptr;

nodoTrie* nuevoNodoTrie() {
    nodoTrie* nodo = new nodoTrie;
    nodo->finDelaPalabra = false;
    return nodo;
}

void insertarTrie(const string& palabra) {
    if (raiz == nullptr)
        raiz = nuevoNodoTrie();
    nodoTrie* temp = raiz;
    for (char c : palabra) {
        if (temp->hijo.find(c) == temp->hijo.end())
            temp->hijo[c] = nuevoNodoTrie();
        temp = temp->hijo[c];
    }

    temp->finDelaPalabra = true;
}

bool buscarTrie(const string& palabra) {
    if (raiz == nullptr) {
        return false;
    }
    nodoTrie* temp = raiz;
    for (char c : palabra) {
        if (temp->hijo.find(c) == temp->hijo.end()) {
            return false;
        }
        temp = temp->hijo[c];
    }
    return temp->finDelaPalabra;
}

void eliminarTrie(const string& palabra) {
    if (raiz == nullptr) {
        return;
    }
    nodoTrie* temp = raiz;
    for (char c : palabra) {
        if (temp->hijo.find(c) == temp->hijo.end()) {
            return;
        }
        temp = temp->hijo[c];
    }

    temp->finDelaPalabra = false;
}
