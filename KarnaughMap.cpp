#include "pch.h"
#include "KarnaughMap.h"

KarnaughMap::KarnaughMap(int vars) {
    numVariables = vars;
    filas = 2;
    columnas = (numVariables == 2) ? 2 : 4; 
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
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) return mapa[fila][columna].getValor();
    return -1;
}

string KarnaughMap::resolverMapa() {
    Expresion expr(numVariables);
    vector<vector<bool>> cubierto(filas, vector<bool>(columnas, false));

    if (numVariables == 2) {
   
    }
    else if (numVariables == 3) {
        bool todosUnos = true;
        for (int i = 0; i < filas; i++) for (int j = 0; j < columnas; j++) if (mapa[i][j].getValor() == 0) todosUnos = false;

        if (todosUnos) return "1";
        for (int i = 0; i < 2; i++) {
            if (mapa[i][0].getValor() == 1 && mapa[i][1].getValor() == 1 && mapa[i][2].getValor() == 1 && mapa[i][3].getValor() == 1) {
                Agrupamiento g;
                for (int j = 0; j < 4; j++) { g.agregarCelda(mapa[i][j]); cubierto[i][j] = true; }
                expr.agregarGrupo(g);
            }
        }
   
        for (int j = 0; j < 4; j++) {
            int j2 = (j + 1) % 4;
            if (mapa[0][j].getValor() == 1 && mapa[0][j2].getValor() == 1 &&
                mapa[1][j].getValor() == 1 && mapa[1][j2].getValor() == 1) {
                if (!cubierto[0][j] || !cubierto[0][j2] || !cubierto[1][j] || !cubierto[1][j2]) {
                    Agrupamiento g;
                    g.agregarCelda(mapa[0][j]); g.agregarCelda(mapa[0][j2]);
                    g.agregarCelda(mapa[1][j]); g.agregarCelda(mapa[1][j2]);
                    expr.agregarGrupo(g);
                    cubierto[0][j] = true; cubierto[0][j2] = true; cubierto[1][j] = true; cubierto[1][j2] = true;
                }
            }
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                int j2 = (j + 1) % 4;
                if (mapa[i][j].getValor() == 1 && mapa[i][j2].getValor() == 1) {
                    if (!cubierto[i][j] || !cubierto[i][j2]) {
                        Agrupamiento g;
                        g.agregarCelda(mapa[i][j]); g.agregarCelda(mapa[i][j2]);
                        expr.agregarGrupo(g);
                        cubierto[i][j] = true; cubierto[i][j2] = true;
                    }
                }
            }
        }
    
        for (int j = 0; j < 4; j++) {
            if (mapa[0][j].getValor() == 1 && mapa[1][j].getValor() == 1) {
                if (!cubierto[0][j] || !cubierto[1][j]) {
                    Agrupamiento g;
                    g.agregarCelda(mapa[0][j]); g.agregarCelda(mapa[1][j]);
                    expr.agregarGrupo(g);
                    cubierto[0][j] = true; cubierto[1][j] = true;
                }
            }
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if (mapa[i][j].getValor() == 1 && !cubierto[i][j]) {
                    Agrupamiento g; g.agregarCelda(mapa[i][j]);
                    expr.agregarGrupo(g);
                    cubierto[i][j] = true;
                }
            }
        }
    }
    return expr.obtenerEcuacionFinal();
}