#include "desencriptar.h"

void desencriptar(){
    int n,opcion,d;
    char c;

    fstream entrada,salida2;
    vector<int> vecBi,VectorComp;
    vector<char>finaldecodificado;
    string Decodi,codi;

    cout<<"INGRESE EL NOMBRE DEL ARCHIVO QUE QUIERE DECODIFICAR:\n ";
    cin >> codi;
    codi+=".txt";
    entrada.open(codi);//abriendo el archivo donde esta el binario a decodificar
    cout<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;

    cout<<"INGRESE EL NOMBRE DEL ARCHIVO DONDE SE GUARDARA EL DECODIFICADO:\n";
    cin >> Decodi;
    Decodi+=".txt";
    cout<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;


    salida2.open(Decodi, ios::out);//creando un archivo de salida para el segundo punto
    if(!salida2.is_open() || !entrada.is_open()){//confirmando que si exista
        cout<<endl;
        cout<<"|========================================================================|"<<endl;
        cout<<"|=======================El archivo no esta===============================|"<<endl;
        cout<<"|========================================================================|"<<endl;
        cout<<endl;
    }

    else{
        while (!entrada.eof()) {//pasar el archivo a un vector de enteros
            entrada>>c;
            d=int(c)-48;
            vecBi.insert(vecBi.end(),d);
        }

    vecBi.erase(vecBi.end()-1);

    cout<<endl;

    cout<<"INGRESE SEMILLA DE CODIFICACION: ";
    cin>>n;
    cout<<endl;

    cout<<"INGRESE EL METODO DE CODIFICACION: ";
    cin>>opcion;
    cout<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;

    switch(opcion){
    case 1:
        VectorComp=primerMet2(vecBi, n);
        break;
    case 2:
        VectorComp=segMet2(vecBi, n);
        break;
    default:
        cout<<"|=======================================================================|"<<endl;
        cout<<"|==================El numero ingresado no es valido=====================|"<<endl;
        cout<<"|=======================================================================|"<<endl;
        cout<<endl;
        break;
    }

    if(VectorComp.size()!=0){
        finaldecodificado=decodificado2(VectorComp);

        for(int i=0;i<finaldecodificado.size();i++)//agregando el vector a un archivo de salida del segundo punto
            salida2<<finaldecodificado[i];

        cout<<endl;
        cout<<"|=======================================================================|"<<endl;
        cout<<"|=======Proceso terminado, dirijase al documento para verificarlo=======|"<<endl;
        cout<<"|=======================================================================|"<<endl;
        cout<<endl;
        cout<<endl;

        salida2.close();
        entrada.close();
     }
   }
}


vector<char> decodificado2(vector<int> vectorpordecodifica1){
    vector<vector<int>> vectorpordecodificar((vectorpordecodifica1.size()/8),vector<int> (8));
    vector<char> vectorfinalcodificado(vectorpordecodificar.size());
    vectorpordecodificar=blockNbits(vectorpordecodifica1, 8);
    int entero=7,entero2=0,entero3;

    for(int t=0; t<vectorpordecodificar.size();t++){
        entero=7;entero2=0;
        for(int i=0;i<8;i++){
            entero3=pow(2,entero);
            entero2+=(vectorpordecodificar[t][i])*entero3;
            entero--;
        }

        vectorfinalcodificado[t]=entero2;

    }
    return vectorfinalcodificado;
}

vector<int> primerMet2(vector<int> VectBin, int n){

    vector<vector<int>> vect4=blockNbits(VectBin,n);//llama la funcion que separa en bloques de n bits
    int cont1=0,cont0=0,a=vect4.size();

    for(int i=0;i<a;i++){
        if(i==0){//modificando el primer bloque con el primer metodo
            for(int j=0;j<n;j++){
                if(vect4[i][j]==0)
                    vect4[i][j]=1;
                else vect4[i][j]=0;
            }
        }

        else if(cont1==cont0)//si hay igual catidad de ceros y unos de invierte cada bit del grupo
            for(int j=0;j<n;j++){
                if(vect4[i][j]==0)
                    vect4[i][j]=1;
                else vect4[i][j]=0;
            }

        else if(cont0>cont1)//si hay mayor cantidad de ceros se invierte cada dos bits
            for(int j=1;j<n;j+=2){
                if(vect4[i][j]==0)
                    vect4[i][j]=1;
                else vect4[i][j]=0;
            }

        else if(cont1>cont0)//si hay mayor cantidad de unos(1) se invierte cada 3 bits
            for(int j=2;j<n;j=j+3){
                if(vect4[i][j]==0)
                    vect4[i][j]=1;
                else vect4[i][j]=0;
            }

        cont0=0;cont1=0;//cuenta los elementos del bloque
        for(int h=0;h<n;h++){
            if(vect4[i][h]==0)
                cont0++;
            else cont1++;
        }
    }
    return ConVect(vect4);//convirtiendo un vector de vectores en un vector
}

vector<int> segMet2(vector<int> VectBin, int n){
    vector<vector<int>> vect4=blockNbits(VectBin, n);
    int a=vect4.size();
    for(int i=0;i<a;i++){
        vect4[i].insert(vect4[i].end(),vect4[i][0]);
        vect4[i].erase(vect4[i].begin());
    }
    return ConVect(vect4);
}

//.
