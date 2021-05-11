#ifndef ENCRIPTAR_H
#define ENCRIPTAR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string.h>

using namespace std;

void encriptar();
vector<int>conversion(vector<int>);
vector<int> frstmetod(vector<int>, int);
vector<int> sndmetod(vector<int>, int);
vector<vector<int>>blockNbits(vector<int>, int);
vector<int>ConVect(vector<vector<int>>);

#endif // ENCRIPTAR_H

