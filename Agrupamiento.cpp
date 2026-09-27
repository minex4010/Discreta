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
    if (numVariables == 4 && celdasAgrupadas.size() == 16) return "1";

    bool x_cambia = false, y_cambia = false, z_cambia = false, w_cambia = false;

    int fila = celdasAgrupadas[0].getFila();
    int col = celdasAgrupadas[0].getColumna();

    int x_val = 0, y_val = 0, z_val = 0, w_val = 0;

    if (numVariables == 2) {
        x_val = (fila == 0) ? 0 : 1;
        y_val = (col == 0) ? 0 : 1;
    }
    else if (numVariables == 3) {
        x_val = (fila == 0) ? 0 : 1;
        y_val = (col == 0 || col == 1) ? 0 : 1;
        z_val = (col == 0 || col == 3) ? 0 : 1;
    }
    else if (numVariables == 4) {
        x_val = (fila == 0 || fila == 1) ? 0 : 1;
        y_val = (fila == 0 || fila == 3) ? 0 : 1;
        z_val = (col == 0 || col == 1) ? 0 : 1;
        w_val = (col == 0 || col == 3) ? 0 : 1;
    }

    for (size_t i = 1; i < celdasAgrupadas.size(); i++) {
        int f = celdasAgrupadas[i].getFila();
        int c = celdasAgrupadas[i].getColumna();

        if (numVariables == 2) {
            if ((f == 0 ? 0 : 1) != x_val) x_cambia = true;
            if ((c == 0 ? 0 : 1) != y_val) y_cambia = true;
        }
        else if (numVariables == 3) {
            if ((f == 0 ? 0 : 1) != x_val) x_cambia = true;
            if (((c == 0 || c == 1) ? 0 : 1) != y_val) y_cambia = true;
            if (((c == 0 || c == 3) ? 0 : 1) != z_val) z_cambia = true;
        }
        else if (numVariables == 4) {
            if (((f == 0 || f == 1) ? 0 : 1) != x_val) x_cambia = true;
            if (((f == 0 || f == 3) ? 0 : 1) != y_val) y_cambia = true;
            if (((c == 0 || c == 1) ? 0 : 1) != z_val) z_cambia = true;
            if (((c == 0 || c == 3) ? 0 : 1) != w_val) w_cambia = true;
        }
    }

    string termino = "";
    if (!x_cambia) termino += (x_val == 0) ? "X'^" : "X^";
    if (!y_cambia) termino += (y_val == 0) ? "Y'^" : "Y^";
    if (numVariables >= 3 && !z_cambia) termino += (z_val == 0) ? "Z'^" : "Z^";
    if (numVariables == 4 && !w_cambia) termino += (w_val == 0) ? "W'^" : "W^";

    if (termino.length() > 0 && termino.back() == '^') {
        termino.pop_back();
    }

    return (termino == "") ? "1" : "(" + termino + ")";
}