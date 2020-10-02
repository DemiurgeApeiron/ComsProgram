/* 
clase para procesar y ordenar las horas
javier alejandro martinez noe
27/9/20
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DataBase.hpp"
using namespace std;
#pragma once

template <class T>
class Hora: public DataBase<T>{
protected:
    int hora;
    int min;
    int sec;
    T fullHora;
public:
    Hora()=default;
    Hora(T &_hora);
    ~Hora();
    int getHora(){return hora;}
    int getMin(){return min;}
    int getSec(){return sec;}
    T display(){return fullHora;}
};
//constructor para procesar el imput
template <class T>
Hora<T>::Hora(T &_hora){
    this->fullHora = _hora;
    vector<T> valores;
    stringstream check1(_hora); 
    string intermediate; 
    while(getline(check1, intermediate, ':')) 
    { 
        valores.push_back(intermediate); 
    }
    this-> hora = stoi(valores[0]);
    this-> min = stoi(valores[1]);
    this-> sec = stoi(valores[2]);
}
template <class T>
Hora<T>::~Hora(){
}