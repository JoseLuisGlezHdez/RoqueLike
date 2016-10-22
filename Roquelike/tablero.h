#ifndef TABLERO_H
#define TABLERO_H

/******LIBRERIAS*******/
#include <iostream>
#include <stdlib.h>


using namespace std;

class Tablero
{
public:
    Tablero(int, int);//Constructor



    void Imprimir_Tablero(int x, int y);
    void Pintar_Tablero(int, int, int, int);
    void Pintar_Mazmorras(int, int, int);
    void Pintar_Amuleto(int , int );
    void Pintar_Mounstruo(int,int);
    void Pintar_Personaje(int,int);






private:

    char **tablero;
    int columnas;
    int filas;
    int vidas;
    int posx,posy;

    char vacio;
    char suelo;
    char pared;
    char puerta;
    char camino;
    char amuleto;
    char mounstruo;
    char pos_Inicial;
    char personaje;
    int Tesoro;
    int Win;



};




#endif // TABLERO_H
