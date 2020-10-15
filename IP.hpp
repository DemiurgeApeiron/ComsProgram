/* 
clase para procesar y ordenar las IP
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

class IP : public DataBase
{
protected:
    string localIp;
    string userIP;
    string fullIP;

public:
    IP() = default;
    IP(string IP);
    ~IP();
    string getLocalIp() { return localIp; }
    string getUserIP() { return userIP; }
    string display() { return fullIP; }
};
//constructor para procesar el imput
IP::IP(string IP)
{
    this->fullIP = IP;
    if (fullIP == "-")
    {
        this->localIp = "0";
        this->userIP = "0";
    }
    else
    {
        vector<string> valores;
        stringstream check1(IP);

        string intermediate;

        while (getline(check1, intermediate, '.'))
        {
            valores.push_back(intermediate);
        }
        if (valores.size() == 4)
        {
            this->localIp = valores[0] + "." + valores[1] + "." + valores[2];
            this->userIP = valores[valores.size() - 1];
        }
        else
        {
            this->localIp = "0";
            this->userIP = "0";
        }
    }
}
IP::~IP()
{
}
