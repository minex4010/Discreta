#pragma once
#include "Celda.h"
#include <vector>

class Agrupamiento
{
private:
    std::vector<Celda> celdasAgrupadas;
public:
    Agrupamiento() {}
    void agregarCelda(Celda c) { celdasAgrupadas.push_back(c); }
};