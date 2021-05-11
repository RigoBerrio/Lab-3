#include "registro_usuarios.h"
#include "acceso_admin.h"
#include "desencriptar.h"
#include "encriptar.h"

//Declaracion de variables
string Cedula, auxCedula,clave;
int saldo=0;
bool encontrado=false;

int registro_usuarios(){
    menu();
    return 0;
    system("PAUSE");
}

void menu(){
    int opcion1=0;


                do{
                         cout<<"|.......................................................|"<<endl;
                         cout<<"|........REGISTRO DE USUARIOS EN LA BASE DE DATOS.......|"<<endl;
                         cout<<"|.......................................................|"<<endl;
                         cout<<"|1. Registrar un usuario................................|"<<endl;
                         cout<<"|2. Salir...............................................|"<<endl;
                         cout<<"|....................QUE DESEA HACER?...................|"<<endl;
                         cout<<"|.......................................................|"<<endl;
                         cout<<endl;

                         cin>>opcion1;
                         cout<<"--------------------------------------------------------"<<endl;
                         cout<<endl;

                         switch(opcion1){
                             case 1:
                                 registrar();
                             break;

                             case 2:
                                 salir();
                             break;

                             default:
                                 cout<<"|=======================================================|"<<endl;
                                 cout<<"|=================¡Opcion Incorrecta!===================|"<<endl;
                                 cout<<"|=======================================================|"<<endl;
                         }
                     }while(opcion1!=2);

}//Fin funcion menu

void registrar(){


    //Declaracion de variables
    ofstream escritura;
    ifstream consulta;
    bool repetido=false;

    cout<<"INGRESA LA CEDULA DEL CLIENTE: ";
    cin>>auxCedula;
    cout<<endl;

    Desencriptar(); //se desencripta la base de datos

    escritura.open("clientes.txt",ios::out|ios::app);
    consulta.open("clientes.txt",ios::in);

     if(escritura.is_open() && consulta.is_open()){

         consulta>>Cedula;

         while(!consulta.eof()){
             consulta>>clave>>saldo;
             if(Cedula==auxCedula){
                 cout<<"|-------------------------------------------------------|"<<endl;
                 cout<<"|----------Ya Existe un Registro con esta Cedula--------|"<<endl;
                 cout<<"|-------------------------------------------------------|"<<endl;
                 cout<<endl;
                 repetido=true;
                 break;
             }

         consulta>>Cedula;

         }

         if(repetido==false){
             cout<<"INGRESA LA CLAVE DEL CLIENTE: ";
             cin>>clave;
             cout<<endl;
             cout<<"INGRESA SU SALDO: ";
             cin>>saldo;
             cout<<endl;

             //Se pasa a imprimir los datos en el fichero de una manera organizada
             escritura<<left<<setw(10)<<auxCedula<<setw(13)<<clave<<setw(7)<<setprecision(2)<<right<<saldo<<endl;
             cout<<endl;

             cout<<"|=======================================================|"<<endl;
             cout<<"|==================Registro Agregado====================|"<<endl;
             cout<<"|=======================================================|"<<endl;

             cout<<endl;
         }


     }

     else{
         cout<<"-Error, el Archivo No se Pudo Abrir o No ha sido Creado-"<<endl;
         cout<<endl;
     }

    //Cerrando los archivos
     escritura.close();
     consulta.close();

     encriptar();//se encripta la base de datos
}//Fin funcion registrar

void salir(){
    cout<<"|=======================================================|"<<endl;
    cout<<"|==================Proceso finalizado===================|"<<endl;
    cout<<"|=======================================================|"<<endl;
    cout<<endl;
}
