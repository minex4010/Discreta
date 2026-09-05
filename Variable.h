#pragma once
#include <string>

class Variable
{
private:
    std::string nombre;
    int valor;
public:
    Variable(std::string n = "") : nombre(n), valor(0) {}
};