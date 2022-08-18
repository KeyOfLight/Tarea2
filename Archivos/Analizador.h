#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include<bits/stdc++.h>
#include "Comando.cpp"

using namespace std;

class Analizador{
    public:
        Comando cmd;
        vector<string> split_txt(string entrada);
        string replace_txt(string str, const string& from, const string& to);
        void analizar(string entrada);
        void identificarParametros(string comando,vector<string> parametros);
};
