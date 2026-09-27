#pragma once
#include "Celda.h"
#include <vector>
#include <string>
using namespace std;

class Agrupamiento
{
private:
    vector<Celda> celdasAgrupadas;
public:
    Agrupamiento();
    void agregarCelda(Celda c);
    string obtenerTermino(int numVariables); 
};