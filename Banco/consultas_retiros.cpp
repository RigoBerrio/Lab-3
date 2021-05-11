#include "consultas_retiros.h"
#include "desencriptar.h"
#include "encriptar.h"

#define ENTER 13
#define BACKSPACE 8

//Declaracion de variables
string Cedula_, auxCedula_,clave_;
int saldo_;
bool encontrado_=false;

int consultas_retiros(){
    menu2();
    return 0;
    system("PAUSE");
}

void menu2(){
    int opcion=0;
    do{
        cout<<"|.......................................................|"<<endl;
        cout<<"|.....CONSULTAR EN LOS REGISTROS DE LA BASE DE DATOS....|"<<endl;
        cout<<"|.......................................................|"<<endl;
        cout<<"|1. Consultar...........................................|"<<endl;
        cout<<"|2. Retirar dinero......................................|"<<endl;
        cout<<"|3. Salir...............................................|"<<endl;
        cout<<"|....................QUE DESEA HACER?...................|"<<endl;
        cout<<"|.......................................................|"<<endl;
        cout<<"|Recuerde que si usted tiene en su cuenta un monto mayor|"<<endl;
        cout<<"|      a 1000 COP se debitara de su cuenta 1000 COP     |"<<endl;
        cout<<"|.......................................................|"<<endl;
        cout<<endl;

        cin>>opcion;
        cout<<"--------------------------------------------------------"<<endl;
        cout<<endl;

        switch(opcion){

           case 1:
                consultar();
            break;

            case 2:
               retirar();
            break;

            case 3:
                salir1();
            break;

            default:

            cout<<"|=======================================================|"<<endl;
            cout<<"|=================¡Opcion Incorrecta!===================|"<<endl;
            cout<<"|=======================================================|"<<endl;
            cout<<endl;

        }

    }while(opcion!=3);


}//Fin funcion menu

void consultar(){

    //Declaracion de variables
    ofstream aux;
    ifstream lectura;
    encontrado_=false;
    string auxCedula;
    int saldo_modificado;


    cout<<"INGRESE SU CEDULA PARA CONSULTAR SU SALDO: ";
    cin>>auxCedula;

    Desencriptar(); //se desencripta la base de datos

    aux.open("auxiliar.txt",ios::out);
    lectura.open("clientes.txt",ios::in);

    if(aux.is_open() && lectura.is_open()){

       cout<<endl;
       cout<<"--------------------------------------------------------";

       lectura>>Cedula_;

       while(!lectura.eof()){
           lectura>>clave_>>saldo_;
           if(auxCedula==Cedula_){
               encontrado_=true;
               cout<<endl;
               cout<<"________________________________________________________"<<endl;
               cout<<"Cedula: "<<Cedula_<<endl;
               cout<<"Clave: "<<clave_<<endl;
               cout<<"Saldo: "<<saldo_<<endl;
               cout<<"________________________________________________________"<<endl;
               cout<<endl;

             //CONDICION PARA DEBITAR POR LA CONSULTA EN CASO DE QUE EL MONTO DE SU CUENTA
             if(saldo_>=1000){
                                 saldo_modificado=saldo_-1000;

                                 cout<<"|.......................................................|"<<endl;
                                 cout<<"|......ADVERTENCIA! ACABAMOS DE DEBITAR 1000 COP........|"<<endl;
                                 cout<<"|.....DE SU CUENTA POR CONSULTAR EN NUESTRO BANCO.......|"<<endl;
                                 cout<<"|.......................................................|"<<endl;
                                 cout<<endl;

                                 saldo_=saldo_modificado;
                         }

               aux<<left<<setw(10)<<Cedula_<<setw(13)<<clave_<<setw(7)<<setprecision(2)<<right<<saldo_<<endl;
               }

             else{
                     aux<<left<<setw(10)<<Cedula_<<setw(13)<<clave_<<setw(7)<<setprecision(2)<<right<<saldo_<<endl;

                  }


          lectura>>Cedula_;

           }
     }

    else
     {
              cout<<"--No se pudo abrir el Archivo o aun no ha sido Creado--"<<endl;
              cout<<endl;
             }

     if(encontrado_==false){
              cout<<endl;
              cout<<"No se encontro ningun registro con ese numero de cedula"<<endl;
              cout<<endl;
             }

     aux.close();
     lectura.close();
     remove("clientes.txt");
     rename("auxiliar.txt","clientes.txt");

     encriptar();//se encripta la base de datos

}//Fin funcion consultar

void retirar(){

    //Declaracion de variables
    ofstream aux;
    ifstream lectura;
    encontrado_=false;
    int saldo_a_retirar=0,saldoModificado;
    string auxCedula;
    \
    cout<<"INGRESE SU CEDULA PARA EXTRAER EL DINERO: ";
    cin>>auxCedula;
    cout<<endl;

    Desencriptar(); //Desencriptar la base de datos

    aux.open("auxiliar.txt",ios::out);
    lectura.open("clientes.txt",ios::in);

    if(aux.is_open() && lectura.is_open()){

        cout<<endl;
        cout<<"--------------------------------------------------------";
        cout<<endl;

        lectura>>Cedula_;

        while(!lectura.eof()){
            lectura>>clave_>>saldo_;
            if(auxCedula==Cedula_){
                encontrado_=true;

                if(saldo_<=0) {
                    cout<<endl;
                    saldo_=0; //para que no ponga resultados negativos en la base de datos
                    cout<<"|-------------------------------------------------------|"<<endl;
                    cout<<"|--------------NO TIENE SALDO PARA RETIRAR--------------|"<<endl;
                    cout<<"|---------------------HASTA LUEGO-----------------------|"<<endl;
                    cout<<"|-------------------------------------------------------|"<<endl;
                    cout<<endl;

                    aux<<left<<setw(10)<<Cedula_<<setw(13)<<clave_<<setw(7)<<setprecision(2)<<right<<saldo_<<endl;

                    break;

                }

                cout<<endl;
                cout<<"________________________________________________________"<<endl;
                cout<<"CEDULA: "<<Cedula_<<endl;
                cout<<"CLAVE: "<<clave_<<endl;
                cout<<"SALDO: "<<saldo_<<endl;
                cout<<"________________________________________________________"<<endl;
                cout<<endl;

                cout<<"INGRESA EL DINERO QUE DESEA RETIRAR: ";
                cin>>saldo_a_retirar;
                cout<<endl;
                cout<<"________________________________________________________"<<endl;

                if(saldo_a_retirar>saldo_){
                    cout<<"|-------------------------------------------------------|"<<endl;
                    cout<<"|-NO TIENE SALDO SUFICIENTE PARA RETIRAR ESTA CANTIDAD--|"<<endl;
                    cout<<"|---------------------HASTA LUEGO-----------------------|"<<endl;
                    cout<<"|-------------------------------------------------------|"<<endl;
                    cout<<endl;
                    aux<<left<<setw(10)<<Cedula_<<setw(13)<<clave_<<setw(7)<<setprecision(2)<<right<<saldo_<<endl;
                    cout<<endl;
                    break;
                }

                saldoModificado=saldo_-saldo_a_retirar;

                aux<<left<<setw(10)<<Cedula_<<setw(13)<<clave_<<setw(7)<<setprecision(2)<<right<<saldoModificado<<endl;

                cout<<"|-------------------------------------------------------|"<<endl;
                cout<<"|-----------------REGISTRO MODIFICADO-------------------|"<<endl;
                cout<<"|-------------------------------------------------------|"<<endl;
                cout<<endl;

                saldo_=saldoModificado;


                if(saldo_>=1000){  //CONDICION PARA DEBITAR DINERO POR CONSULTA
                    saldo_=saldo_-1000;

                    cout<<"|........................................................|"<<endl;
                    cout<<"|......ADVERTENCIA! ACABAMOS DE DEBITAR 1000 COP.........|"<<endl;
                    cout<<"|.......DE SU CUENTA POR RETIRAR EN NUESTRO BANCO........|"<<endl;
                    cout<<"|........................................................|"<<endl;
                    cout<<endl;

                }

            }

            else{
               aux<<left<<setw(10)<<Cedula_<<setw(13)<<clave_<<setw(7)<<setprecision(2)<<right<<saldo_<<endl;
            }


     lectura>>Cedula_;

     }
  }

   else{
           cout<<"--No se pudo abrir el Archivo o aun no ha sido Creado--"<<endl;
           cout<<endl;
       }

   if(encontrado_==false){
           cout<<endl;
           cout<<"-No se encontro ningun registro con ese numero de cedula-"<<endl;
           cout<<endl;
           cout<<endl;
       }

   //Cerrando los archivos
   aux.close();
   lectura.close();
   remove("clientes.txt");
   rename("auxiliar.txt","clientes.txt");

   encriptar(); //se encripta la base de datos

} //Fin funcion retirar

void salir1(){
    cout<<"|=======================================================|"<<endl;
    cout<<"|==================Proceso finalizado===================|"<<endl;
    cout<<"|=======================================================|"<<endl;
    cout<<endl;
}
