#pragma once
#include "Agrupamiento.h"
#include <vector>
#include <string>

using namespace std;

class Expresion
{
private:
    vector<Agrupamiento> grupos;
    int numVars;
public:
    Expresion(int vars);
    void agregarGrupo(Agrupamiento g);
    string obtenerEcuacionFinal();
};