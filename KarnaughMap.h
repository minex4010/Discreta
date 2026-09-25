#pragma once
#include "Celda.h"
#include <vector>

class KarnaughMap
{
private:
    std::vector<std::vector<Celda>> mapa;
    int filas;
    int columnas;
public:
    KarnaughMap();
    void configurarCelda(int fila, int columna, int valor);
    int obtenerValorCelda(int fila, int columna);
};