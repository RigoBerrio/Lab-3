#ifndef DESENCRIPTAR_H
#define DESENCRIPTAR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include "encriptar.h"

using namespace std;

void desencriptar();
vector<int> primerMet2(vector<int> VectBin, int n);
vector<int> segMet2(vector<int> VectBin, int n);
vector<char> decodificado2(vector<int>);

#endif // DESENCRIPTAR_H
