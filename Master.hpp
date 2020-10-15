/* 
clase para procesar y ordenar los datos
javier alejandro martinez noe y Ricardo Uraga
27/9/20
*/
#include <iostream>
#include <vector>

#include "ADT.hpp"
#include "ConexionesComputadora.hpp"
using namespace std;
#pragma once

class Master {
   protected:
    vector<ADT> lista;
    vector<string> allServices;
    vector<string> activePorts;
    vector<ConexionesComputadora> listComputers;
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
    bool ComputerIntegration(ConexionesComputadora *indexConexion, ADT &a);
    vector<ADT> mergeSort(vector<ADT> &listaToMege, int primer, int ultimo, bool (Master::*compareMin)(ADT &a, ADT &b), bool (Master::*compareMax)(ADT &a, ADT &b));
    vector<ADT> merge(vector<ADT> &l, vector<ADT> &r, bool (Master::*compareMin)(ADT &a, ADT &b), bool (Master::*compareMax)(ADT &a, ADT &b));
    ConexionesComputadora *busquedaArbolConexiones(int primer, int ultimo, bool (Master::*compare)(ConexionesComputadora a, string _ip), string var, bool PrintBool);
    ConexionesComputadora *busquedaConexiones(bool (Master::*compare)(ConexionesComputadora a, string _ip), string var, bool PrintBool);
    void loadComputers(bool (Master::*compare)(ADT &a, string &num), string var);

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
    string SearchByIP(string _IP);
    string getLasConection(string _IP);
    string getIncomingConection(string _IP);
    string getComputerName(string _IP);
    void fullConectionStatus(string _IP);
    int getAllIncomingConections(string _IP);
    int getAllOutgoingConections(string _IP);
    void singleConectionAssessment(string _IP);
    vector<string> getNOutOutgoingConections(string _ip, int N);
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
    return (fecha.getDia() + _dia - 1);
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
    loadComputers(&Master::AddComputer, "all");
    /*for (size_t i = 0; i < listComputers.size(); i++)
    {
        cout << listComputers[i].getComputerIP() << endl;
    }*/
}

// este es un metodo para generar las computadoras apartir del resitro trabaja en conjunto con busqueda
void Master::loadComputers(bool (Master::*compare)(ADT &a, string &num), string var) {
    for (size_t i = 0; i < lista.size(); i++) {
        if (lista[i].getIPODisplay() == var || lista[i].getIPDDisplay() == var) {
            //cout << lista[i].getIndice() << endl;
        }
        (this->*compare)(lista[i], var);
    }
}

// es el metodo que te permite crear una nueva computadora o hacer una conexion dependiendo de si ya existe 1
bool Master::ComputerIntegration(ConexionesComputadora *indexConexion, ADT &a) {
    /*cout << a.getIndice() << endl;
    if (a.getIPO().display() == "10.8.134.178" || a.getIPD().display() == "10.8.134.178")
    {
        printVector(a);
        bool cond = indexConexion == NULL;
        cout << "------------" << a.getIPO().display() << " = " << a.getIPD().display() << "------------" << cond << endl;
    }*/

    if ((indexConexion != NULL) && (a.getIPO().display() == indexConexion->getComputerIP())) {
        if (indexConexion->getName() != "-" || indexConexion->getName() != "") {
            indexConexion->setName(a.getHostO().getName());
        }
        indexConexion->conexion(a.getIPO(), a.getIndice());
        return (true);
    } else if ((indexConexion != NULL) && (a.getIPD().display() == indexConexion->getComputerIP())) {
        if (indexConexion->getName() != "-" || indexConexion->getName() != "") {
            indexConexion->setName(a.getHostD().getName());
        }
        indexConexion->conexion(a.getIPO(), a.getIndice());
        return (true);
    } else {
        listComputers.push_back(ConexionesComputadora(a.getIPO()));
        listComputers.back().setName(a.getHostODisplay());
        listComputers.back().conexion(a.getIPO(), a.getIndice());

        listComputers.push_back(ConexionesComputadora(a.getIPD()));
        listComputers.back().setName(a.getHostDDisplay());
        listComputers.back().conexion(a.getIPD(), a.getIndice());
        //cout << a.getHostODisplay() << ": " << listComputers.back().getComputerIP() << endl;
    }
    return (false);
}

// este metodo se ocupa para agregar todas computadoras haciendo una busqueda para ver si hay una instancia previa
bool Master::AddComputer(ADT &a, string &_ip) {
    ConexionesComputadora *indexConexion = busquedaConexiones(&Master::IPSearch, a.getIPO().display(), true);
    ComputerIntegration(indexConexion, a);
    indexConexion = busquedaConexiones(&Master::IPSearch, a.getIPD().display(), true);
    ComputerIntegration(indexConexion, a);
    return true;
}

// este metodo te permite generar una espesifica computadora y sus conexiones
bool Master::singleConectionSearch(ADT &a, string &_ip) {
    /*if (a.getIPO().display() == "10.8.134.178" || a.getIPD().display() == "10.8.134.178")
    {
        printVector(a);
        cout << "------------" << a.getIPO().display() << " = " << a.getIPD().display() << "------------" << _ip << endl;
    }*/
    if (a.getIPO().display() == _ip) {
        ConexionesComputadora *indexConexion = busquedaConexiones(&Master::IPSearch, _ip, true);
        ComputerIntegration(indexConexion, a);
        return true;
    } else if (a.getIPD().display() == _ip) {
        ConexionesComputadora *indexConexion = busquedaConexiones(&Master::IPSearch, _ip, true);
        ComputerIntegration(indexConexion, a);
        return true;
    } else {
        return false;
    }
}

// esta funcion llama singleConectionSearch y hace un fullConectionStatus
void Master::singleConectionAssessment(string _IP) {
    loadComputers(&Master::singleConectionSearch, _IP);
    fullConectionStatus(_IP);
}

// esta es la condicional para hacer una busqueda de IPs
bool Master::IPSearch(ConexionesComputadora a, string _ip) {
    return a.getComputerIP() == _ip ? true : false;
}

//funcion para iniciar las busquedas en la lista de computadoras
ConexionesComputadora *Master::busquedaConexiones(bool (Master::*compare)(ConexionesComputadora a, string _ip), string var, bool firstFind) {
    return (busquedaArbolConexiones(0, listComputers.size() - 1, (compare), var, firstFind));
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
string Master::SearchByIP(string _IP) {
    ConexionesComputadora *tempConection = busquedaConexiones(&Master::computerConectionCond, _IP, true);
    return tempConection->getComputerIP();
}

// regresa las conexiones entrantes mediante la busqueda de una IP espesifica
string Master::getIncomingConection(string _IP) {
    ConexionesComputadora *tempConection = busquedaConexiones(&Master::computerConectionCond, _IP, true);
    stack<IP> allIncomingConection = tempConection->getConexionesEntrantes();
    if (tempConection != NULL) {
        return allIncomingConection.top().display();
    } else {
        return "NULL";
    }
}

// regresa el tamaño de las conexones entrantes
int Master::getAllIncomingConections(string _IP) {
    ConexionesComputadora *tempConection = busquedaConexiones(&Master::computerConectionCond, _IP, true);
    stack<IP> allIncomingConection = tempConection->getConexionesEntrantes();
    return allIncomingConection.size();
}

// regresa el tamaño de las conexones salientes
int Master::getAllOutgoingConections(string _IP) {
    ConexionesComputadora *tempConection = busquedaConexiones(&Master::computerConectionCond, _IP, true);
    vector<IP> allIncomingConection = tempConection->getConexionesSalientesV();
    return allIncomingConection.size();
}

// regresa el nombre de las la computadora mediante una ip espesifica
string Master::getComputerName(string _IP) {
    ConexionesComputadora *tempConection = busquedaConexiones(&Master::computerConectionCond, _IP, true);
    return tempConection->getName();
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
vector<string> Master::getNOutOutgoingConections(string _ip, int N) {
    ConexionesComputadora *tempConection = busquedaConexiones(&Master::computerConectionCond, _ip, true);
    vector<string> rVector;
    if (tempConection != NULL && !tempConection->getConexionesSalientesV().empty()) {
        vector<IP> salientes = tempConection->getConexionesSalientesV();
        if (N < salientes.size()) {
            for (size_t i = 0; i < N; i++) {
                rVector.push_back(salientes.front().display());
            }
        } else {
            rVector.push_back("N is bigger than size");
        }
    } else {
        rVector.push_back("NULL");
    }
    return rVector;
}
// imprime un resumen de una computadora espesifica mediante la busqueda de una ip
void Master::fullConectionStatus(string _IP) {
    cout << "--IP Analisis--" << endl;
    ConexionesComputadora *tempConection = busquedaConexiones(&Master::computerConectionCond, _IP, true);

    if (tempConection != NULL) {
        stack<IP> entrantes = tempConection->getConexionesEntrantes();
        stack<int> entrantesIndice = tempConection->getConexionesEntrantesIndice();
        vector<IP> salientes = tempConection->getConexionesSalientesV();
        vector<int> salientesIndice = tempConection->getConexionesSalientesVIndice();
        string name = tempConection->getName();
        string CIP = tempConection->getComputerIP();
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
