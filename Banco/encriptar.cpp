#include "encriptar.h"

void encriptar(){
    int SemillaCodificacion=1,opcion=0;
    char c;
    ifstream fin;
    ofstream arch2;
    vector<int>VectorCompleto;
    vector <int> vect1,VectBin;

    fin.open("clientes.txt");//abriendo el archivo creado para convertir

    if(!fin.is_open())//comprobando que el archivo esta(existe) dentro del programa
    {
        cout<<"|=======================================================|"<<endl;
        cout<<"|==================El archivo no esta===================|"<<endl;
        cout<<"|=======================================================|"<<endl;
    }

    else{

        arch2.open("auxiliar.txt", ios::out);//creando un archivo de salida

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

            fin.close();
            arch2.close();
            remove("clientes.txt");
            rename("auxiliar.txt","clientes.txt");

       }
   }
}

vector<int>conversion(vector<int> vect1){
    vector<int>vect2,ultimovect;

    for(int t=0;t<vect1.size();t++){
        int contador=0;
        vect2.clear();

        while(vect1[t]>0){
            vect2.insert(vect2.begin(),vect1[t]%2);
            contador++;
            vect1[t]=vect1[t]/2;
        }

        for(int j=0;j<8-contador;j++)
            vect2.insert(vect2.begin(),0);

        ultimovect.insert(ultimovect.end(),vect2.begin(),vect2.end());
    }
    return ultimovect;
}

vector<int> sndmetod(vector<int> VectBin, int n){
    vector<vector<int>> vect4=blockNbits(VectBin, n);
    int a=vect4.size();

    for(int i=0;i<a;i++){
        vect4[i].insert(vect4[i].begin(),vect4[i][n-1]);
        vect4[i].erase(vect4[i].end()-1);
    }

    return ConVect(vect4);
}


vector<vector<int>> blockNbits(vector<int> VectBin, int n){//funcion que divide en n bits
    int cont2=0 ,a=VectBin.size();
    vector<vector<int>> vect4((a/n),vector<int>(n));

    for(int i=0;i<a/n;i++)//dividiendo el vector en bloques de n bits

        for(int cont=0;cont<n;cont++){
            vect4[i][cont]=VectBin[cont2];
            cont2++;
        }

    return vect4;
}

vector<int>ConVect(vector<vector<int>>vect4){
    vector<int> vectotal;
    int a=vect4.size();
    for(int t=0;t<a;t++)//convirtiendo un vector de vectores, en vector lineal
        vectotal.insert(vectotal.end(),vect4[t].begin(),vect4[t].end());
    return  vectotal;
}
