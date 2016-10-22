#include "tablero.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <time.h>



Tablero::Tablero(int n_filas, int n_columnas){

    columnas = n_columnas;
    filas = n_filas;
    tablero=new char *[columnas];
    for (int i = 0; i < filas; i++) {
        tablero[i] = new char [columnas];
    }
    vacio=' ';
    suelo='.';
    pared='*';
    puerta='+';
    camino='#';
    amuleto='&';
    mounstruo='O';
    pos_Inicial='X';
    personaje='@';
    Tesoro=0;
    Win=0;






}

void Tablero::Pintar_Tablero(int, int,int posx,int posy)
{


    //llenamos el tablero de blancos
    for(int i=posx;i<filas;i++){
        for(int j=posy;j<columnas;j++){
            tablero[i][j]=vacio;
        }
    }

    Pintar_Mazmorras(4,4,0);
    Pintar_Mazmorras(4,20,0);
    Pintar_Mazmorras(15,20,1);
    Pintar_Amuleto(17,23);
    Pintar_Mounstruo(6,6);
    Pintar_Mounstruo(7,22);
    Pintar_Mounstruo(18,23);
    Pintar_Personaje(8,5);


}
void Tablero::Pintar_Mazmorras(int x,int y,int flag){

    Tablero Mazmorras(6,6);
    Mazmorras.posx=x;
    Mazmorras.posy=y;
    for(int i=Mazmorras.posx;i< Mazmorras.filas + Mazmorras.posx;i++){
        for(int j=Mazmorras.posy;j<Mazmorras.posy + Mazmorras.columnas;j++){
            tablero[i][j]=suelo;
        }
    }
    ///creacion de bordes de las mazmorra

    for(int j=Mazmorras.posy;j < Mazmorras.posy + Mazmorras.columnas ;j++){
        tablero[Mazmorras.posx][j]=Mazmorras.pared;
    }

    for(int j=Mazmorras.posy;j< Mazmorras.posy + Mazmorras.columnas;j++){
        tablero[Mazmorras.posx + Mazmorras.filas -1][j]=Mazmorras.pared;

    }


    for(int i=Mazmorras.posx;i< Mazmorras.filas + Mazmorras.posx;i++){

        tablero[i][Mazmorras.posy]=Mazmorras.pared;
    }

    for(int i=Mazmorras.posx;i<Mazmorras.filas + Mazmorras.posx;i++){
        tablero[i][Mazmorras.posy + Mazmorras.columnas -1]=Mazmorras.pared;
    }
    ///Creacion puertas y camino del tablero
    if(flag==1){
        //PUERTTAS
        tablero[6][9]=Mazmorras.puerta;
        tablero[9][6]=Mazmorras.puerta;
        tablero[6][20]=Mazmorras.puerta;
        tablero[9][23]=Mazmorras.puerta;
        tablero[18][20]=Mazmorras.puerta;
        tablero[15][23]=Mazmorras.puerta;

        //CAMINOS
        for(int j=10;j<20;j++){
            tablero[6][j]=Mazmorras.camino;
        }

        for(int i=10;i<15;i++){
            tablero[i][23]=Mazmorras.camino;
        }

        for(int i=10;i<19;i++){
            tablero[i][6]=Mazmorras.camino;
        }

        for(int j=6;j<20;j++){
            tablero[18][j]= Mazmorras.camino;
        }

    }



}

void Tablero::Pintar_Amuleto(int x,int y){

    Tablero Amuleto(0,0);
    Amuleto.posx=x;
    Amuleto.posy=y;
    tablero[Amuleto.posx][Amuleto.posy]=Amuleto.amuleto;
}


void Tablero::Pintar_Mounstruo(int x,int y){

    Tablero Mounstruo(0,0);
    Mounstruo.posx=x;
    Mounstruo.posy=y;
    tablero[Mounstruo.posx][Mounstruo.posy]=Mounstruo.mounstruo;


}



void Tablero::Pintar_Personaje(int x, int y){

    Tablero Personaje(0,0);
    Personaje.posx=x;
    Personaje.posy=y;
    Personaje.vidas=5;
    Personaje.Win=0;
    Personaje.Tesoro=0;
    tablero[Personaje.posx][Personaje.posy]=pos_Inicial;
    Imprimir_Tablero(x,y);
    //Imprimir_Tablero();

    char c;

    do{
        system("stty raw");
        c=getchar();
        system("stty cooked");

        switch (c){
        case 'w'://SUBIR
            if((tablero[Personaje.posx-1][Personaje.posy]!=pared) && (tablero[Personaje.posx-1][Personaje.posy]!=mounstruo) && (tablero[Personaje.posx-1][Personaje.posy]!=vacio)){//MIRAMOS SI HAY PARED O MOUNSTRUO

                if(tablero[Personaje.posx][Personaje.posy]==pos_Inicial){//primer movimiento
                    tablero[Personaje.posx][Personaje.posy]=pos_Inicial;
                    tablero[Personaje.posx-1][Personaje.posy]=personaje;
                }else
                    if(tablero[Personaje.posx-1][Personaje.posy]==amuleto){//amuleto
                        tablero[Personaje.posx-1][Personaje.posy]=Personaje.personaje;
                        tablero[Personaje.posx][Personaje.posy]=suelo;
                        Personaje.Tesoro=1;

                    }
                    else

                        if(tablero[Personaje.posx-1][Personaje.posy]==pos_Inicial){
                            tablero[Personaje.posx-1][Personaje.posy]=pos_Inicial;

                            if(Personaje.Tesoro==1){
                                tablero[Personaje.posx-1][Personaje.posy]='$';
                                Personaje.Win=1;
                                break;
                            }
                        }
                        else

                            //CAMINOSSSS PUERTAS SUELOS

                            if((tablero[Personaje.posx-1][Personaje.posy]==puerta) && (tablero[Personaje.posx-2][Personaje.posy]==camino)){//entreando en puertas desde mazmorra
                                tablero[Personaje.posx-1][Personaje.posy]=Personaje.personaje;
                                tablero[Personaje.posx][Personaje.posy]=suelo;


                            }

                            else
                                if((tablero[Personaje.posx-1][Personaje.posy]==camino) && (tablero[Personaje.posx+1][Personaje.posy]==suelo)){//entrando en caminos
                                    tablero[Personaje.posx-1][Personaje.posy]=Personaje.personaje;
                                    tablero[Personaje.posx][Personaje.posy]=puerta;


                                }
                                else
                                    if(tablero[Personaje.posx-1][Personaje.posy]==camino){
                                        tablero[Personaje.posx-1][Personaje.posy]=Personaje.personaje;
                                        tablero[Personaje.posx][Personaje.posy]=camino;

                                    }

                                    else
                                        if((tablero[Personaje.posx-1][Personaje.posy]==puerta) && (tablero[Personaje.posx-2][Personaje.posy]==suelo)){//entreando en puertas desde camino
                                            tablero[Personaje.posx-1][Personaje.posy]=Personaje.personaje;
                                            tablero[Personaje.posx][Personaje.posy]=camino;


                                        }

                                        else
                                            if((tablero[Personaje.posx-1][Personaje.posy]==suelo) && (tablero[Personaje.posx+1][Personaje.posy]==camino)){//entreando en puertas desde mazmorra
                                                tablero[Personaje.posx-1][Personaje.posy]=Personaje.personaje;
                                                tablero[Personaje.posx][Personaje.posy]=puerta;


                                            }
                                            else
                                                if(tablero[Personaje.posx-1][Personaje.posy]==suelo){//Movimiento en mazmorra
                                                    tablero[Personaje.posx-1][Personaje.posy]=Personaje.personaje;
                                                    tablero[Personaje.posx][Personaje.posy]=suelo;

                                                }



                Personaje.posx = Personaje.posx-1;

                //vidas
                if((tablero[Personaje.posx-1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx+1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx][Personaje.posy -1]==mounstruo) || (tablero[Personaje.posx][Personaje.posy+1]==mounstruo))
                {
                    //DIAGONALES  tablero[Personaje.posx-1][Personaje.posy-1]==mounstruo|| tablero[Personaje.posx+1][Personaje.posy +1]==mounstruo || tablero[Personaje.posx+1][Personaje.posy-1]==mounstruo || tablero[Personaje.posx-11][Personaje.posy+1]==mounstruo)

                    Personaje.vidas=Personaje.vidas-1;
                }
                cout<<"vidas:"<<Personaje.vidas<<endl;


            }
            Imprimir_Tablero(Personaje.posx,Personaje.posy);
            //Imprimir_Tablero();
            break;
        case 's'://BAJAR
            if((tablero[Personaje.posx+1][Personaje.posy]!=pared) && (tablero[Personaje.posx+1][Personaje.posy]!=mounstruo) && (tablero[Personaje.posx+1][Personaje.posy]!=vacio)){//MIRAMOS SI HAY PARED O MOUNSTRUO

                if(tablero[Personaje.posx][Personaje.posy]==pos_Inicial){//primer movimiento
                    tablero[Personaje.posx][Personaje.posy]=pos_Inicial;
                    tablero[Personaje.posx+1][Personaje.posy]=personaje;
                }
                else
                    if(tablero[Personaje.posx+1][Personaje.posy]==pos_Inicial){//primer movimiento
                        tablero[Personaje.posx+1][Personaje.posy]=pos_Inicial;

                    }
                    else
                        if(tablero[Personaje.posx+1][Personaje.posy]==amuleto){//amuleto
                            tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;
                            tablero[Personaje.posx][Personaje.posy]=suelo;
                            Personaje.Tesoro=1;

                        }
                        else

                            if(tablero[Personaje.posx+1][Personaje.posy]==pos_Inicial){
                                tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;

                                if(Personaje.Tesoro==1){
                                    tablero[Personaje.posx+1][Personaje.posy]='$';
                                    Personaje.Win=1;
                                    break;
                                }
                            }
                            else

                                //CAMINOSSSS PUERTAS SUELOS

                                if((tablero[Personaje.posx+1][Personaje.posy]==puerta) && (tablero[Personaje.posx+2][Personaje.posy]==camino)){//entreando en puertas desde mazmorra
                                    tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;
                                    tablero[Personaje.posx][Personaje.posy]=suelo;


                                }


                if((tablero[Personaje.posx+1][Personaje.posy]==camino) && (tablero[Personaje.posx-1][Personaje.posy]==suelo)){//entrando en caminos
                    tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;
                    tablero[Personaje.posx][Personaje.posy]=puerta;


                }
                else
                    if(tablero[Personaje.posx+1][Personaje.posy]==camino){//en el camino dentro
                        tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;
                        tablero[Personaje.posx][Personaje.posy]=camino;

                    }

                    else
                        if((tablero[Personaje.posx+1][Personaje.posy]==puerta) && (tablero[Personaje.posx+2][Personaje.posy]==suelo)){//entreando en puertas desde camino
                            tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;
                            tablero[Personaje.posx][Personaje.posy]=camino;


                        }

                        else
                            if((tablero[Personaje.posx+1][Personaje.posy]==suelo) && (tablero[Personaje.posx-1][Personaje.posy]==camino)){//entreando en puertas desde mazmorra
                                tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;
                                tablero[Personaje.posx][Personaje.posy]=puerta;


                            }
                            else
                                if(tablero[Personaje.posx+1][Personaje.posy]==suelo){//Movimiento en mazmorra
                                    tablero[Personaje.posx+1][Personaje.posy]=Personaje.personaje;
                                    tablero[Personaje.posx][Personaje.posy]=suelo;

                                }

                Personaje.posx = Personaje.posx+1;

                //vidas
                if((tablero[Personaje.posx+1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx-1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx][Personaje.posy +1]==mounstruo) || (tablero[Personaje.posx][Personaje.posy-1]==mounstruo))
                {
                    //DIAGONALES  tablero[Personaje.posx-1][Personaje.posy-1]==mounstruo|| tablero[Personaje.posx+1][Personaje.posy +1]==mounstruo || tablero[Personaje.posx+1][Personaje.posy-1]==mounstruo || tablero[Personaje.posx-11][Personaje.posy+1]==mounstruo)

                    Personaje.vidas=Personaje.vidas-1;
                }
                cout<<"vidas:"<<Personaje.vidas<<endl;


            }
            Imprimir_Tablero(Personaje.posx,Personaje.posy);
            //Imprimir_Tablero();

            break;
        case 'a'://IZQUIERDA

            if((tablero[Personaje.posx][Personaje.posy-1]!=pared) && (tablero[Personaje.posx][Personaje.posy-1]!=mounstruo) && (tablero[Personaje.posx][Personaje.posy-1]!=vacio)){//MIRAMOS SI HAY PARED O MOUNSTRUO
                if(tablero[Personaje.posx][Personaje.posy]==pos_Inicial){//primer movimiento
                    tablero[Personaje.posx][Personaje.posy]=pos_Inicial;
                    tablero[Personaje.posx][Personaje.posy-1]=personaje;
                }
                else

                    if(tablero[Personaje.posx][Personaje.posy-1]==amuleto){//amuleto
                        tablero[Personaje.posx][Personaje.posy-1]=Personaje.personaje;
                        tablero[Personaje.posx][Personaje.posy]=suelo;
                        Personaje.Tesoro=1;

                    }
                    else

                        if(tablero[Personaje.posx][Personaje.posy-1]==pos_Inicial){
                            tablero[Personaje.posx][Personaje.posy-1]=pos_Inicial;

                            if(Personaje.Tesoro==1){
                                tablero[Personaje.posx][Personaje.posy-1]='$';
                                Personaje.Win=1;
                                break;
                            }
                        }
                        else

                            //CAMINOSSSS PUERTAS SUELOS

                            if((tablero[Personaje.posx][Personaje.posy-1]==puerta) && (tablero[Personaje.posx][Personaje.posy-2]==camino)){//entreando en puertas desde mazmorra
                                tablero[Personaje.posx][Personaje.posy-1]=Personaje.personaje;
                                tablero[Personaje.posx][Personaje.posy]=suelo;


                            }

                            else
                                if((tablero[Personaje.posx][Personaje.posy-1]==camino) && (tablero[Personaje.posx][Personaje.posy+1]==suelo)){//entrando en caminos
                                    tablero[Personaje.posx][Personaje.posy-1]=Personaje.personaje;
                                    tablero[Personaje.posx][Personaje.posy]=puerta;


                                }
                                else
                                    if(tablero[Personaje.posx][Personaje.posy-1]==camino){
                                        tablero[Personaje.posx][Personaje.posy-1]=Personaje.personaje;
                                        tablero[Personaje.posx][Personaje.posy]=camino;

                                    }

                                    else
                                        if((tablero[Personaje.posx][Personaje.posy-1]==puerta) && (tablero[Personaje.posx][Personaje.posy-2]==suelo)){//entreando en puertas desde camino
                                            tablero[Personaje.posx][Personaje.posy-1]=Personaje.personaje;
                                            tablero[Personaje.posx][Personaje.posy]=camino;


                                        }

                                        else
                                            if((tablero[Personaje.posx][Personaje.posy-1]==suelo) && (tablero[Personaje.posx][Personaje.posy+1]==camino)){//entreando en puertas desde mazmorra
                                                tablero[Personaje.posx][Personaje.posy-1]=Personaje.personaje;
                                                tablero[Personaje.posx][Personaje.posy]=puerta;


                                            }
                                            else
                                                if(tablero[Personaje.posx][Personaje.posy-1]==suelo){
                                                    tablero[Personaje.posx][Personaje.posy-1]=Personaje.personaje;
                                                    tablero[Personaje.posx][Personaje.posy]=suelo;

                                                }


                Personaje.posy = Personaje.posy-1;

                //vidas
                if((tablero[Personaje.posx-1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx+1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx][Personaje.posy -1]==mounstruo) || (tablero[Personaje.posx][Personaje.posy+1]==mounstruo))
                {
                    //DIAGONALES  tablero[Personaje.posx-1][Personaje.posy-1]==mounstruo|| tablero[Personaje.posx+1][Personaje.posy +1]==mounstruo || tablero[Personaje.posx+1][Personaje.posy-1]==mounstruo || tablero[Personaje.posx-11][Personaje.posy+1]==mounstruo)

                    Personaje.vidas=Personaje.vidas-1;
                }
                cout<<"vidas:"<<Personaje.vidas<<endl;


            }
            Imprimir_Tablero(Personaje.posx,Personaje.posy);
            //Imprimir_Tablero();
            break;
        case 'd'://DERECHA

            if((tablero[Personaje.posx][Personaje.posy+1]!=pared) && (tablero[Personaje.posx][Personaje.posy+1]!=mounstruo) && (tablero[Personaje.posx][Personaje.posy+1]!=vacio)){//MIRAMOS SI HAY PARED O MOUNSTRUO
                if(tablero[Personaje.posx][Personaje.posy]==pos_Inicial){//primer movimiento
                    tablero[Personaje.posx][Personaje.posy]=pos_Inicial;
                    tablero[Personaje.posx][Personaje.posy+1]=personaje;
                }
                else
                    if(tablero[Personaje.posx][Personaje.posy+1]==amuleto){//amuleto
                        tablero[Personaje.posx][Personaje.posy+1]=Personaje.personaje;
                        tablero[Personaje.posx][Personaje.posy]=suelo;
                        Personaje.Tesoro=1;

                    }
                    else

                        if(tablero[Personaje.posx][Personaje.posy+1]==pos_Inicial){
                            tablero[Personaje.posx][Personaje.posy+1]=personaje;

                            if(Personaje.Tesoro==1){
                                tablero[Personaje.posx][Personaje.posy+1]='$';
                                Personaje.Win=1;
                                break;
                            }
                        }
                        else

                            //CAMINOSSSS PUERTAS SUELOS

                            if((tablero[Personaje.posx][Personaje.posy+1]==puerta) && (tablero[Personaje.posx][Personaje.posy+2]==camino)){//entreando en puertas desde mazmorra
                                tablero[Personaje.posx][Personaje.posy+1]=Personaje.personaje;
                                tablero[Personaje.posx][Personaje.posy]=suelo;

                            }

                            else
                                if((tablero[Personaje.posx][Personaje.posy+1]==camino) && (tablero[Personaje.posx][Personaje.posy-1]==suelo)){//entrando en caminos
                                    tablero[Personaje.posx][Personaje.posy+1]=Personaje.personaje;
                                    tablero[Personaje.posx][Personaje.posy]=puerta;


                                }
                                else
                                    if(tablero[Personaje.posx][Personaje.posy+1]==camino){
                                        tablero[Personaje.posx][Personaje.posy+1]=Personaje.personaje;
                                        tablero[Personaje.posx][Personaje.posy]=camino;

                                    }

                                    else
                                        if((tablero[Personaje.posx][Personaje.posy+1]==puerta) && (tablero[Personaje.posx][Personaje.posy+2]==suelo)){//entreando en puertas desde camino
                                            tablero[Personaje.posx][Personaje.posy+1]=Personaje.personaje;
                                            tablero[Personaje.posx][Personaje.posy]=camino;


                                        }

                                        else
                                            if((tablero[Personaje.posx][Personaje.posy+1]==suelo) && (tablero[Personaje.posx][Personaje.posy-1]==camino)){//entreando en puertas desde mazmorra
                                                tablero[Personaje.posx][Personaje.posy+1]=Personaje.personaje;
                                                tablero[Personaje.posx][Personaje.posy]=puerta;


                                            }
                                            else
                                                if(tablero[Personaje.posx][Personaje.posy+1]==suelo){
                                                    tablero[Personaje.posx][Personaje.posy+1]=Personaje.personaje;
                                                    tablero[Personaje.posx][Personaje.posy]=suelo;

                                                }

                Personaje.posy = Personaje.posy+1;

                //vidas
                if((tablero[Personaje.posx-1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx+1][Personaje.posy]==mounstruo) || (tablero[Personaje.posx][Personaje.posy -1]==mounstruo) || (tablero[Personaje.posx][Personaje.posy+1]==mounstruo))
                {
                    //DIAGONALES  tablero[Personaje.posx-1][Personaje.posy-1]==mounstruo|| tablero[Personaje.posx+1][Personaje.posy +1]==mounstruo || tablero[Personaje.posx+1][Personaje.posy-1]==mounstruo || tablero[Personaje.posx-11][Personaje.posy+1]==mounstruo)

                    Personaje.vidas=Personaje.vidas-1;
                }
                cout<<"vidas:"<<Personaje.vidas<<endl;


            }
            Imprimir_Tablero(Personaje.posx,Personaje.posy);
            //Imprimir_Tablero();
            break;
        }


    }

    while((Personaje.vidas!=0) && (Personaje.Win!=1));
    if(Personaje.Win==1){

        cout<<endl<<"HAS GANADO"<<endl;
    }
    else

        cout<<"HAS PERDIDO"<<endl;


}

// Imprimir Tablero

void Tablero::Imprimir_Tablero(int x, int y)
{

    for(int i=0;i<filas;i++){

        for(int j=0;j<columnas;j++){

            if(i==x-1 && j==y-1){
                cout << tablero[i][j];
            }
            if(i==x-1 && j==y){
                cout << tablero[i][j];
            }
            if(i==x-1 && j==y+1){
                cout << tablero[i][j];
            }
            if(i==x+1 && j==y+1){
                cout << tablero[i][j];
            }
            if(i==x+1 && j==y-1){
                cout << tablero[i][j];
            }
            if(i==x+1 && j==y){
                cout << tablero[i][j];
            }
            if(i==x && j==y-1){
                cout << tablero[i][j];
            }
            if(i==x && j==y+1){
                cout << tablero[i][j];
            }
            if(i==x && j==y){
                cout << tablero[i][j];
            }
            else
                cout<<" ";
        }

        cout <<endl;
    }

}

/*void Tablero::Imprimir_Tablero()
{

    for(int i=0;i<filas;i++){

        for(int j=0;j<columnas;j++){
            cout << tablero[i][j];

        }
        cout << endl;
    }



}*/

/* funcion mover mounstruos
    time.h
    srand(time(NULL);//Semilla
    t=rand()%4

    segun lo que devuleva seria subir=0,bjar=1,izq=2,der=3 en un switch
    movernos si la casilla siguiente es suelo , si es otra cosa no me muevo
*/




