#include <iostream>
#include <cstdlib>
#include <ctime>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;
// Variables Globales
char sopa[15][15];

void Seleccionar(); //Selecciona las palabras a insertar de un archivo y las envia a otro archivo
void rellenar_matriz(); // Rellena la matriz
void insertarPalabra(string palabra); //Inserta la palabra en la sopa de letras
void aleatorio(); // Es el srand para crear numero aleatorios
int numero_aleatorio(); // Selecciona un numero aleatorio entre 1 y 15
void crea_matriz(); // Crea una matriz con espacios vacios
bool compureba_espacio(string palabra,int caso, int x, int y);
void comenzar();

int main() {

    int opc = 0;
    string palabra;
    aleatorio();
    crea_matriz();
    do{
		printf("\n1)Lectura\n2)Rellenar matriz\n3)Mostrar matriz\n4)Leer documento\n5)Salir");
		printf("\nOpcion:"); scanf("%i",&opc);
        switch(opc){
			case 1: cout<<"Lectura:"<<endl;
                    Seleccionar();
				break;
            case 2: comenzar();
                    rellenar_matriz();
                    
                break;
            case 3:
                break;
            case 4:
                    
                break;
		}

	}while (opc != 5);

    return 0;
}

void Seleccionar(){
    ifstream palabras;
    ofstream inicio("Juego.txt"); // se utiliza para escribir datos en un archivo de texto.
    string texto;
    int num_palabras = 0;
    
    palabras.open("SopaPalabras.txt", ios::in); //Abrimos el archivo

    if(palabras.fail()){            // Por si falla el archivo al abrir
        cout<<"Error 501";
        exit(1);
    }
    
    while (palabras >> texto) { //Almacena el numero de plabras que existen en un archivo
        num_palabras++;
    }

    srand(time(NULL));
    int posicion = rand() % (num_palabras - 2);

    palabras.clear();
    palabras.seekg(0);
    for (int i = 0; i < posicion; i++) {
        palabras >> texto;
    }

    for (int i = 0; i < 3 && palabras >> texto; i++) {
        inicio << texto << endl;
    }

    palabras.close();
}

void comenzar(){
    ifstream juego("Juego.txt");
    string palabra;
    if(juego.fail()){            // Por si falla el archivo al abrir
        cout<<"Error 501";
        exit(1);
    }

    while (juego >> palabra) { //Almacena el numero de plabras que existen en un archivo
        insertarPalabra(palabra);
    }
}
void insertarPalabra(string palabra){
    int x,y,opc = 1,ex = 0, caso = 1;
    x = numero_aleatorio();
    y = numero_aleatorio(); 
    int continuarY = y;
    int continuarX= x;

    do{
        switch(opc){
			case 1: 
                    if(compureba_espacio(palabra,caso, x, y)){
                        for (int i = 0; i < palabra.length(); ++i) {
                            if((continuarY + palabra.length()) < 15){
                                sopa[x][y + i] = palabra[i];
                            }
                            
                        }
                        ex = 1;
                    }
                    else{
                        caso += 1;
                        opc += 1;
                    }
				break;
            case 2: 
                    if(compureba_espacio(palabra,caso, x, y)){
                        for (int i = 0; i < palabra.length(); ++i) {
                            if((continuarY + palabra.length() && (continuarX + palabra.length()) < 15) < 15){
                                sopa[x + i][y + i] = palabra[i];
                            }
                            
                        }
                        ex = 1;
                    }
                    else{
                        caso += 1;
                        opc += 1;
                    }

                break;
            case 3:
                    if(compureba_espacio(palabra,caso, x, y)){
                        for (int i = 0; i < palabra.length(); ++i) {
                            if((continuarX + palabra.length()) < 15){
                                sopa[x + i][y] = palabra[i];
                            }
                        }
                        ex = 1;
                    }
                    else{
                        caso += 1;
                        opc += 1;
                    }
                break;
            case 4:
                    if(compureba_espacio(palabra,caso, x, y)){
                        for (int i = 0; i < palabra.length(); ++i) {
                            if((continuarX + palabra.length()) < 15 && (continuarY - palabra.length()) > 0){
                                sopa[x + i][y - i] = palabra[i];
                            }
                        }
                        ex = 1;
                    }
                    else{
                        caso += 1;
                        opc += 1;
                    }
                break;
            case 5:
                    if(compureba_espacio(palabra,caso, x, y)){
                        for (int i = 0; i < palabra.length(); ++i) {
                            sopa[x][y - i] = palabra[i];
                        }
                        ex = 1;
                    }
                    else{
                        caso += 1;
                        opc += 1;
                    }
                break;
            case 6:
                    if(compureba_espacio(palabra,caso, x, y)){
                        for (int i = 0; i < palabra.length(); ++i) {
                            sopa[x - i][y] = palabra[i];
                        }
                        ex = 1;
                    }
                    else{
                        caso += 1;
                        opc += 1;
                    }
                break;
            case 7:
                    if(compureba_espacio(palabra,caso, x, y)){
                        for (int i = 0; i < palabra.length(); ++i) {
                            sopa[x - i][y - i] = palabra[i];
                        }
                        ex = 1;
                    }
                    else{
                        x = numero_aleatorio();
                        y = numero_aleatorio();
                        opc = 1;
                    }
                break;
		}       
        
    }
    while(ex != 1);

}

void crea_matriz(){
    
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
               sopa[i][j] = ' ';    
        }
    }
    
}

void rellenar_matriz(){
    
    int rellenar = 1;
    

    while (rellenar == 1)
    {
        srand(time(NULL));
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {

                if(sopa[i][j] == ' ' ){
                    sopa[i][j] = 'A' + rand() % 26;           
                }    
            }
        }


        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++){ 
                    cout << sopa[i][j] << "  ";
            }
            cout << endl;
            rellenar = 0;
        }
    }
    
        
    
}

void aleatorio(){
    srand(time(0));
}

int numero_aleatorio(){
    int ale;
    ale = rand() % 15 + 1;
    return ale;
}

bool compureba_espacio(string palabra,int caso, int x, int y){
    int contador = 0;
    switch(caso){
			case 1: 
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' '){
                            y += 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;   
                        }
                    }

				break;
            case 2: 
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' '){
                            y += 1;
                            x += 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;
                        } 
                    }    
                break;
            case 3:
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' '){
                            x += 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;
                        }
                    }
                break;
            case 4:
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' '){
                            y -= 1;
                            x += 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;
                        }
                    }
                break;
            case 5:
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' '){
                            y -= 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;
                        }
                    }
                break;
            case 6:
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' '){
                            y -= 1;
                            x -= 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;
                        }
                    }
                break;
            case 7:
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' ' ){
                            x -= 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;
                        }
                    }
                break;
            case 8: 
                    for (int i = 0; i < palabra.length(); ++i) {
                        if(sopa[x][y] == ' ' ){
                            y += 1;
                            x -= 1;
                            contador +=1;
                        }
                        else{
                            contador = 0;
                            return false;
                        }
                    }
                break;
	}

    if(contador == palabra.length()){
        return true;
    }

    return false;
}