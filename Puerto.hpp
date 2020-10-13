/* 
clase para procesar y ordenar los puertos
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

class Puerto : public DataBase
{
protected:
    string port;
    int puerto;

public:
    Puerto() = default;
    Puerto(string _puerto);
    ~Puerto();
    int getPuerto() { return puerto; }
    string display() { return port; }
};
//constructor para procesar el imput
Puerto::Puerto(string _puerto)
{
    if (_puerto == "-")
    {
        this->port = _puerto;
    }
    else
    {
        this->puerto = stoi(_puerto);
        this->port = _puerto;
    }
}
Puerto::~Puerto()
{
}