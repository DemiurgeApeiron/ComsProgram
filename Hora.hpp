/* 
clase para procesar y ordenar las horas
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

class Hora : public DataBase
{
protected:
    int hora;
    int min;
    int sec;
    string fullHora;

public:
    Hora() = default;
    Hora(string &_hora);
    ~Hora();
    int getHora() { return hora; }
    int getMin() { return min; }
    int getSec() { return sec; }
    string display() { return fullHora; }
};
//constructor para procesar el imput

Hora::Hora(string &_hora)
{
    this->fullHora = _hora;
    vector<string> valores;
    stringstream check1(_hora);
    string intermediate;
    while (getline(check1, intermediate, ':'))
    {
        valores.push_back(intermediate);
    }
    this->hora = stoi(valores[0]);
    this->min = stoi(valores[1]);
    this->sec = stoi(valores[2]);
}

Hora::~Hora()
{
}