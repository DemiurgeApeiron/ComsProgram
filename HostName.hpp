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
    HostName(T &HostName);
    ~HostName();
    T display(){return fullName;}
    T getName(){return name;}
};
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
        this-> name = valores[0];   
    }
}
template <class T>
HostName<T>::~HostName(){
}
