/* 
clase para almacenar computadores y sus conexiones 
javier alejandro martinez noe y Ricardo Uraga
15/10/20
*/
#include <iostream>
#include <queue>
#include <stack>

#include "IP.hpp"
#pragma once
using namespace std;

class ConexionesComputadora {
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
    string getComputerIP() { return ip.display(); }
    string getComputerIPUser() { return ip.getUserIP(); }
    string getComputerIPLocal() { return ip.getLocalIp(); }
    stack<IP> getConexionesEntrantes() { return ConexionesEntrantes; }
    vector<IP> getConexionesSalientesV() { return ConexionesSalientesV; }
    stack<int> getConexionesEntrantesIndice() {
        return ConexionesEntrantesIndice;
    }
    vector<int> getConexionesSalientesVIndice() {
        return ConexionesSalientesVndice;
    }
    string getName() { return nombre; }
    void setName(string name);
};

ConexionesComputadora::ConexionesComputadora(IP IPFuente) {
    this->ip = IPFuente;
}

ConexionesComputadora::~ConexionesComputadora() {}

// este metodo guarda las conexiones
void ConexionesComputadora::conexion(IP _ip, int _indice) {
    // cout << ip.display() << " = " << _ip.display() << endl;

    if (ip.display() != _ip.display()) {
        ConexionesEntrantes.push(_ip);
        ConexionesEntrantesIndice.push(_indice);
    } else {
        ConexionesSalientesV.push_back(_ip);
        ConexionesSalientesVndice.push_back(_indice);
    }
}
// este metodo establece el nombre
void ConexionesComputadora::setName(string name) { this->nombre = name; }
