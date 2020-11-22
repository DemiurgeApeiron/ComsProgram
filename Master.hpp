/*
clase para procesar y ordenar los datos
javier alejandro martinez noe y Ricardo Uraga
27/9/20
*/
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "ADT.hpp"
#include "ConexionesComputadora.hpp"
#include "Graph.hpp"
#include "arbolBinarioMapNc.hpp"
using namespace std;
#pragma once

class Master {
   protected:
    vector<ADT> lista;
    vector<string> allServices;
    vector<string> activePorts;
    vector<ConexionesComputadora> listComputers;
    map<string, ConexionesComputadora> computerDictionary;
    map<string, ConexionesComputadora> dayComputerDictionary;
    map<string, string> HostIP;
    set<string> domainNames;
    BinarySearchTree BST;
    map<string, Graph<string>> IPNetwork;

    int indice = 0;
    ADT computer;
    bool dayCond(ADT &a, ADT &b);
    bool timeCondMin(ADT &a, ADT &b);
    bool timeCondMax(ADT &a, ADT &b);
    bool dayBusquedaCond(ADT &a, string &num);
    bool horaCond(ADT &a, ADT &b);
    void quickSort(vector<ADT> &list, int low, int high);
    int partition(vector<ADT> &list, int low, int high);
    int busqueda(bool (Master::*compare)(ADT &a, string &num), string var, bool PrintBool);
    int busquedaArbol(int primer, int ultimo, bool (Master::*compare)(ADT &a, string &num), string var, int &contador, bool PrintBool);
    bool puertoMinBusquedaCond(ADT &a, string &num);
    void printVector(ADT list);
    bool OrdenadorBusquedaCond(ADT &a, string &name);
    bool ServicioBusquedaCond(ADT &a, string &name);
    bool busquedaUsuarioCompletoCond(ADT &a, string &name);
    bool getAllServicesCond(ADT &a, string &name);
    bool getActivePortsDestinyCond(ADT &a, string &name);
    bool getActivePortsOriginCond(ADT &a, string &name);
    bool AddComputer(ADT &a, string &_ip);
    bool IPSearch(ConexionesComputadora a, string _ip);
    bool busquedaPorIndiceCond(ADT &a, string &_ip);
    bool computerConectionCond(ConexionesComputadora a, string _ip);
    bool singleConectionSearch(ADT &a, string &_ip);
    bool ComputerIntegration(ADT &a, string &_ip);
    vector<ADT> mergeSort(vector<ADT> &listaToMege, int primer, int ultimo, bool (Master::*compareMin)(ADT &a, ADT &b), bool (Master::*compareMax)(ADT &a, ADT &b));
    vector<ADT> merge(vector<ADT> &l, vector<ADT> &r, bool (Master::*compareMin)(ADT &a, ADT &b), bool (Master::*compareMax)(ADT &a, ADT &b));
    ConexionesComputadora *busquedaArbolConexiones(int primer, int ultimo, bool (Master::*compare)(ConexionesComputadora a, string _ip), string var, bool PrintBool);
    ConexionesComputadora *busquedaConexiones(bool (Master::*compare)(ConexionesComputadora a, string _ip), string var, bool PrintBool);
    void loadComputers(bool (Master::*compare)(ADT &a, string &num), string var);
    bool addComputerByDay(ADT &a, string &dia);
    bool dayIntegration(ADT &a, string &dia);
    bool addServicesNames(ADT &a, string &name);
    Graph<string> makeGraphOfDay(Fecha _fecha);

   public:
    Master() = default;
    ~Master();
    void addRegister(vector<string> &_lista);
    vector<ADT> sortByTime();
    int numeroDeRegistros() { return lista.size(); }
    void Display(int resp);
    int busquedaDia(string num, bool PrintBool);
    int busquedaMinpuerto(string num, bool PrintBool);
    int diaRelativo(int _dia, bool sort);
    int busquedaServicio(string nombre, bool PrintBool);
    int busquedaOrdenador(string nombre, bool PrintBool);
    int busquedaUsuarioCompleto(string nombre, bool PrintBool);
    string conseguirIpLocal();
    vector<string> GetAllServices();
    vector<string> getActivePortsDestiny();
    vector<string> getActivePortsOrigin();
    void computerAnalisis();
    string SearchByIP(int _IP);
    string getLasConection(int _IP);
    string getIncomingConection(int _IP);
    string getComputerName(int _IP);
    void fullConectionStatus(int _IP);
    int getAllIncomingConections(int _IP);
    int getAllOutgoingConections(int _IP);
    void singleConectionAssessment(int _IP);
    vector<string> getNOutOutgoingConections(int _ip, int N);
    string getComputerIP(string name);
    int getComputerWConections();
    set<string> getComputerUniqueServices();
    set<string> getComputerUniqueServicesIndividual();
    map<string, int> conexionesPorDia(Fecha _fecha);
    vector<string> top(int n, string _fecha);
    vector<vector<string>> ChronologyOfMostConections(int num);
    void getStrangeHost();
    bool checkIfConnection(string IP1, string IP2);
    void generateGraphConnections();
    vector<string> getGraphIncomingConnectionsInternal(string _fecha, int IP);
    vector<string> getGraphOutgoingConnectionsInternal(string _fecha, int IP);
    map<string, Graph<string>> tempGetIPNetwork() { return IPNetwork; }
};

Master::~Master() {
}
//metodo para incluir los registros a la clase abstracta

void Master::addRegister(vector<string> &_lista) {
    indice += 1;
    ADT registro = ADT(_lista, indice);
    lista.push_back(registro);
}
//metodo para ordenar los registros por fecha

vector<ADT> Master::sortByTime() {
    lista = mergeSort(lista, 0, lista.size() - 1, &Master::timeCondMin, &Master::timeCondMax);
    return (lista);
}
//metodo de ordenamiento Quick Sort

vector<ADT> Master::mergeSort(vector<ADT> &listaToMege, int primer, int ultimo, bool (Master::*compareMin)(ADT &a, ADT &b), bool (Master::*compareMax)(ADT &a, ADT &b)) {
    int n = listaToMege.size();
    if (primer < ultimo) {
        int medio = primer + (ultimo - primer) / 2;

        vector<ADT> izquierda = mergeSort(listaToMege, primer, medio, (compareMin), (compareMax));
        vector<ADT> derecha = mergeSort(listaToMege, medio + 1, ultimo, (compareMin), (compareMax));

        return (merge(izquierda, derecha, (compareMin), (compareMax)));
    } else {
        vector<ADT> resp;
        if (primer - ultimo != 0) {
            resp = vector<ADT>(listaToMege.begin() + primer, listaToMege.end() - (listaToMege.size() - ultimo));
        } else if (primer == 0 && ultimo == 0) {
            resp = vector<ADT>(listaToMege.begin(), listaToMege.end() - (listaToMege.size() - 1));
        } else {
            resp = vector<ADT>(listaToMege.begin() + primer, listaToMege.end() - (listaToMege.size() - ultimo - 1));
        }
        return (resp);
    }
}

vector<ADT> Master::merge(vector<ADT> &l, vector<ADT> &r, bool (Master::*compareMin)(ADT &a, ADT &b), bool (Master::*compareMax)(ADT &a, ADT &b)) {
    int n = l.size() + r.size();

    int i = 0, j = 0, x = 0, y = 0;
    vector<ADT> result;
    result.resize(n);
    for (size_t p = 0; p < n; p++) {
        if (i == l.size()) {
            x = i - 1;
        } else {
            x = i;
        }
        if (j == r.size()) {
            y = j - 1;
        } else {
            y = j;
        }

        if (i < l.size() && ((this->*compareMin)(l[x], r[y]) || (j >= r.size()))) {
            result[p] = l[i];
            i++;
        } else if ((this->*compareMax)(l[x], r[y]) || i >= l.size()) {
            result[p] = r[j];
            j++;
        }
    }

    return (result);
}
//metodo para comparar fechas y hora

bool Master::timeCondMin(ADT &a, ADT &b) {
    Fecha tempFechaA = a.getFecha();
    Fecha tempFechaB = b.getFecha();
    int tiempoFechaTotalA = tempFechaA.getYear() * 365 + tempFechaA.getMes() * 30 + tempFechaA.getDia();
    int tiempoFechaTotalB = tempFechaB.getYear() * 365 + tempFechaB.getMes() * 30 + tempFechaB.getDia();
    if (tiempoFechaTotalA < tiempoFechaTotalB) {
        return (true);
    } else {
        Hora tempHoraA = a.getHora();
        Hora tempHoraB = b.getHora();
        int tiempoHoraTotalA = tempHoraA.getHora() * 3600 + tempHoraA.getMin() * 60 + tempHoraA.getSec();
        int tiempoHoraTotalB = tempHoraB.getHora() * 3600 + tempHoraB.getMin() * 60 + tempHoraB.getSec();
        if (tiempoHoraTotalA <= tiempoHoraTotalB) {
            return (true);
        }
        return (false);
    }
}
//metodo para comparar fechas y hora

bool Master::timeCondMax(ADT &a, ADT &b) {
    Fecha tempFechaA = a.getFecha();
    Fecha tempFechaB = b.getFecha();
    int tiempoFechaTotalA = tempFechaA.getYear() * 365 + tempFechaA.getMes() * 30 + tempFechaA.getDia();
    int tiempoFechaTotalB = tempFechaB.getYear() * 365 + tempFechaB.getMes() * 30 + tempFechaB.getDia();
    if (tiempoFechaTotalA > tiempoFechaTotalB) {
        return (true);
    } else {
        Hora tempHoraA = a.getHora();
        Hora tempHoraB = b.getHora();
        int tiempoHoraTotalA = tempHoraA.getHora() * 3600 + tempHoraA.getMin() * 60 + tempHoraA.getSec();
        int tiempoHoraTotalB = tempHoraB.getHora() * 3600 + tempHoraB.getMin() * 60 + tempHoraB.getSec();
        if (tiempoHoraTotalA > tiempoHoraTotalB) {
            return (true);
        }
        return (false);
    }
}
//metodo para comparar fechas

bool Master::dayCond(ADT &a, ADT &b) {
    Fecha tempFechaA = a.getFecha();
    Fecha tempFechaB = b.getFecha();
    if (tempFechaA.getYear() < tempFechaB.getYear()) {
        return (true);
    } else if ((tempFechaA.getYear() == tempFechaB.getYear()) && (tempFechaA.getMes() < tempFechaB.getMes())) {
        return (true);
    } else if ((tempFechaA.getYear() == tempFechaB.getYear()) && (tempFechaA.getMes() == tempFechaB.getMes()) && (tempFechaA.getDia() < tempFechaB.getDia())) {
        return (true);
    } else {
        return (false);
    }
}
//metodo para comparar horas

bool Master::horaCond(ADT &a, ADT &b) {
    Hora tempHoraA = a.getHora();
    Hora tempHoraB = b.getHora();
    if (tempHoraA.getHora() < tempHoraB.getHora()) {
        return (true);
    } else if ((tempHoraA.getHora() == tempHoraB.getHora()) && (tempHoraA.getMin() < tempHoraB.getMin())) {
        return (true);
    } else if ((tempHoraA.getHora() == tempHoraB.getHora()) && (tempHoraA.getMin() == tempHoraB.getMin()) && (tempHoraA.getSec() < tempHoraB.getSec())) {
        return (true);
    } else {
        return (false);
    }
}
// funcion para imprimir el registro el input es cuatas filas quieres imprimir. 0 es todas

void Master::Display(int resp) {
    size_t size;
    if (resp == 0) {
        size = lista.size();
    } else {
        size = resp;
    }
    for (size_t i = 0; i < size; i++) {
        cout << lista[i].getFechaDisplay() << ", " << lista[i].getHoraDisplay() << ", " << lista[i].getIPODisplay() << ", " << lista[i].getPuertoODisplay() << ", " << lista[i].getHostODisplay() << ", " << lista[i].getIPDDisplay() << ", " << lista[i].getPuertoDDisplay() << ", " << lista[i].getHostDDisplay() << endl;
    }
}
//funcion para imprimir un solo registro

void Master::printVector(ADT list) {
    cout << list.getFechaDisplay() << ", " << list.getHoraDisplay() << ", " << list.getIPODisplay() << ", " << list.getPuertoODisplay() << ", " << list.getHostODisplay() << ", " << list.getIPDDisplay() << ", " << list.getPuertoDDisplay() << ", " << list.getHostDDisplay() << endl;
}
//funcion para iniciar las busquedas

int Master::busqueda(bool (Master::*compare)(ADT &a, string &num), string var, bool PrintBool) {
    int contador = 0;
    return (busquedaArbol(0, lista.size() - 1, (compare), var, contador, PrintBool));
}
//funcion para hacer una busqueda

int Master::busquedaArbol(int primer, int ultimo, bool (Master::*compare)(ADT &a, string &num), string var, int &contador, bool PrintBool) {
    if (ultimo < primer) {
        return contador;
    }

    int medio = (primer + ultimo) / 2;
    if ((this->*compare)(lista[medio], var)) {
        if (PrintBool) {
            printVector(lista[medio]);
        }
        contador++;
    }
    int izquierda = busquedaArbol(primer, medio - 1, (compare), var, contador, PrintBool);
    int derecha = busquedaArbol(medio + 1, ultimo, (compare), var, contador, PrintBool);
    return (contador);
}
//funcion para buscar una fecha espesifica

bool Master::dayBusquedaCond(ADT &a, string &num) {
    Fecha tempFecha = a.getFecha();
    if (tempFecha.getDia() == stoi(num)) {
        return (true);
    }
    return (false);
}
//funcion para buscar el puerto mas chico

bool Master::puertoMinBusquedaCond(ADT &a, string &num) {
    Puerto tempPuerto = a.getPuertoD();
    if (tempPuerto.getPuerto() < stoi(num)) {
        return (true);
    }
    return (false);
}
//funcion para buscar un usuario

bool Master::OrdenadorBusquedaCond(ADT &a, string &name) {
    HostName tempHost = a.getHostO();
    if (tempHost.getName() == name) {
        return (true);
    }
    return (false);
}
//funcion para buscar un servicio en espesifico

bool Master::ServicioBusquedaCond(ADT &a, string &name) {
    HostName tempHost = a.getHostD();
    if (tempHost.getName() == name) {
        return (true);
    }
    return (false);
}
//busqueda de un usuario por nombre completo

bool Master::busquedaUsuarioCompletoCond(ADT &a, string &name) {
    HostName tempCompleto = a.getHostO();
    if (tempCompleto.display() == name) {
        return (true);
    }
    return (false);
}
//metodo para encontrar todos los servicios

bool Master::getAllServicesCond(ADT &a, string &name) {
    HostName servicioTemp = a.getHostD();
    if (find(allServices.begin(), allServices.end(), servicioTemp.getName()) != allServices.end()) {
        return (false);
    } else {
        allServices.push_back(servicioTemp.getName());
        return (true);
    }
}
//metodo para encontrar todos los puertos de destino sin repeticion

bool Master::getActivePortsDestinyCond(ADT &a, string &name) {
    Puerto portDTemp = a.getPuertoD();
    if (find(activePorts.begin(), activePorts.end(), portDTemp.display()) != activePorts.end()) {
        return (false);
    } else {
        activePorts.push_back(portDTemp.display());
        return (true);
    }
}
//metodo para encontrar todos los puertos de origen sin repeticion

bool Master::getActivePortsOriginCond(ADT &a, string &name) {
    Puerto portOTemp = a.getPuertoO();
    if (find(activePorts.begin(), activePorts.end(), portOTemp.display()) != activePorts.end()) {
        return (false);
    } else {
        activePorts.push_back(portOTemp.display());
        return (true);
    }
}
// metodo para iniciar la busqueda de un dia

int Master::busquedaDia(string num, bool PrintBool) {
    return (busqueda(&Master::dayBusquedaCond, num, PrintBool));
}
// metodo para iniciar la busqueda de un puerto minimo a un punto

int Master::busquedaMinpuerto(string num, bool PrintBool) {
    return (busqueda(&Master::puertoMinBusquedaCond, num, PrintBool));
}
// metodo para iniciar la busqueda de un servicio

int Master::busquedaServicio(string nombre, bool PrintBool) {
    return (busqueda(&Master::ServicioBusquedaCond, nombre, PrintBool));
}
// metodo para iniciar la busqueda de un usuario

int Master::busquedaOrdenador(string nombre, bool PrintBool) {
    return (busqueda(&Master::OrdenadorBusquedaCond, nombre, PrintBool));
}
// metodo para iniciar la busqueda de un usuario por nombre completo

int Master::busquedaUsuarioCompleto(string nombre, bool PrintBool) {
    return (busqueda(&Master::busquedaUsuarioCompletoCond, nombre, PrintBool));
}
// metodo para iniciar la busqueda de un dia relativo

int Master::diaRelativo(int _dia, bool sort) {
    if (sort) {
        sortByTime();
    }
    Fecha fecha = lista[0].getFecha();
    return (fecha.getDia() + _dia);
}
// metodo para iniciar la busqueda de todos los servicios

vector<string> Master::GetAllServices() {
    busqueda(&Master::getAllServicesCond, "-", false);
    return (allServices);
}
// metodo para iniciar la busqueda de tosos los puertos activos de destino

vector<string> Master::getActivePortsDestiny() {
    activePorts.clear();
    busqueda(&Master::getActivePortsDestinyCond, "-", false);
    return (activePorts);
}
// metodo para iniciar la busqueda de todos los puertos activos de origen

vector<string> Master::getActivePortsOrigin() {
    activePorts.clear();
    busqueda(&Master::getActivePortsOriginCond, "-", false);
    return (activePorts);
}

// metodo para consegir la ip local
string Master::conseguirIpLocal() {
    int indice = 0;
    IP tempUser = lista[indice].getIPO();
    while (tempUser.getLocalIp() == "0") {
        indice++;
        tempUser = lista[indice].getIPO();
    }
    return (tempUser.getLocalIp() + ".0");
}

// metodo para iniciar un anailisis completo en este se agregan todas las computadoras con las que se realizo una conexion en
//la red
void Master::computerAnalisis() {
    cout << endl;
    cout << "--Generating Computers--" << endl;
    cout << endl;
    loadComputers(&Master::ComputerIntegration, "all");
    /*for (size_t i = 0; i < listComputers.size(); i++)
    {
        cout << listComputers[i].getComputerIP() << endl;
    }*/
}

// este es un metodo para generar las computadoras apartir del resitro trabaja en conjunto con busqueda
void Master::loadComputers(bool (Master::*compare)(ADT &a, string &num), string var) {
    for (size_t i = 0; i < lista.size(); i++) {
        (this->*compare)(lista[i], var);
    }
}

// es el metodo que te permite crear una nueva computadora o hacer una conexion dependiendo de si ya existe 1
bool Master::ComputerIntegration(ADT &a, string &_ip) {
    map<string, ConexionesComputadora>::iterator searchIPO = computerDictionary.find(a.getIPO().display());
    map<string, ConexionesComputadora>::iterator searchIPD = computerDictionary.find(a.getIPD().display());
    if ((searchIPO != computerDictionary.end()) && (a.getIPO().display() == searchIPO->first)) {
        if (a.getHostODisplay() != "-" && a.getHostODisplay() != "") {
            computerDictionary[a.getIPO().display()].setName(a.getHostODisplay());
        }
        computerDictionary[a.getIPO().display()].conexion(false, a.getIPD(), a.getIndice());
    }
    if ((searchIPD != computerDictionary.end()) && (a.getIPD().display() == searchIPD->first)) {
        if (a.getHostDDisplay() != "-" && a.getHostDDisplay() != "") {
            computerDictionary[a.getIPD().display()].setName(a.getHostDDisplay());
        }
        computerDictionary[a.getIPD().display()].conexion(true, a.getIPO(), a.getIndice());
    }
    if (searchIPO == computerDictionary.end()) {
        computerDictionary[a.getIPO().display()] = ConexionesComputadora(a.getIPO());
        computerDictionary[a.getIPO().display()].setName(a.getHostODisplay());
        computerDictionary[a.getIPO().display()].conexion(false, a.getIPD(), a.getIndice());
        HostIP[a.getHostO().getName()] = a.getIPODisplay();
    }
    if (searchIPD == computerDictionary.end()) {
        computerDictionary[a.getIPD().display()] = ConexionesComputadora(a.getIPD());
        computerDictionary[a.getIPD().display()].setName(a.getHostDDisplay());
        computerDictionary[a.getIPD().display()].conexion(true, a.getIPO(), a.getIndice());
        HostIP[a.getHostD().getName()] = a.getIPDDisplay();
    }
    return (false);
}

// esta funcion llama singleConectionSearch y hace un fullConectionStatus
void Master::singleConectionAssessment(int _IPI) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_IPI);
    loadComputers(&Master::ComputerIntegration, _IP);
    fullConectionStatus(_IPI);
}

// esta es la condicional para hacer una busqueda de IPs
bool Master::IPSearch(ConexionesComputadora a, string _ip) {
    return a.getComputerIP() == _ip ? true : false;
}

//funcion para iniciar las busquedas en la lista de computadoras
ConexionesComputadora *Master::busquedaConexiones(bool (Master::*compare)(ConexionesComputadora a, string _ip), string var, bool firstFind) {
    return (busquedaArbolConexiones(0, computerDictionary.size() - 1, (compare), var, firstFind));
}

//funcion para hacer una busqueda en la lista de computadoras
ConexionesComputadora *Master::busquedaArbolConexiones(int primer, int ultimo, bool (Master::*compare)(ConexionesComputadora a, string _ip), string var, bool firstFind) {
    if (ultimo < primer) {
        //cout << "NULL   " << endl;
        return NULL;
    }

    int medio = (primer + ultimo) / 2;
    if ((this->*compare)(listComputers[medio], var)) {
        if (firstFind) {
            //cout << "work   " << listComputers[medio].getComputerIP() << endl;
            return (&listComputers[medio]);
        }
    }
    ConexionesComputadora *izquierda = busquedaArbolConexiones(primer, medio - 1, (compare), var, firstFind);
    ConexionesComputadora *derecha = busquedaArbolConexiones(medio + 1, ultimo, (compare), var, firstFind);
    if (izquierda != NULL) {
        //cout << "izquierda " << izquierda->getComputerIP() << " ptr " << izquierda << endl;
        return (izquierda);
    } else if (derecha != NULL) {
        //cout << "derecha " << derecha->getComputerIP() << " ptr " << derecha << endl;
        return (derecha);
    } else {
        return (NULL);
    }
}

// la condicional para encontrar una computadora espesifica
bool Master::computerConectionCond(ConexionesComputadora a, string _ip) {
    return a.getComputerIP() == _ip ? true : false;
}

// realiza una busqueda mediante una IP en la lista de computadoras
string Master::SearchByIP(int _IPI) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_IPI);
    map<string, ConexionesComputadora>::iterator tempConection = computerDictionary.find(_IP);
    return tempConection->second.getComputerIP();
}

// regresa las conexiones entrantes mediante la busqueda de una IP espesifica
string Master::getIncomingConection(int _IPI) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_IPI);
    map<string, ConexionesComputadora>::iterator tempConection = computerDictionary.find(_IP);
    stack<IP> allIncomingConection = tempConection->second.getConexionesEntrantes();
    if (tempConection != computerDictionary.end()) {
        return allIncomingConection.top().display();
    } else {
        return "NULL";
    }
}

// regresa el tamaño de las conexones entrantes
int Master::getAllIncomingConections(int _IPI) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_IPI);
    map<string, ConexionesComputadora>::iterator tempConection = computerDictionary.find(_IP);
    if (tempConection != computerDictionary.end()) {
        stack<IP> allIncomingConection = tempConection->second.getConexionesEntrantes();
        return allIncomingConection.size();
    } else {
        return 0;
    }
}

// regresa el tamaño de las conexones salientes
int Master::getAllOutgoingConections(int _IPI) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_IPI);
    map<string, ConexionesComputadora>::iterator tempConection = computerDictionary.find(_IP);
    if (tempConection != computerDictionary.end()) {
        queue<IP> allIncomingConection = tempConection->second.getConexionesSalientes();
        return allIncomingConection.size();
    } else {
        return 0;
    }
}

// regresa el nombre de las la computadora mediante una ip espesifica
string Master::getComputerName(int _IPI) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_IPI);
    map<string, ConexionesComputadora>::iterator tempConection = computerDictionary.find(_IP);
    if (tempConection != computerDictionary.end()) {
        return tempConection->second.getName();
    } else {
        return "NULL";
    }
}

// condicion para la busqueda de una compu por indice se ocupa con la busqueda de registros
bool Master::busquedaPorIndiceCond(ADT &a, string &_ip) {
    if (to_string(a.getIndice()) == _ip) {
        computer = a;
        return true;
    } else {
        return false;
    }
}

//gets the last N of outgoing conections
vector<string> Master::getNOutOutgoingConections(int _ipI, int N) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_ipI);
    map<string, ConexionesComputadora>::iterator tempConection = computerDictionary.find(_IP);
    vector<string> rVector;
    if (tempConection != computerDictionary.end() && !tempConection->second.getConexionesSalientes().empty()) {
        queue<int> salientesI = tempConection->second.getConexionesSalientesIndice();
        if (N < salientesI.size()) {
            for (size_t i = 0; i < N; i++) {
                rVector.push_back(to_string(salientesI.front()));
                busqueda(&Master::busquedaPorIndiceCond, to_string(salientesI.front()), true);
                salientesI.pop();
            }
        } else {
            rVector.push_back("N is bigger than size");
        }
    } else {
        rVector.push_back("NULL/EMPTY");
    }
    return rVector;
}
// imprime un resumen de una computadora espesifica mediante la busqueda de una ip
void Master::fullConectionStatus(int _IPI) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(_IPI);
    cout << "--IP Analisis--" << endl;
    map<string, ConexionesComputadora>::iterator tempConection = computerDictionary.find(_IP);

    if (tempConection != computerDictionary.end()) {
        stack<IP> entrantes = tempConection->second.getConexionesEntrantes();
        stack<int> entrantesIndice = tempConection->second.getConexionesEntrantesIndice();
        queue<IP> salientes = tempConection->second.getConexionesSalientes();
        queue<int> salientesIndice = tempConection->second.getConexionesSalientesIndice();
        string name = tempConection->second.getName();
        string CIP = tempConection->second.getComputerIP();
        string entranteValor = "0";

        if (!entrantes.empty()) {
            entranteValor = entrantes.top().display();
        }
        string salienteValor = "0";
        if (salientes.size() != 0) {
            salienteValor = salientes.front().display();
        }
        string entranteValorIndice = "NULL";
        if (!entrantesIndice.empty()) {
            entranteValorIndice = to_string(entrantesIndice.top());
        }
        string salienteValorIndice = "NULL";
        if (salientesIndice.size() != 0) {
            cout << "salientesIndice.size()" << endl;
            salienteValorIndice = to_string(salientesIndice.front());
        }

        cout << "computer name: " << name << endl;
        cout << endl;
        cout << "computer IP: " << CIP << endl;
        cout << endl;
        cout << "Number of Incoming conections: " << entrantes.size() << endl;
        cout << endl;
        cout << "Number of Outgoing conections: " << salientes.size() << endl;
        cout << endl;
        cout << "Incoming conection: " << entranteValor << endl;
        busqueda(&Master::busquedaPorIndiceCond, entranteValorIndice, true);
        cout << endl;
        cout << "Outgoing connection: " << salienteValor << endl;
        busqueda(&Master::busquedaPorIndiceCond, salienteValorIndice, true);
        cout << endl;
        cout << "Last conection: ";
        string str = conseguirIpLocal().substr(0, conseguirIpLocal().length() - 2);
        if (entrantes.top().getLocalIp() == str) {
            cout << "IP: Interna-> ";
        } else {
            cout << "IP: Externa-> ";
        }
        busqueda(&Master::busquedaPorIndiceCond, entranteValorIndice, true);
    } else {
        cout << "NULL" << endl;
    }
}
// Este metodo busca a traves de la estructura de datos map<host,ip> permitiendo encontrar la ip de una computadora por su nombre
string Master::getComputerIP(string name) {
    map<string, string>::iterator tempHost = HostIP.find(name);
    if (tempHost != HostIP.end()) {
        return tempHost->second;
    } else {
        return "NULL";
    }
}
//Este metodo busca todas las computadoras que almenos tiene una conexion
int Master::getComputerWConections() {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    int ActiveComputers = 0;
    for (size_t i = 1; i < 255; i++) {
        string _IP = sbst + to_string(i);
        if (computerDictionary[_IP].getConexionesEntrantesSize() > 0) {
            ActiveComputers++;
        }
    }
    return (ActiveComputers);
}
// Este metodo obtiene las conexiones entrantes unicas de todas las computadoras regresandolas en un conjunto
set<string> Master::getComputerUniqueServices() {
    set<string> tcp;
    for (auto &x : computerDictionary) {
        stack indexE = x.second.getConexionesEntrantesIndice();
        while (!indexE.empty() && lista[indexE.top()].getHostDDisplay() != "-") {
            indexE.pop();
        }

        queue indexS = x.second.getConexionesSalientesIndice();
        while (!indexS.empty() && lista[indexS.front()].getHostODisplay() != "-") {
            indexS.pop();
        }

        if (!indexS.empty() && lista[indexS.front()].getHostODisplay() != "68" || !indexE.empty() && lista[indexE.top()].getHostDDisplay() != "67")
            if (x.second.getComputerIPLocal() == "10.8.134" && x.second.getName() != "server.reto.com") {
                stack conexionesEntrantes = x.second.getConexionesEntrantes();
                for (size_t i = 0; i < conexionesEntrantes.size(); i++) {
                    tcp.insert(conexionesEntrantes.top().display());
                    conexionesEntrantes.pop();
                }
            }
    }
    return (tcp);
}
// Este metodo obtiene las conexiones entrantes unicas de cada computadora
set<string> Master::getComputerUniqueServicesIndividual() {
    set<string> tcp;
    for (auto &x : computerDictionary) {
        set<string> tcp;
        stack indexE = x.second.getConexionesEntrantesIndice();
        while (!indexE.empty() && lista[indexE.top()].getHostDDisplay() != "-") {
            indexE.pop();
        }

        queue indexS = x.second.getConexionesSalientesIndice();
        while (!indexS.empty() && lista[indexS.front()].getHostODisplay() != "-") {
            indexS.pop();
        }

        if (!indexS.empty() && lista[indexS.front()].getHostODisplay() != "68" || !indexE.empty() && lista[indexE.top()].getHostDDisplay() != "67")
            if (x.second.getComputerIPLocal() == "10.8.134" && x.second.getName() != "server.reto.com" && x.second.getName() != "-") {
                stack conexionesEntrantes = x.second.getConexionesEntrantes();
                for (size_t i = 0; i < conexionesEntrantes.size(); i++) {
                    tcp.insert(conexionesEntrantes.top().display());
                    conexionesEntrantes.pop();
                }
                cout << "for the computer " << x.second.getName() << " the unique conections are: " << endl;
                for (auto elem : tcp) {
                    cout << elem << ", ";
                }

                cout << endl;
            }
    }
    return (tcp);
}
//Este metodo va atraves de las conexiones entrantes y salientes de la computadora espesificada
bool Master::checkIfConnection(string IP1, string IP2) {
    map<string, ConexionesComputadora>::iterator searchIP = computerDictionary.find(IP1);
    stack IPsSearchE = searchIP->second.getConexionesEntrantes();
    if (searchIP != computerDictionary.end() || !IPsSearchE.empty()) {
        for (size_t i = 0; i < IPsSearchE.size(); i++) {
            //cout << "cons1 " << IPsSearchE.top().display() << " == " << IP2 << endl;
            if (IPsSearchE.top().display() == IP2) {
                return (true);
            }
            IPsSearchE.pop();
        }
    }
    queue IPsSearchS = searchIP->second.getConexionesSalientes();
    if (searchIP != computerDictionary.end() || !IPsSearchS.empty()) {
        for (size_t i = 0; i < IPsSearchS.size(); i++) {
            //cout << "cons2 " << IPsSearchS.front().display() << " == " << IP2 << endl;
            if (IPsSearchS.front().display() == IP2) {
                return (true);
            }
            IPsSearchS.pop();
        }
    }
    return (false);
}
// es el metodo que te permite crear una nueva computadora o hacer una conexion dependiendo de si ya existe 1 sobre un solo dia
bool Master::dayIntegration(ADT &a, string &dia) {
    map<string, ConexionesComputadora>::iterator searchIPO = dayComputerDictionary.find(a.getIPO().display());
    map<string, ConexionesComputadora>::iterator searchIPD = dayComputerDictionary.find(a.getIPD().display());
    if ((searchIPO != dayComputerDictionary.end()) && (a.getIPO().display() == searchIPO->first)) {
        if (a.getHostODisplay() != "-" && a.getHostODisplay() != "") {
            dayComputerDictionary[a.getIPO().display()].setName(a.getHostODisplay());
        }
        dayComputerDictionary[a.getIPO().display()].conexion(false, a.getIPD(), a.getIndice());
    }
    if ((searchIPD != dayComputerDictionary.end()) && (a.getIPD().display() == searchIPD->first)) {
        if (a.getHostDDisplay() != "-" && a.getHostDDisplay() != "") {
            dayComputerDictionary[a.getIPD().display()].setName(a.getHostDDisplay());
        }
        dayComputerDictionary[a.getIPD().display()].conexion(true, a.getIPO(), a.getIndice());
    }
    if (searchIPO == dayComputerDictionary.end() && to_string(a.getFecha().getDia()) == dia) {
        dayComputerDictionary[a.getIPO().display()] = ConexionesComputadora(a.getIPO());
        dayComputerDictionary[a.getIPO().display()].setName(a.getHostODisplay());
        dayComputerDictionary[a.getIPO().display()].conexion(false, a.getIPD(), a.getIndice());
    }
    if (searchIPD == dayComputerDictionary.end() && to_string(a.getFecha().getDia()) == dia) {
        dayComputerDictionary[a.getIPD().display()] = ConexionesComputadora(a.getIPD());
        dayComputerDictionary[a.getIPD().display()].setName(a.getHostDDisplay());
        dayComputerDictionary[a.getIPD().display()].conexion(true, a.getIPO(), a.getIndice());
    }
    return (false);
}
//este metodo crea una estructura de datos tipo diccionario en la que asigna a cada servicio el numero de conecciones.
map<string, int> Master::conexionesPorDia(Fecha _fecha) {
    map<string, int> tCDictionary;
    loadComputers(&Master::dayIntegration, to_string(_fecha.getDia()));
    for (auto &x : dayComputerDictionary) {
        string tempIPN = x.second.getName();
        string tempIPL = x.second.getComputerIPLocal();
        if (tempIPN != "-" && tempIPN != "" && tempIPL != "10.8.134") {
            tCDictionary[tempIPN] = x.second.getConexionesEntrantesSize();
        }
    }
    return (tCDictionary);
}
//Este metodo obtiene le numero indicado de de mayores sitios con con conecciones en una espesifica fecha
vector<string> Master::top(int n, string _fecha) {
    Fecha date(_fecha);
    map<string, int> TCD = conexionesPorDia(date);
    for (auto &x : TCD) {
        //cout << "pre ins" << endl;
        BST.insertNodeRecursive({{x.first, x.second}});
        //cout << "post ins" << endl;
    }
    //BST.printV1();
    vector<string> values;
    values.reserve(n);
    //cout << "pre topn" << endl;
    BST.getTopNvalues(n, values);
    //cout << "post topn" << endl;
    return (values);
}
// este metodod utiliza la funcion top para realizar el top de connecciones de todos los dias
vector<vector<string>> Master::ChronologyOfMostConections(int num) {
    vector<vector<string>> storage;
    sortByTime();
    string fechaTemp = lista[0].getFechaDisplay();
    string withoutDay = to_string(lista[0].getFecha().getDia());
    string fechaMovible = fechaTemp.substr(withoutDay.size(), fechaTemp.size());
    for (size_t i = lista[0].getFecha().getDia(); i <= lista[lista.size() - 1].getFecha().getDia(); i++) {
        string tempFecha = to_string(i) + fechaMovible;
        storage.push_back(top(num, tempFecha));
    }
    return (storage);
}
// este metodo obtienene los nombres de todos los servicios y los mete en un diccionario
bool Master::addServicesNames(ADT &a, string &name) {
    if (a.getIPD().getLocalIp() != "10.8.134" && a.getHostDDisplay() != "-") {
        domainNames.insert(a.getHostDDisplay());
    }
    return (true);
}
// este meteodo obtiene todos los nombres de los servicios almacenados en domainNames
void Master::getStrangeHost() {
    loadComputers(&Master::addServicesNames, "all");
    for (auto x : domainNames) {
        cout << x << " , ";
    }
    cout << endl;
}
// este meteodo genera un grafo de las conexiones entre ips por dia
Graph<string> Master::makeGraphOfDay(Fecha date) {
    loadComputers(&Master::dayIntegration, to_string(date.getDia()));
    Graph<string> tGraph(true);
    map<string, int> indexOfIP;
    int ind = 0;
    string LIP = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 2);
    for (auto &x : dayComputerDictionary) {
        if (indexOfIP.find(x.first) == indexOfIP.end() && x.second.getComputerIPLocal() == LIP) {
            tGraph.add_node(x.first);
            indexOfIP[x.first] = ind;
        }
        stack<IP> Icnx = x.second.getConexionesEntrantes();
        if (!Icnx.empty()) {
            for (size_t i = 0; i < Icnx.size(); i++) {
                if (indexOfIP.find(Icnx.top().display()) == indexOfIP.end() && Icnx.top().getLocalIp() == LIP) {
                    tGraph.add_node(Icnx.top().display());
                    indexOfIP[Icnx.top().display()] = ind++;
                }
                tGraph.add_edge(indexOfIP[Icnx.top().display()], indexOfIP[x.first]);
                Icnx.pop();
            }
        }
        queue<IP> Scnx = x.second.getConexionesSalientes();
        if (!Scnx.empty()) {
            for (size_t i = 0; i < Scnx.size(); i++) {
                if (indexOfIP.find(Scnx.front().display()) == indexOfIP.end() && Scnx.front().getLocalIp() == LIP) {
                    //cout << "eGameS" << Scnx.front().display() << endl;
                    tGraph.add_node(Scnx.front().display());
                    indexOfIP[Scnx.front().display()] = ind++;
                }
                tGraph.add_edge(indexOfIP[x.first], indexOfIP[Scnx.front().display()]);
                Scnx.pop();
            }
        }
    }
    return (tGraph);
}
// este meteodo genera un diccionario de grafos de las conexiones entre ips por dia
void Master::generateGraphConnections() {
    sortByTime();
    string fechaTemp = lista[0].getFechaDisplay();
    string withoutDay = to_string(lista[0].getFecha().getDia());
    string fechaMovible = fechaTemp.substr(withoutDay.size(), fechaTemp.size());
    for (size_t i = lista[0].getFecha().getDia(); i <= lista[lista.size() - 1].getFecha().getDia(); i++) {
        string tempFecha = to_string(i) + fechaMovible;
        Fecha date(tempFecha);
        IPNetwork[tempFecha] = makeGraphOfDay(date);
        cout << "Graph of " << date.display() << " Generated" << endl;
    }
    cout << "Genaration Finished" << endl;
}
// este meteodo busca las conexiones recibidas a una ip espesifica en un dia
vector<string> Master::getGraphIncomingConnectionsInternal(string _fecha, int IP) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(IP);
    Fecha date(_fecha);
}
// este meteodo busca las conexiones salientes de una ip espesifica en un dia
vector<string> Master::getGraphOutgoingConnectionsInternal(string _fecha, int IP) {
    string sbst = conseguirIpLocal().substr(0, conseguirIpLocal().size() - 1);
    string _IP = sbst + to_string(IP);
    Fecha date(_fecha);
}