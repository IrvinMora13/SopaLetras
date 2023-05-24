#include "Hash.h"
#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;
tnodo *mapa[100];

int funcion_hash(const string &llave)
{
    int a = 0;
    for (int i = 0; llave[i] != '\0'; i++)
    {
        a += static_cast<int>(llave[i]);
    }
    a %= 100;
    return a;
}

void inicializarHash()
{
    for (int i = 0; i < 100; i++)
    {
        mapa[i] = NULL;
    }
}

tnodo *crear_nodo(string &llave, string &PalabraSelec)
{
    tnodo *nuevo = (tnodo *)malloc(sizeof(tnodo));
    nuevo->llave = llave;
    nuevo->PalabraSelec = PalabraSelec;
    nuevo->llave[sizeof(nuevo->llave) - 1] = '\0';
    nuevo->PalabraSelec[sizeof(nuevo->PalabraSelec) - 1] = '\0';
    nuevo->sig = NULL;
    return nuevo;
}

int insertarHash(string &llave, string &PalabraSelec)
{
    int index = funcion_hash(llave);
    tnodo *nuevo_nodo = crear_nodo(llave, PalabraSelec);
    if (mapa[index] == NULL)
    {
        mapa[index] = nuevo_nodo;
    }
    else
    {
        tnodo *actual = mapa[index];
        while (actual->sig != NULL)
        {
            actual = actual->sig;
        }
        actual->sig = nuevo_nodo;
    }
    return index;
}

bool buscarHash(const string &llave)
{
    int index = funcion_hash(llave);
    tnodo *actual = mapa[index];
    while (actual != NULL)
    {
        if (actual->llave == llave)
        {
            return true; // Se encontr� la palabra
        }
        else
        {
            actual = actual->sig;
        }
    }
    return false; // No se encontr� la palabra
}

void eliminarHash(string &llave)
{
    if(buscarHash(llave))
    {
        int index = funcion_hash(llave);
        mapa[index] = NULL;
        if (!buscarHash(llave))
            printf("Se elimino exitosamente el elemento");
        else
            printf("No se elimino el elemento");
    }
    else
        printf("No se encontro el elemento");
}
