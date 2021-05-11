#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include "encriptar.h"
#include "desencriptar.h"

using namespace std;

int main()
{
    int n;
    do{
        cout<<"|------------------------------------------------------------------------|\n";
        cout<<"|------------------------MENU--------------------------------------------|\n";
        cout<<"|                                                                        |\n";
        cout<<"|  Codificar Archivo...................................1                 |\n";
        cout<<"|  Decodificar Archivo.................................2                 |\n";
        cout<<"|  Salir...............................................0                 |\n";
        cout<<"|------------------------------------------------------------------------|\n";
        cout<<"|------------------------------------------------------------------------|\n";
        cout<<endl;

        cout<<"ingrese una opcion: ";
        cin>>n;
        cout<<endl;

        switch (n) {

        case 1:
            //ENTRADA: archivo (archivo.txt) - SALIDA: archivo (salida.txt)

            cout <<"|------------------------------------------------------------------------|"<<endl;
            cout <<"|-----Este programa codifica textos dando una semilla de codificacion----|"<<endl;
            cout <<"|---------------------y el metodo de codificacion------------------------| "<<endl;
            cout <<"|------------------------------------------------------------------------|"<<endl;
            cout<<endl;
            encriptar();
            break;

        case 2:
            //ENTRADA: archivo (salida.txt) - SALIDA: archivo (salida2.txt)
            cout <<"|------------------------------------------------------------------------|"<<endl;
            cout <<"|----------Este programa Decodifica textos dando la misma semilla--------|"<<endl;
            cout <<"|------------de codificacion y el mismo metodo de codificacion-----------|"<<endl;
            cout <<"|------------------------------------------------------------------------|"<<endl;
            cout<<endl;
            desencriptar();
            break;

        case 0:
            return -1;

        default:
            cout<<"|========================================================================|"<<endl<<endl;
            cout<<"|===================el valor ingresado no es valido======================|"<<endl<<endl;
            cout<<"|========================================================================|"<<endl<<endl;
            break;
        }
    } while(n!=0);
    cin.get();
    return 0;
}


