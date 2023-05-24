#ifndef HASH_H
#define HASH_H
#include <string>
#include <iostream>

using namespace std;

typedef struct snodo
{
    string llave;
    string PalabraSelec;
    struct snodo *sig;
} tnodo;

int funcion_hash(const string &llave);
void inicializarHash();
int insertarHash(string &llave, string &PalabraSelec);
tnodo *crear_nodo(string &llave, string &PalabraSelec);
bool buscarHash(const string &llave);
void eliminarHash(string &llave);

#endif // TABLAHASH_h
