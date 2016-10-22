#include <iostream>
#include "tablero.h"
#include <stdlib.h>


#define COL 30
#define FIL 25

using namespace std;

int main()
{
    int opcion;
    Tablero Mazmorras(6,6);
    Tablero tablero1(FIL,COL);

    do{
        cout<<"********************************************************"<<endl;
        cout<<"**********************ROQUELIKE*************************"<<endl;
        cout<<"***                                                  ***"<<endl;
        cout<<"***-Introduzca un 1 para empezar el juego aleatorio  ***"<<endl;
        cout<<"***-Introduzca un 2 para cargar el juego por fichero ***"<<endl;
        cout<<"***-Introduzca un 3 para salir                       ***"<<endl;
        cout<<"***                                                  ***"<<endl;
        cout<<"********************************************************"<<endl;
        cout<<"Introduzca su opcion:";
        cin >>opcion;

        switch(opcion){
        case 1:
            tablero1.Pintar_Tablero(FIL,COL,0,0);
            break;

        case 2:
            cout<<"Habriendo fichero"<<endl;
            tablero1.Pintar_Tablero(FIL,COL,0,0);
            break;
        case 3:
            cout<<"Ha decidido salir"<<endl;
            break;
       }

    }

    while(opcion !=3);

    return 0;
}

