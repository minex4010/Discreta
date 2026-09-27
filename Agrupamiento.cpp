#include "pch.h"
#include "Agrupamiento.h"

Agrupamiento::Agrupamiento() {}

void Agrupamiento::agregarCelda(Celda c) {
    celdasAgrupadas.push_back(c);
}

string Agrupamiento::obtenerTermino(int numVariables) {
    if (celdasAgrupadas.empty()) return "0";
    if (numVariables == 2 && celdasAgrupadas.size() == 4) return "1";
    if (numVariables == 3 && celdasAgrupadas.size() == 8) return "1";

    bool x_cambia = false, y_cambia = false, z_cambia = false;

    int x_val = celdasAgrupadas[0].getFila();
    int col0 = celdasAgrupadas[0].getColumna();

    int y_val = (col0 == 0 || col0 == 1) ? 0 : 1;
    int z_val = (col0 == 0 || col0 == 3) ? 0 : 1;

    for (size_t i = 1; i < celdasAgrupadas.size(); i++) {
        if (celdasAgrupadas[i].getFila() != x_val) x_cambia = true;

        int col = celdasAgrupadas[i].getColumna();
        int y_actual = (col == 0 || col == 1) ? 0 : 1;
        int z_actual = (col == 0 || col == 3) ? 0 : 1;

        if (y_actual != y_val) y_cambia = true;
        if (z_actual != z_val) z_cambia = true;
    }

    string termino = "";
    if (!x_cambia) termino += (x_val == 0) ? "x'" : "x";
    if (!y_cambia) termino += (y_val == 0) ? "y'" : "y";
    if (numVariables == 3 && !z_cambia) termino += (z_val == 0) ? "z'" : "z";

    return (termino == "") ? "1" : termino;
}