/* 
clase para regitrar datos abstractos
javier alejandro martinez noe y Ricardo Uraga
27/9/20
*/
#include <iostream>
#include <vector>

#include "Fecha.hpp"
#include "Hora.hpp"
#include "HostName.hpp"
#include "IP.hpp"
#include "Puerto.hpp"
using namespace std;
#pragma once

class ADT {
   protected:
    int indice;
    Fecha fecha;
    Hora hora;
    IP IPOrigen;
    IP IPDestino;
    HostName HostOrigen;
    HostName HostDestino;
    Puerto PuertoOrigen;
    Puerto PuertoDestino;

   public:
    ADT() = default;
    ADT(vector<string> &_lista, int _indice);
    ~ADT();
    int getIndice() { return indice; }
    Fecha getFecha() { return fecha; }
    Hora getHora() { return hora; }
    IP getIPO() { return IPOrigen; }
    IP getIPD() { return IPDestino; }
    HostName getHostO() { return HostOrigen; }
    HostName getHostD() { return HostDestino; }
    Puerto getPuertoO() { return PuertoOrigen; }
    Puerto getPuertoD() { return PuertoDestino; }

    string getFechaDisplay() { return fecha.display(); }
    string getHoraDisplay() { return hora.display(); }
    string getIPODisplay() { return IPOrigen.display(); }
    string getIPDDisplay() { return IPDestino.display(); }
    string getHostODisplay() { return HostOrigen.display(); }
    string getHostDDisplay() { return HostDestino.display(); }
    string getPuertoODisplay() { return PuertoOrigen.display(); }
    string getPuertoDDisplay() { return PuertoDestino.display(); }
};
//constructor para procesar las diferentes entradas del vector
ADT::ADT(vector<string> &_lista, int _indice) {
    this->indice = _indice;
    this->fecha = Fecha(_lista[0]);
    this->hora = Hora(_lista[1]);
    this->IPOrigen = IP(_lista[2]);
    this->PuertoOrigen = Puerto(_lista[3]);
    this->HostOrigen = HostName(_lista[4]);
    this->IPDestino = IP(_lista[5]);
    this->PuertoDestino = Puerto(_lista[6]);
    this->HostDestino = HostName(_lista[7]);
}

ADT::~ADT() {
}
