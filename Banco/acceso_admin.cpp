#include "acceso_admin.h"
#include "encriptar.h"
#include "desencriptar.h"

#define ENTER 13
#define BACKSPACE 8

int acceso_admin() {

    //Declaracion de variables
    char cadena[128];
    string NombreAdministrador, password;
    int Decision=0;
    char caracter;

    desencriptar_Contrasena(); //Se desencripta la contrasena

    ifstream ficheroAutenticacion("Contrasena_De_Autenticacion_Administradores.txt");//se abre el fichero donde se encuentra la contrasena que lo acredita
                                                                                     //como administrador

    while (!ficheroAutenticacion.eof()) {
      ficheroAutenticacion >> cadena;
    }

    encriptar_contrasena(); //se encripta la contrasena

    cout<<"INGRESE SU NOMBRE: ";
    cin>>NombreAdministrador;

    cout<<"INGRESE CONTRASENA: ";

        //La contrasena ingresada se cifra a un estilo password con el simbolo "*"
        caracter = getch();
        password = "";

        while (caracter != ENTER) {

            if (caracter != BACKSPACE) {
                password.push_back(caracter);
                cout << "*";

            }

            else {
                if (password.length() > 0) {
                    cout << "\b \b";
                    password = password.substr(0, password.length() - 1);
                }

            }

            caracter = getch();
         }

    cout<<endl;
    cout<<"........................................................."<<endl;

    cout<<endl;


    if(cadena==password)
      {  Decision=0;
        cout<<"|-------------------------------------------------------|\n";
        cout<<"|................Bienvenido.."<<NombreAdministrador<<".....................|\n";
        cout<<"|.........Usted es uno de nuestros administradores......|\n";
        cout<<"|.......Ahora Podra Acceder a Nuestra Base de Datos.....|\n";
        cout<<"|-------------------------------------------------------|\n";
        cout<<endl;
        cout<<"........................................................"<<endl;

    }

    else {

        Decision=1;
        cout<<"|--------------------------------------------------------|"<<endl;
        cout<<"|..........USTED NO ES ADMINISTRADOR DE ESTE BANCO.......|"<<endl;
        cout<<"|....NO TIENE PERMISOS PARA ACCEDER A LA BASE DE DATOS...|"<<endl;
        cout<<"|........................................................|"<<endl;
        cout<<"|....EN POCOS SEGUNDOS VOLVERA A NUESTRO MENU DE INICIO..|"<<endl;
        cout<<"|--------------------------------------------------------|"<<endl;
        cout<<endl;
        cout<<"........................................................"<<endl;

    }

   ficheroAutenticacion.close();  //Se cierra el archivo

   remove("Contrasena_De_Autenticacion_Administradores.txt");
   rename("Contrasena.txt","Contrasena_De_Autenticacion_Administradores.txt");

   return Decision;

} //Fin funcion acceso_admin

void encriptar_contrasena(){

    //Declaracion de variables
    int SemillaCodificacion=1;
    char c;
    fstream fin;
    ofstream arch2;
    vector<int>VectorCompleto;
    vector <int> vect1,VectBin;

    fin.open("Contrasena_De_Autenticacion_Administradores.txt");//abriendo el archivo creado para convertir

    if(!fin.is_open())//comprobando que el archivo esta(existe) dentro del programa
    {
        cout<<"|=======================================================|"<<endl;
        cout<<"|==================El archivo no esta===================|"<<endl;
        cout<<"|=======================================================|"<<endl;
    }

    else{

        arch2.open("Contrasena.txt", ios::out);//creando un archivo de salida

        while (!fin.eof()) {//transformar el archivo en un vector
            fin.get(c);
            vect1.insert(vect1.end(),c);
        }

        vect1.erase(vect1.end()-1);
        VectBin=conversion(vect1); //llamando la funcion que convierte a binario

        VectorCompleto=sndmetod(VectBin, SemillaCodificacion);

        if(VectorCompleto.size()!=0){
            for(int i=0;i<VectorCompleto.size();i++){
                arch2<<VectorCompleto[i];
            }

            if(VectBin.size()%SemillaCodificacion!=0){
                for(int i=0;i<VectBin.size()-VectorCompleto.size();i++)
                    arch2<<VectBin[VectorCompleto.size()+i];
            }

    //Cerrando archivos
    fin.close();
    arch2.close();

    remove("Contrasena_De_Autenticacion_Administradores.txt");
    rename("Contrasena.txt","Contrasena_De_Autenticacion_Administradores.txt");


        }
    }
}

void desencriptar_Contrasena(){

    //Declaracion de variables
    int d, SemillaCodificacion=1;
    char c;

    fstream entrada,salida2;
    vector<int> vecBi,VectorComp;
    vector<char>finaldecodificado;

    entrada.open("Contrasena_De_Autenticacion_Administradores.txt");//abriendo el archivo donde esta el binario a decodificar

    salida2.open("Contrasena.txt", ios::out);//creando un archivo de salida

    if(!salida2.is_open() || !entrada.is_open()){//confirmando que si exista

        cout<<"|=======================================================|"<<endl;
        cout<<"|==================El archivo no esta===================|"<<endl;
        cout<<"|=======================================================|"<<endl;
    }

    else
    {
        while (!entrada.eof()) {//pasar el archivo a un vector de enteros
            entrada>>c;
            d=int(c)-48;
            vecBi.insert(vecBi.end(),d);
        }
        vecBi.erase(vecBi.end()-1);


        VectorComp=segMet2(vecBi, SemillaCodificacion);

        if(VectorComp.size()!=0){
            finaldecodificado=decodificado2(VectorComp);
            for(int i=0;i<finaldecodificado.size();i++)//agregando el vector a un archivo de salida del segundo punto
                salida2<<finaldecodificado[i];

        //Cerrando archivos
        salida2.close();
        entrada.close();

        remove("Contrasena_De_Autenticacion_Administradores.txt");
       rename("Contrasena.txt","Contrasena_De_Autenticacion_Administradores.txt");

        }
    }
}
