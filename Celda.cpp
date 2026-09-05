#include "pch.h"
#include "Celda.h"

Celda::Celda(int f, int c, int v) {
    fila = f;
    columna = c;
    valor = v;
}

int Celda::getValor() {
    return valor;
}

void Celda::setValor(int v) {
    if (v == 0 || v == 1) {
        valor = v;
    }
}

int Celda::getFila() { return fila; }
int Celda::getColumna() { return columna; }