#include <iostream>
#include "IP.hpp"
#include <queue>
#include <stack>

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
    void conexion(string _ip, int _indice);
    string getLastIncomingConection() { return LastConection > 0 ? ConexionesEntrantes.top().display() : ConexionesSalientesV.front().display(); }
    string getComputerIP() { return ip.display(); }
    string getComputerIPUser() { return ip.getUserIP(); }
    string getComputerIPLocal() { return ip.getLocalIp(); }
    stack<IP> getConexionesEntrantes() { return ConexionesEntrantes; }
    vector<IP> getConexionesSalientesV() { return ConexionesSalientesV; }
    stack<int> getConexionesEntrantesIndice() { return ConexionesEntrantesIndice; }
    vector<int> getConexionesSalientesVIndice() { return ConexionesSalientesVndice; }
    void setName(string name);
};

ConexionesComputadora::ConexionesComputadora(IP IPFuente)
{
    this->ip = IPFuente;
}

ConexionesComputadora::~ConexionesComputadora()
{
}

void ConexionesComputadora::conexion(string _ip, int _indice)
{
    if (ip.display() != _ip)
    {
        this->LastConection = 0;
        ConexionesEntrantes.push(IP(_ip));
        ConexionesEntrantesIndice.push(_indice);
    }
    else
    {
        this->LastConection = 1;
        ConexionesSalientesV.push_back(IP(_ip));
        ConexionesSalientesVndice.push_back(_indice);
    }
}

void ConexionesComputadora::setName(string name)
{
    this->nombre = name;
}