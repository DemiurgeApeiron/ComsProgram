#include <iostream>
#include <vector>
#include "Puerto.hpp"
#include "HostName.hpp"
#include "IP.hpp"
#include "Fecha.hpp"
#include "Hora.hpp"
using namespace std;
#pragma once

template <class T>
class ADT
{
protected:
    Fecha<T> fecha;
    Hora<T>  hora;
    IP<T>  IPOrigen;
    IP<T>  IPDestino;
    HostName<T>  HostOrigen;
    HostName<T>  HostDestino;
    Puerto<T>  PuertoOrigen;
    Puerto<T>  PuertoDestino;

public:
    ADT()=default;
    ADT(vector<T> &_lista);
    ~ADT();
    Fecha<T> getFecha(){return fecha;}
    Hora<T> getHora(){return hora;}
    IP<T> getIPO(){return IPOrigen;}
    IP<T> getIPD(){return IPDestino;}
    HostName<T> getHostO(){return HostOrigen;}
    HostName<T> getHostD(){return HostDestino;}
    Puerto<T> getPuertoO(){return PuertoOrigen;}
    Puerto<T> getPuertoD(){return PuertoDestino;}
    
    string getFechaDisplay(){return fecha.display();}
    string getHoraDisplay(){return hora.display();}
    string getIPODisplay(){return IPOrigen.display();}
    string getIPDDisplay(){return IPDestino.display();}
    string getHostODisplay(){return HostOrigen.display();}
    string getHostDDisplay(){return HostDestino.display();}
    string getPuertoODisplay(){return PuertoOrigen.display();}
    string getPuertoDDisplay(){return PuertoDestino.display();}
    
};
template <class T>
ADT<T>::ADT(vector<T> &_lista){
    this-> fecha = Fecha(_lista[0]);
    this-> hora = Hora(_lista[1]);
    this-> IPOrigen = IP(_lista[2]);
    this-> PuertoOrigen = Puerto(_lista[3]);
    this-> HostOrigen = HostName(_lista[4]);
    this-> IPDestino = IP(_lista[5]);
    this-> PuertoDestino = Puerto(_lista[6]);
    this-> HostDestino = HostName(_lista[7]);
}
template <class T>
ADT<T>::~ADT()
{
}
