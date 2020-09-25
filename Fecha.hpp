#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DataBase.hpp"
using namespace std;
#pragma once

template <class T>
class Fecha : public DataBase<T>{
protected:
    T fullFecha;
    int year;
    int mes;
    int dia;
public:
    Fecha()=default;
    Fecha(T Fecha);
    ~Fecha();
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getYear(){return year;}
    T display(){return fullFecha;}
};
template <class T>
Fecha<T>::Fecha(T Fecha){
    this->fullFecha= Fecha;
    vector <string> valores;
    stringstream check1(Fecha); 
    string intermediate; 

    while(getline(check1, intermediate, '-')) 
    { 
        valores.push_back(intermediate); 
    } 

    this-> dia = stoi(valores[0]);
    this-> mes = stoi(valores[1]);
    this-> year = stoi(valores[2]);
}
template <class T>
Fecha<T>::~Fecha(){
}

