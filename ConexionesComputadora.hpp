#include <iostream>
#include "IP.hpp"
#include <queue>
#include <stack>
#pragma once
using namespace std;

class ConexionesComputadora
{
protected:
    IP ip;
    string nombre;

    int LastConection;
    stack<IP> ConexionesEntrantes;
    stack<int> ConexionesEntrantesIndice;
    vector<IP> ConexionesSalientesV;
    vector<int> ConexionesSalientesVndice;

public:
    ConexionesComputadora(IP IPFuente);
    ~ConexionesComputadora();
    void conexion(IP _ip, int _indice);
    string getLastConection();
    string getComputerIP() { return ip.display(); }
    string getComputerIPUser() { return ip.getUserIP(); }
    string getComputerIPLocal() { return ip.getLocalIp(); }
    stack<IP> getConexionesEntrantes() { return ConexionesEntrantes; }
    vector<IP> getConexionesSalientesV() { return ConexionesSalientesV; }
    stack<int> getConexionesEntrantesIndice() { return ConexionesEntrantesIndice; }
    vector<int> getConexionesSalientesVIndice() { return ConexionesSalientesVndice; }
    string getName() { return nombre; }
    void setName(string name);
};

ConexionesComputadora::ConexionesComputadora(IP IPFuente)
{
    this->ip = IPFuente;
}

ConexionesComputadora::~ConexionesComputadora()
{
}

void ConexionesComputadora::conexion(IP _ip, int _indice)
{
    //cout << ip.display() << " = " << _ip.display() << endl;
    if (ip.display() != _ip.display())
    {
        this->LastConection = 0;
        ConexionesEntrantes.push(_ip);
        ConexionesEntrantesIndice.push(_indice);
    }
    else
    {
        this->LastConection = 1;
        ConexionesSalientesV.push_back(_ip);
        ConexionesSalientesVndice.push_back(_indice);
    }
}

void ConexionesComputadora::setName(string name)
{
    this->nombre = name;
}

string ConexionesComputadora::getLastConection()
{
    if (LastConection == 0)
    {
        return ConexionesEntrantes.top().display();
    }
    if (LastConection == 1)
    {
        return ConexionesSalientesV.front().display();
    }
    return "NULL";
}