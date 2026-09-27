#include "pch.h"
#include "Expresion.h"

Expresion::Expresion(int vars) {
    numVars = vars;
}

void Expresion::agregarGrupo(Agrupamiento g) {
    grupos.push_back(g);
}

string Expresion::obtenerEcuacionFinal() {
    if (grupos.empty()) return "0";

    string ecuacion = grupos[0].obtenerTermino(numVars);

    for (size_t i = 1; i < grupos.size(); ++i) {
        ecuacion += " + " + grupos[i].obtenerTermino(numVars);
    }
    return ecuacion;
}