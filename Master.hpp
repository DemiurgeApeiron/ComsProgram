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
class Master{
protected:
    vector<vector <DataBase<T>> > lista;
    bool dayCond(vector<DataBase<T>*> &a, vector<DataBase<T>*> &b);
    bool dayBusquedaCond(vector<DataBase<T>*> &a, T &num);
    bool horaCond(vector<DataBase<T>*> &a, vector<DataBase<T>*> &b);
    void quickSort(vector<vector<DataBase<T>*>> &list, int low, int high);
    int partition(vector<vector<DataBase<T>*>> &list, int low, int high);
    int busqueda(bool (Master<T>::*compare)(vector<DataBase<T>*> &a, T &num), T var);
    int busquedaArbol(int primer, int ultimo, bool (Master<T>::*compare)(vector<DataBase<T>*> &a, T &num), T var);
    bool puertoMinBusquedaCond(vector<DataBase<T>*> &a, T &num);
    void printVector(vector<DataBase<T>*> list);


public:
    Master()=default;
    ~Master();
    void addRegister(std::vector<T> &_lista);
    vector<vector<DataBase<T>*>>  sortByTime();
    int numeroDeRegistros(){return lista.size();}
    void Display(int resp);
    int busquedaDia(T num);
    int busquedaMinpuerto(T num);
    

};

template <class T>
Master<T>::~Master(){
    /*for(size_t i = 0; i < lista.size();i++){
        for(size_t j = 0; j < lista.size();j++){
            delete(lista[i][j]);
        }
    }*/
}

template <class T>
void Master<T>::addRegister(vector<T> &_lista){
    vector<DataBase<T>> v;
    cout << "Fecha->" <<endl;
    v.push_back(Fecha(_lista[0]));
    cout << "Hora->" <<endl;
    v.push_back(Hora(_lista[1]));
    cout << "Ip->" <<endl;
    v.push_back(IP(_lista[2]));
    cout << "Puerto->" <<endl;
    v.push_back(Puerto(_lista[3]));
    cout << "Host->" <<endl;
    v.push_back(HostName(_lista[4]));
    cout << "IP D->" <<endl;
    v.push_back(IP(_lista[5]));
    cout << "Puerto D->" <<endl;
    v.push_back(Puerto(_lista[6]));
    cout << "Host D->" <<endl;
    v.push_back(HostName(_lista[7]));

    lista.push_back(v);
    
}

template <class T>
vector<vector<DataBase<T>*>> Master<T>:: sortByTime(){
    quickSort(lista, 0, lista.size()-1);
    return(lista); 
}
template <class T>
void Master<T>::quickSort(vector<vector<DataBase<T>*>> &list, int low, int high){
    if(low < high){
        int piv = partition(list,low, high);
        quickSort(list,low, piv-1);
        quickSort(list,piv+1, high);
    }
}
template <class T>
int Master<T>::partition(vector<vector<DataBase<T>*>> &list, int low, int high){
    vector<DataBase<T>*> pivote = lista[high];
    int i = low-1;

    for (int j = low; j < high; j++){
        Fecha<T> tempFechaA = dynamic_cast<Fecha<T>&>(lista[j][0]);
        Fecha<T> tempFechaB = dynamic_cast<Fecha<T>&>(pivote[0]);
        if((tempFechaA.getAño() == tempFechaB.getAño()) && (tempFechaA.getMes() == tempFechaB.getMes()) && (tempFechaA.getDia() == tempFechaB.getDia())){
            if(horaCond(lista[j],pivote)){
                i++;
                vector<DataBase<T>*> temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
        else if(dayCond(lista[j],pivote)){
            i++;
            vector<DataBase<T>*> temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    vector<DataBase<T>*> temp = list[i+1];
    list[i+1] = list[high];
    list[high] = temp;
    return i + 1;
    

}

template <class T>
bool Master<T>::dayCond(vector<DataBase<T>> &a, vector<DataBase<T>> &b){
    Fecha<T> tempFechaA = dynamic_cast<Fecha<T>&>(a[0]);
    Fecha<T> tempFechaB = dynamic_cast<Fecha<T>&>(b[0]);
    if(tempFechaA.getAño() < tempFechaB.getAño()){
        return(true);
    }
    else if((tempFechaA.getAño() == tempFechaB->getAño()) && (tempFechaA.getMes() < tempFechaB.getMes())){
        return(true);
    }
    else if((tempFechaA.getAño() == tempFechaB->getAño()) && (tempFechaA.getMes() == tempFechaB.getMes()) && (tempFechaA.getDia() < tempFechaB.getDia())){
        return(true);
    }
    else
    {
        return(false);
    }
}

template <class T>
bool Master<T>::horaCond(vector<DataBase<T>*> &a, vector<DataBase<T>*> &b){
    Hora<T> tempHoraA = dynamic_cast<Hora<T>&>(a[1]);
    Hora<T> tempHoraB = dynamic_cast<Hora<T>&>(b[1]);
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
    for(size_t i = 0; i < lista.size(); i++){
        Fecha<T> tempFecha = dynamic_cast<Fecha<T>&>(lista[i][0]);
        Hora<T> tempHora = dynamic_cast<Hora<T>&>(lista[i][1]);
        IP<T> tempIP = dynamic_cast<IP<T>&>(lista[i][2]);
        Puerto<T> tempPuerto = dynamic_cast<Puerto<T>&>(lista[i][3]);
        HostName<T> tempHost = dynamic_cast<HostName<T>&>(lista[i][4]);
        IP<T> tempIPD = dynamic_cast<IP<T>&>(lista[i][5]);
        Puerto<T> tempPuertoD = dynamic_cast<Puerto<T>&>(lista[i][6]);
        HostName<T> tempHostD = dynamic_cast<HostName<T>&>(lista[i][7]);
        
        cout<< tempFecha.display() << ", " << tempHora.display() << ", " << tempIP.display() << ", " << "tempPuerto->display()" << ", " << tempHost.display() << ", " << tempIPD.display() << ", " << "tempPuertoD->display()" << ", " << tempHostD.display() <<endl;   
    }
}

template <class T>
void Master<T>::printVector(vector<DataBase<T>> list){
    Fecha<T> tempFecha = dynamic_cast<Fecha<T>&>(list[0]);
    Hora<T> tempHora = dynamic_cast<Hora<T>&>(list[1]);
    IP<T> tempIP = dynamic_cast<IP<T>&>(list[2]);
    Puerto<T> tempPuerto = dynamic_cast<Puerto<T>&>(list[3]);
    HostName<T> tempHost = dynamic_cast<HostName<T>&>(list[4]);
    IP<T> tempIPD = dynamic_cast<IP<T>&>(list[5]);
    Puerto<T> tempPuertoD = dynamic_cast<Puerto<T>&>(list[6]);
    HostName<T> tempHostD = dynamic_cast<HostName<T>&>(list[7]);
        
    cout<< tempFecha.display() << ", " << tempHora.display() << ", " << tempIP.display() << ", " << "tempPuerto->display()" << ", " << tempHost.display() << ", " << tempIPD.display() << ", " << "tempPuertoD->display()" << ", " << tempHostD.display() <<endl;
}
template <class T>
int Master<T>:: busqueda(bool (Master<T>::*compare)(vector<DataBase<T>*> &a, T &num), T var){
    busquedaArbol(0,lista.size()-1, (compare), var);
}
template <class T>
int Master<T>:: busquedaArbol(int primer, int ultimo, bool (Master<T>::*compare)(vector<DataBase<T>*> &a, T &num), T var){
    if(ultimo < primer){
        return -1;
    }
    int medio = (primer + ultimo)/2;

    if((this->*compare)(lista[medio], var)){
        printVector(lista[medio]);
    }
    int izquierda = busquedaArbol(primer, medio-1, (compare), var);
    int derecha = busquedaArbol(medio+1, ultimo, (compare), var);
    if(derecha != -1){
        return derecha;
    }
    else if(izquierda != -1){
        return izquierda;
    }
    else{
        return -1;
    }
    
}

template <class T>
bool Master<T>:: dayBusquedaCond(vector<DataBase<T>*> &a, T &num){
    Fecha<T>* tempFecha = dynamic_cast<Fecha<T>*>(a[0]);
    if(tempFecha->getDia() == stoi(num)){
        return(true);
    }
    return(false);
}
template <class T>
bool Master<T>:: puertoMinBusquedaCond(vector<DataBase<T>*> &a, T &num){
    Puerto<T>* tempPuerto = dynamic_cast<Puerto<T>*>(a[0]);
    if(tempPuerto->getPort() < num){
        return(true);
    }
    return(false);
}

template <class T>
int Master<T>:: busquedaDia(T num){
    busqueda(&Master<T>::dayBusquedaCond, num);
}
template <class T>
int Master<T>:: busquedaMinpuerto(T num){
    busqueda(&puertoMinBusquedaCond, num);
}


