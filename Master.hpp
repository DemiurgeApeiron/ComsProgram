#include <iostream>
#include <vector>
#include "ADT.hpp"
using namespace std;
#pragma once

template <class T>
class Master{
protected:
    vector<ADT<T>> lista;
    bool dayCond(ADT<T> &a, ADT<T> &b);
    bool dayBusquedaCond(ADT<T> &a, T &num);
    bool horaCond(ADT<T> &a, ADT<T> &b);
    void quickSort(vector<ADT<T>> &list, int low, int high);
    int partition(vector<ADT<T>> &list, int low, int high);
    int busqueda(bool (Master<T>::*compare)(ADT<T> &a, T &num), T var, bool PrintBool);
    int busquedaArbol(int primer, int ultimo, bool (Master<T>::*compare)(ADT<T> &a, T &num), T var, int &contador, bool PrintBool);
    bool puertoMinBusquedaCond(ADT<T> &a, T &num);
    void printVector(ADT<T> list);
    bool OrdenadorBusquedaCond(ADT<T> &a, T &name);
    bool ServicioBusquedaCond(ADT<T> &a, T &name);


public:
    Master()=default;
    ~Master();
    void addRegister(std::vector<T> &_lista);
    vector<ADT<T>> sortByTime();
    int numeroDeRegistros(){return lista.size();}
    void Display(int resp);
    int busquedaDia(T num, bool PrintBool);
    int busquedaMinpuerto(T num, bool PrintBool);
    int diaRelativo(int _dia);
    int busquedaServicio(T nombre, bool PrintBool);
    int busquedaOrdenador(T nombre, bool PrintBool);
    

};

template <class T>
Master<T>::~Master(){
}

template <class T>
void Master<T>::addRegister(vector<T> &_lista){
    ADT<T> registro = ADT(_lista);
    lista.push_back(registro);
    
}

template <class T>
vector<ADT<T>>  Master<T>:: sortByTime(){
    quickSort(lista, 0, lista.size()-1);
    return(lista); 
}
template <class T>
void Master<T>::quickSort(vector<ADT<T>>  &list, int low, int high){
    if(low < high){
        int piv = partition(list,low, high);
        quickSort(list,low, piv-1);
        quickSort(list,piv+1, high);
    }
}
template <class T>
int Master<T>::partition(vector<ADT<T>> &list, int low, int high){
    ADT<T> pivote = lista[high];
    int i = low-1;

    for (int j = low; j < high; j++){
        Fecha<T> tempFechaA = lista[j].getFecha();
        Fecha<T> tempFechaB = pivote.getFecha();
        if((tempFechaA.getYear() == tempFechaB.getYear()) && (tempFechaA.getMes() == tempFechaB.getMes()) && (tempFechaA.getDia() == tempFechaB.getDia())){
            if(horaCond(lista[j],pivote)){
                i++;
                ADT<T> temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
        else if(dayCond(lista[j],pivote)){
            i++;
            ADT<T> temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    ADT<T> temp = list[i+1];
    list[i+1] = list[high];
    list[high] = temp;
    return i + 1;
    

}

template <class T>
bool Master<T>::dayCond(ADT<T> &a, ADT<T> &b){
    Fecha<T> tempFechaA = a.getFecha();
    Fecha<T> tempFechaB = b.getFecha();
    if(tempFechaA.getYear() < tempFechaB.getYear()){
        return(true);
    }
    else if((tempFechaA.getYear() == tempFechaB.getYear()) && (tempFechaA.getMes() < tempFechaB.getMes())){
        return(true);
    }
    else if((tempFechaA.getYear() == tempFechaB.getYear()) && (tempFechaA.getMes() == tempFechaB.getMes()) && (tempFechaA.getDia() < tempFechaB.getDia())){
        return(true);
    }
    else
    {
        return(false);
    }
}

template <class T>
bool Master<T>::horaCond(ADT<T> &a, ADT<T> &b){
    Hora<T> tempHoraA = a.getHora();
    Hora<T> tempHoraB = b.getHora();
    if(tempHoraA.getHora() < tempHoraB.getHora()){
        return(true);
    }
    else if((tempHoraA.getHora() == tempHoraB.getHora()) && (tempHoraA.getMin() < tempHoraB.getMin())){
        return(true);
    }
    else if((tempHoraA.getHora() == tempHoraB.getHora()) && (tempHoraA.getMin() == tempHoraB.getMin()) && (tempHoraA.getSec() < tempHoraB.getSec())){
        return(true);
    }
    else
    {
        return(false);
    }
}
template <class T>
void Master<T>::Display(int resp){
    size_t size;
    if(resp==0){
        size = lista.size();
    }
    else
    {
        size = resp;
    }
    for(size_t i = 0; i < size; i++){ 
        cout<< lista[i].getFechaDisplay() << ", " << lista[i].getHoraDisplay() << ", " << lista[i].getIPODisplay() << ", " << lista[i].getPuertoODisplay() << ", " << lista[i].getHostODisplay() << ", " << lista[i].getIPDDisplay() << ", " << lista[i].getPuertoDDisplay() << ", " << lista[i].getHostDDisplay() <<endl;   
    }
}

template <class T>
void Master<T>::printVector(ADT<T> list){
    cout<< list.getFechaDisplay() << ", " << list.getHoraDisplay() << ", " << list.getIPODisplay() << ", " << list.getPuertoODisplay() << ", " << list.getHostODisplay() << ", " << list.getIPDDisplay() << ", " << list.getPuertoDDisplay() << ", " << list.getHostDDisplay() <<endl;
}
template <class T>
int Master<T>:: busqueda(bool (Master<T>::*compare)(ADT<T> &a, T &num), T var, bool PrintBool){
    int contador = 0;
    return(busquedaArbol(0,lista.size()-1, (compare), var, contador, PrintBool));
}
template <class T>
int Master<T>:: busquedaArbol(int primer, int ultimo, bool (Master<T>::*compare)(ADT<T> &a, T &num), T var, int &contador, bool PrintBool){
    if(ultimo < primer){
        return contador;
    }
    int medio = (primer + ultimo)/2;

    if((this->*compare)(lista[medio], var)){
        if(PrintBool){
            printVector(lista[medio]);
        }
        contador++;
    }
    int izquierda = busquedaArbol(primer, medio-1, (compare), var, contador, PrintBool);
    int derecha = busquedaArbol(medio+1, ultimo, (compare), var, contador, PrintBool);
    return(contador);
    
}

template <class T>
bool Master<T>:: dayBusquedaCond(ADT<T> &a, T &num){
    Fecha<T> tempFecha = a.getFecha();
    if(tempFecha.getDia() == stoi(num)){
        return(true);
    }
    return(false);
}
template <class T>
bool Master<T>:: puertoMinBusquedaCond(ADT<T> &a, T &num){
    Puerto<T> tempPuerto = a.getPuertoD();
    if(tempPuerto.getPuerto() < stoi(num)){
        return(true);
    }
    return(false);
}
template <class T>
bool Master<T>:: OrdenadorBusquedaCond(ADT<T> &a, T &name){
    HostName<T> tempHost = a.getHostO();
    if(tempHost.getName() == name){
        return(true);
    }
    return(false);
}
template <class T>
bool Master<T>:: ServicioBusquedaCond(ADT<T> &a, T &name){
    HostName<T> tempHost = a.getHostD();
    if(tempHost.getName() == name){
        return(true);
    }
    return(false);
}

template <class T>
int Master<T>:: busquedaDia(T num, bool PrintBool){
    return(busqueda(&Master<T>::dayBusquedaCond, num, PrintBool));
}
template <class T>
int Master<T>:: busquedaMinpuerto(T num, bool PrintBool){
    return(busqueda(&Master<T>::puertoMinBusquedaCond, num, PrintBool));
}
template <class T>
int Master<T>:: busquedaServicio(T nombre, bool PrintBool){
    return(busqueda(&Master<T>::ServicioBusquedaCond, nombre, PrintBool));
}
template <class T>
int Master<T>:: busquedaOrdenador(T nombre, bool PrintBool){
    return(busqueda(&Master<T>::OrdenadorBusquedaCond, nombre, PrintBool));
}

template <class T>
int Master<T>:: diaRelativo(int _dia){
    sortByTime();
    Fecha<T> fecha = lista[0].getFecha();
    return(fecha.getDia()+ _dia -1);
}

