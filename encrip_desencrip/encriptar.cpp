#include "encriptar.h"

void encriptar(){
    int n,opcion;
    char c, **cad;
    cad=new char *[3000];
    fstream fin;
    ofstream arch2;
    vector<int>VectorCompleto;
    vector <int> vect1,VectBin;
    string NomArch,ArchDeco;

   cout << "ingrese el nombre del archivo que desea abrir: "<<endl;
   cout<<endl;
   cout<<"En este caso puede abrir el archivo 'Texto_A_Codificar'"<<endl;
   cout<<endl;
   cin >>NomArch;
   NomArch+=".txt";

    fin.open(NomArch);//abriendo el archivo creado para convertir
    cout<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;

    if(!fin.is_open()){//comprobando que el archivo esta(existe) dentro del programa
        cout<<endl;
        cout<<"el archivo no esta"<<endl;
        cout<<endl;

    }

    else{

        cout<<"INGRESE EL NOMBRE PARA CREAR EL NUEVO ARCHIVO DONDE GUARDARA EL CODIFICADO:\n ";
        cout<<endl;
        cin >> ArchDeco;
        ArchDeco+=".txt";
        arch2.open(ArchDeco, ios::out);//creando un archivo de salida
        cout<<endl;
        cout<<"------------------------------------------------------------------------"<<endl;

        while (!fin.eof()) {//transformar el archivo en un vector
            fin.get(c);
            vect1.insert(vect1.end(),c);
    }

    vect1.erase(vect1.end()-1);
    VectBin=conversion(vect1); //llamando la funcion que convierte a binario

    cout<<endl;
    cout<<"INGRESE LA SEMILLA DE CODIFICACION: ";
    cin>>n;
    cout<<endl;

    cout<<"INGRESE EL METODO DE CODIFICACION: ";
    cin>>opcion;
    cout<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;

    switch(opcion){
    case 1:
        VectorCompleto=frstmetod(VectBin, n);
        break;
    case 2:
        VectorCompleto=sndmetod(VectBin, n);
        break;
    default:
        cout<<"|=======================================================================|"<<endl;
        cout<<"|==================el numero ingresado no es valido=====================|"<<endl;
        cout<<"|=======================================================================|"<<endl;
        cout<<endl;
        break;
    }
    if(VectorCompleto.size()!=0){
        for(int i=0;i<VectorCompleto.size();i++){
            arch2<<VectorCompleto[i];
        }
        if(VectBin.size()%n!=0){
            for(int i=0;i<VectBin.size()-VectorCompleto.size();i++)
                arch2<<VectBin[VectorCompleto.size()+i];
        }
        cout<<"|========================================================================|"<<endl;
        cout<<"|Proceso terminado dirijase al documento para ver el resultado codificado|"<<endl;
        cout<<"|========================================================================|"<<endl;
        cout<<endl;

        fin.close();
        arch2.close();
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

vector<int> frstmetod(vector<int> VectBin, int n){

    vector<vector<int>> vect4=blockNbits(VectBin,n);//llama la funcion que separa en bloques de n bits
    vector<vector<int>> vectContar=vect4;//variable auxiliar para contar los 1s y 0s de el bloque anterior
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
            if(vectContar[i][h]==0)
                cont0++;
            else cont1++;
        }
    }
    return ConVect(vect4);//convirtiendo un vector de vectores en un vector
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

