#include "desencriptar.h"

void Desencriptar(){

    //Declaracion de variables
    int d, SemillaCodificacion=1;
    char c;

    ifstream entrada;
    ofstream salida2;
    vector<int> vecBi,VectorComp;
    vector<char>finaldecodificado;

    entrada.open("clientes.txt");//abriendo el archivo donde esta el binario a decodificar

    salida2.open("auxiliar.txt", ios::out);//creando un archivo de salida

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

  remove("clientes.txt");
  rename("auxiliar.txt","clientes.txt");

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


vector<int> segMet2(vector<int> VectBin, int n){
    vector<vector<int>> vect4=blockNbits(VectBin, n);
    int a=vect4.size();

    for(int i=0;i<a;i++){
        vect4[i].insert(vect4[i].end(),vect4[i][0]);
        vect4[i].erase(vect4[i].begin());
    }

    return ConVect(vect4);
}



