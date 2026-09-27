#pragma once
#include "Celda.h"
#include "Expresion.h"
#include <vector>
#include <string>

using namespace std;

class KarnaughMap
{
private:
    vector<vector<Celda>> mapa;
    int filas;
    int columnas;
    int numVariables;

public:
    KarnaughMap(int vars); 
    void configurarCelda(int fila, int columna, int valor);
    int obtenerValorCelda(int fila, int columna);
    string resolverMapa();
};