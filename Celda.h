#pragma once

class Celda
{
private:
    int valor;  
    int fila;
    int columna;

public:
    Celda(int f = 0, int c = 0, int v = 0);
    int getValor();
    void setValor(int v);
    int getFila();
    int getColumna();
};