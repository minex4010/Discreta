#pragma once
#include "Agrupamiento.h"
#include <vector>
#include <string>

class Expresion
{
private:
    std::vector<Agrupamiento> grupos;
public:
    Expresion() {}
    std::string obtenerEcuacionFinal() { return ""; } 
};