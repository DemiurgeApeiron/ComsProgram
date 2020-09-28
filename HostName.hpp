/* 
clase para procesar y ordenar los host
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
class HostName: public DataBase<T>{
protected:
    T fullName;
    T name;
public:
    HostName()=default;
    HostName(T &HostName);
    ~HostName();
    T display(){return fullName;}
    T getName(){return name;}
};
//constructor para procesar el imput
template <class T>
HostName<T>::HostName(T &_HostName){
    this-> fullName = _HostName;
    if(fullName == "-"){
        this->name = fullName;
    }
    else{
        vector <T> valores;
        stringstream check1(_HostName); 
        string intermediate; 
        while(getline(check1, intermediate, '.')) 
        { 
            valores.push_back(intermediate); 
        }
        if(valores.size() > 1){
            this-> name = valores[0]; 
        }
        else{
            this->name = "unknown";
            this->fullName = "unknown";
        }
        
          
    }
}
template <class T>
HostName<T>::~HostName(){
}
