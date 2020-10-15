/* 
clase para procesar y ordenar las fechas
javier alejandro martinez noe y Ricardo Uraga
27/9/20
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DataBase.hpp"
using namespace std;
#pragma once

class Fecha : public DataBase
{
protected:
    string fullFecha;
    int year;
    int mes;
    int dia;

public:
    Fecha() = default;
    Fecha(string Fecha);
    ~Fecha();
    int getDia() { return dia; }
    int getMes() { return mes; }
    int getYear() { return year; }
    string display() { return fullFecha; }
};
//constructor para procesar el imput

Fecha::Fecha(string Fecha)
{
    this->fullFecha = Fecha;
    vector<string> valores;
    stringstream check1(Fecha);
    string intermediate;

    while (getline(check1, intermediate, '-'))
    {
        valores.push_back(intermediate);
    }

    this->dia = stoi(valores[0]);
    this->mes = stoi(valores[1]);
    this->year = stoi(valores[2]);
}

Fecha::~Fecha()
{
}
