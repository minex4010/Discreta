#include "pch.h"
#include "KarnaughMap.h"

KarnaughMap::KarnaughMap() {
    filas = 2;
    columnas = 2;
    mapa.resize(filas);
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            mapa[i].push_back(Celda(i, j, 0));
        }
    }
}

void KarnaughMap::configurarCelda(int fila, int columna, int valor) {
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) {
        mapa[fila][columna].setValor(valor);
    }
}

int KarnaughMap::obtenerValorCelda(int fila, int columna) {
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) {
        return mapa[fila][columna].getValor();
    }
    return -1;
}