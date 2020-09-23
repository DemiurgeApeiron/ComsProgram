#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DataBase.hpp"
using namespace std;
#pragma once

template <class T>
class Puerto : public DataBase<T>{
protected:
    T port;
    int puerto;
public:
    Puerto(T _puerto);
    ~Puerto();
    int getPuerto(){return puerto;}
    T display(){return port;}

};
template <class T>
Puerto<T>::Puerto(T _puerto){
    if(_puerto == "-"){
        this->port = _puerto;
    }
    else{
        this->puerto = stoi(_puerto);
        this->port = _puerto;
    }
}
template <class T>
Puerto<T>::~Puerto(){
}