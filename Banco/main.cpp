#include "acceso_admin.h"
#include "consultas_retiros.h"
#include "desencriptar.h"
#include "encriptar.h"
#include "registro_usuarios.h"

int main()
        {

    int n;

    do{
        cout<<"|-------------------------------------------------------|\n";
        cout<<"|--BIENVENIDO AL BANCO DE LA UNIVERSIDAD DE ANTIOQUIA---|\n";
        cout<<"|-------------------------------------------------------|\n";
        cout<<"|-------------------------MENU--------------------------|\n";
        cout<<"|-------------------------------------------------------|\n";
        cout<<"|........Es usted administrador del banco?.............1|\n";
        cout<<"|........Es usted usuario del banco?...................2|\n";
        cout<<"|-------------------------------------------------------|\n";

        cout<<endl;

        cout<<"INGRESE UNA OPCION: ";
        cin>>n;
        cout<<"--------------------------------------------------------"<<endl;
        cout<<endl;

        switch (n) {
            case 1:
                if(acceso_admin()==0)
                  registro_usuarios();
                break;

            case 2:
                consultas_retiros();
                break;


            case 0:
                return -1;

             default:
                cout<<"|========================================================|"<<endl;
                cout<<"|=============El valor ingresado no es valido============|"<<endl;
                cout<<"|========================================================|"<<endl;
                break;
        }
    } while(n!=0);

    cin.get();
    return 0;
}
