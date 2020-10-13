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

class HostName : public DataBase
{
protected:
    string fullName;
    string name;

public:
    HostName() = default;
    HostName(string &HostName);
    ~HostName();
    string display() { return fullName; }
    string getName() { return name; }
};
//constructor para procesar el imput

HostName::HostName(string &_HostName)
{
    this->fullName = _HostName;
    if (fullName == "-")
    {
        this->name = fullName;
    }
    else
    {
        vector<string> valores;
        stringstream check1(_HostName);
        string intermediate;
        while (getline(check1, intermediate, '.'))
        {
            valores.push_back(intermediate);
        }
        if (valores.size() > 1)
        {
            this->name = valores[0];
        }
        else
        {
            this->name = "unknown";
            this->fullName = "unknown";
        }
    }
}
HostName::~HostName()
{
}
