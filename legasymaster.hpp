/* 
clase para procesar y ordenar los datos
javier alejandro martinez noe
27/9/20
*/
#include <iostream>
#include <vector>
#include "ADT.hpp"
using namespace std;
#pragma once

template <class T>
class Master{
protected:
    vector<ADT<T>> lista;
    vector<string> allServices;
    vector<string> activePorts;
    bool dayCond(ADT<T> &a, ADT<T> &b);
    bool timeCond(ADT<T> &a, ADT<T> &b);
    bool dayBusquedaCond(ADT<T> &a, T &num);
    bool horaCond(ADT<T> &a, ADT<T> &b);
    void quickSort(vector<ADT<T>> &list, int low, int high, bool (Master<T>::*compare)(ADT<T> &a, ADT<T> &b));
    int partition(vector<ADT<T>> &list, int low, int high, bool (Master<T>::*compare)(ADT<T> &a, ADT<T> &b));
    int busqueda(bool (Master<T>::*compare)(ADT<T> &a, T &num), T var, bool PrintBool);
    int busquedaArbol(int primer, int ultimo, bool (Master<T>::*compare)(ADT<T> &a, T &num), T var, int &contador, bool PrintBool);
    bool puertoMinBusquedaCond(ADT<T> &a, T &num);
    void printVector(ADT<T> list);
    bool OrdenadorBusquedaCond(ADT<T> &a, T &name);
    bool ServicioBusquedaCond(ADT<T> &a, T &name);
    bool busquedaUsuarioCompletoCond(ADT<T> &a, T &name);
    bool getAllServicesCond(ADT<T> &a, T &name);
    bool getActivePortsDestinyCond(ADT<T> &a, T &name);
    bool getActivePortsOriginCond(ADT<T> &a, T &name);

public:
    Master()=default;
    ~Master();
    void addRegister(std::vector<T> &_lista);
    vector<ADT<T>> sortByTime();
    int numeroDeRegistros(){return lista.size();}
    void Display(int resp);
    int busquedaDia(T num, bool PrintBool);
    int busquedaMinpuerto(T num, bool PrintBool);
    int diaRelativo(int _dia, bool sort);
    int busquedaServicio(T nombre, bool PrintBool);
    int busquedaOrdenador(T nombre, bool PrintBool);
    int busquedaUsuarioCompleto(T nombre, bool PrintBool);
    string conseguirIpLocal();
    vector<string> GetAllServices();
    vector<string> getActivePortsDestiny();
    vector<string> getActivePortsOrigin();
};

template <class T>
Master<T>::~Master(){
}
//metodo para incluir los registros a la clase abstracta
template <class T>
void Master<T>::addRegister(vector<T> &_lista){
    ADT<T> registro = ADT(_lista);
    lista.push_back(registro);
    
}
//metodo para ordenar los registros por fecha
template <class T>
vector<ADT<T>>  Master<T>:: sortByTime(){
    quickSort(lista, 0, lista.size()-1, &Master<T>::timeCond);
    return(lista); 
}
//metodo de ordenamiento Quick Sort
template <class T>
void Master<T>::quickSort(vector<ADT<T>>  &list, int low, int high, bool (Master<T>::*compare)(ADT<T> &a, ADT<T> &b)){
    if(low < high){
        int piv = partition(list,low, high, (compare));
        quickSort(list,low, piv-1, (compare));
        quickSort(list,piv+1, high, (compare));
    }
}
//metodo que trbaja en conjunto con quicksort y hace las comparaciones 
template <class T>
int Master<T>::partition(vector<ADT<T>> &list, int low, int high, bool (Master<T>::*compare)(ADT<T> &a, ADT<T> &b)){
    ADT<T> pivote = lista[high];
    int i = low-1;

    for (int j = low; j < high; j++){
        if((this->*compare)(lista[j],pivote)){
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
//metodo para comparar fechas y hora
template <class T>
bool Master<T>::timeCond(ADT<T> &a, ADT<T> &b){
    Fecha<T> tempFechaA = a.getFecha();
    Fecha<T> tempFechaB = b.getFecha();
    int tiempoFechaTotalA = tempFechaA.getYear()*365 + tempFechaA.getMes()*30 + tempFechaA.getDia();
    int tiempoFechaTotalB = tempFechaB.getYear()*365 + tempFechaB.getMes()*30 + tempFechaB.getDia();
    if(tiempoFechaTotalA < tiempoFechaTotalB){
        return(true);
    }
    else{
        Hora<T> tempHoraA = a.getHora();
        Hora<T> tempHoraB = b.getHora();
        int tiempoHoraTotalA = tempHoraA.getHora()*3600 + tempHoraA.getMin()*60 + tempHoraA.getSec();
        int tiempoHoraTotalB = tempHoraB.getHora()*3600 + tempHoraB.getMin()*60 + tempHoraB.getSec();
        if(tiempoHoraTotalA < tiempoHoraTotalB){
            return(true);
        }
        return(false);
    }
}
//metodo para comparar fechas
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
//metodo para comparar horas
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
// funcion para imprimir el registro el input es cuatas filas quieres imprimir. 0 es todas 
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
//funcion para imprimir un solo registro
template <class T>
void Master<T>::printVector(ADT<T> list){
    cout<< list.getFechaDisplay() << ", " << list.getHoraDisplay() << ", " << list.getIPODisplay() << ", " << list.getPuertoODisplay() << ", " << list.getHostODisplay() << ", " << list.getIPDDisplay() << ", " << list.getPuertoDDisplay() << ", " << list.getHostDDisplay() <<endl;
}
//funcion para iniciar las busquedas
template <class T>
int Master<T>:: busqueda(bool (Master<T>::*compare)(ADT<T> &a, T &num), T var, bool PrintBool){
    int contador = 0;
    return(busquedaArbol(0,lista.size()-1, (compare), var, contador, PrintBool));
}
//funcion para hacer una busqueda
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
//funcion para buscar una fecha espesifica
template <class T>
bool Master<T>:: dayBusquedaCond(ADT<T> &a, T &num){
    Fecha<T> tempFecha = a.getFecha();
    if(tempFecha.getDia() == stoi(num)){
        return(true);
    }
    return(false);
}
//funcion para buscar el puerto mas chico
template <class T>
bool Master<T>:: puertoMinBusquedaCond(ADT<T> &a, T &num){
    Puerto<T> tempPuerto = a.getPuertoD();
    if(tempPuerto.getPuerto() < stoi(num)){
        return(true);
    }
    return(false);
}
//funcion para buscar un usuario
template <class T>
bool Master<T>:: OrdenadorBusquedaCond(ADT<T> &a, T &name){
    HostName<T> tempHost = a.getHostO();
    if(tempHost.getName() == name){
        return(true);
    }
    return(false);
}
//funcion para buscar un servicio en espesifico
template <class T>
bool Master<T>:: ServicioBusquedaCond(ADT<T> &a, T &name){
    HostName<T> tempHost = a.getHostD();
    if(tempHost.getName() == name){
        return(true);
    }
    return(false);
}
//busqueda de un usuario por nombre completo
template <class T>
bool Master<T>::busquedaUsuarioCompletoCond(ADT<T> &a, T &name){
  HostName<T> tempCompleto = a.getHostO();
  if (tempCompleto.display() == name){
    return (true);
  }
  return (false);
}
//metodo para encontrar todos los servicios
template <class T>
bool Master<T>::getAllServicesCond(ADT<T> &a, T &name){
HostName<T> servicioTemp = a.getHostD();
    if (find(allServices.begin(), allServices.end(), servicioTemp.getName()) != allServices.end()){
        return (false);
    }
    else{
        allServices.push_back(servicioTemp.getName());
        return (true);
    }
}
//metodo para encontrar todos los puertos de destino sin repeticion
template <class T>
bool Master<T>::getActivePortsDestinyCond(ADT<T> &a, T &name){
Puerto<T> portDTemp = a.getPuertoD();
    if (find(activePorts.begin(), activePorts.end(), portDTemp.display()) != activePorts.end()){
        return (false);
    }
    else{
        activePorts.push_back(portDTemp.display());
        return (true);
    }
}
//metodo para encontrar todos los puertos de origen sin repeticion
template <class T>
bool Master<T>::getActivePortsOriginCond(ADT<T> &a, T &name){
Puerto<T> portOTemp = a.getPuertoO();
    if (find(activePorts.begin(), activePorts.end(), portOTemp.display()) != activePorts.end()){
        return (false);
    }
    else{
        activePorts.push_back(portOTemp.display());
        return (true);
    }
}
// metodo para iniciar la busqueda de un dia
template <class T>
int Master<T>:: busquedaDia(T num, bool PrintBool){
    return(busqueda(&Master<T>::dayBusquedaCond, num, PrintBool));
}
// metodo para iniciar la busqueda de un puerto minimo a un punto
template <class T>
int Master<T>:: busquedaMinpuerto(T num, bool PrintBool){
    return(busqueda(&Master<T>::puertoMinBusquedaCond, num, PrintBool));
}
// metodo para iniciar la busqueda de un servicio
template <class T>
int Master<T>:: busquedaServicio(T nombre, bool PrintBool){
    return(busqueda(&Master<T>::ServicioBusquedaCond, nombre, PrintBool));
}
// metodo para iniciar la busqueda de un usuario
template <class T>
int Master<T>:: busquedaOrdenador(T nombre, bool PrintBool){
    return(busqueda(&Master<T>::OrdenadorBusquedaCond, nombre, PrintBool));
}
// metodo para iniciar la busqueda de un usuario por nombre completo
template <class T>
int Master<T>:: busquedaUsuarioCompleto(T nombre, bool PrintBool){
    return(busqueda(&Master<T>::busquedaUsuarioCompletoCond, nombre, PrintBool));
}
// metodo para iniciar la busqueda de un dia relativo
template <class T>
int Master<T>:: diaRelativo(int _dia, bool sort){
    if(sort){
        sortByTime();
    }
    Fecha<T> fecha = lista[0].getFecha();
    return(fecha.getDia()+ _dia -1);
}
// metodo para iniciar la busqueda de todos los servicios
template<class T>
vector<string> Master<T>:: GetAllServices(){
    busqueda(&Master<T>::getAllServicesCond, "-", false);
    return(allServices);
}
// metodo para iniciar la busqueda de tosos los puertos activos de destino
template<class T>
vector<string> Master<T>:: getActivePortsDestiny(){
    activePorts.clear();
    busqueda(&Master<T>::getActivePortsDestinyCond, "-", false);
    return(activePorts);
}
// metodo para iniciar la busqueda de todos los puertos activos de origen
template<class T>
vector<string> Master<T>:: getActivePortsOrigin(){
    activePorts.clear();
    busqueda(&Master<T>::getActivePortsOriginCond, "-", false);
    return(activePorts);
}
// metodo para consegir la ip local
template<class T>
string Master<T>::conseguirIpLocal(){
  int indice = 0;
  IP<T> tempUser = lista[indice].getIPO();
  while (tempUser.getLocalIp() == "0"){
    indice++;
    tempUser = lista[indice].getIPO();
  }
  return(tempUser.getLocalIp() + ".0");
}


