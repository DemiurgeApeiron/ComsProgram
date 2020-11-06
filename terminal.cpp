/* 
programa para probar la funcionalidad de ComsProgram
javier alejandro martinez noe y Ricardo Uraga
27/9/20
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "CsvReader.hpp"
#include "Master.hpp"
using namespace std;

//funcion para imprimir el registro

void print(Master &object) {
    int resp;
    cout << endl;
    cout << "Espesifica cuantas filas quieres imprimir, 0 = All: " << endl;
    cin >> resp;
    object.Display(resp);
    cout << endl;
}
//funcion para añadir regitros

Master addRegistro(vector<vector<string>> &_registros, Master &_program) {
    for (size_t i = 0; i < _registros.size(); i++) {
        _program.addRegister(_registros[i]);
    }
    return (_program);
}
//funcion para controlar el programa

int terminal() {
    Master program;
    CSVReader reader("nuevo5.csv");
    vector<vector<string>> regitros = reader.getData();
    program = addRegistro(regitros, program);

    cout << "display head(5)" << endl;
    program.Display(5);
    cout << endl;
    cout << "En total hay: " << program.numeroDeRegistros() << " Registros" << endl;
    cout << endl;
    int sorter;
    cout << "Do you want to sort? naturally the list is sorted but if you want to sort it will take time. 0: no, 1: yes" << endl;
    cin >> sorter;
    bool sort;
    if (sorter == 1) {
        sort = true;
    } else {
        sort = false;
    }
    if (sort) {
        cout << "sorting by time" << endl;
        program.sortByTime();
        cout << "display head(5)" << endl;
        program.Display(5);
        cout << endl;
    }
    cout << endl;
    string diaRelativo = to_string(program.diaRelativo(2, sort));
    cout << "El segundo dia es: " << diaRelativo << endl;
    int numRegistros = program.busquedaDia(diaRelativo, false);
    cout << "El segundo dia hay: " << numRegistros << " registros" << endl;
    cout << endl;
    int num = program.busquedaMinpuerto("1000", false);
    if (num != 0) {
        cout << "Si hay un puerto de destino menor a 1000" << endl;
        cout << "Hay " << num << " en el regitro con un puerto de destino menor a 1000" << endl;
    }
    int print;
    cout << "Do you want to print the registers under 1000 in the port. 0: no, 1: yes" << endl;
    cin >> print;
    cout << endl;
    if (print == 1) {
        program.busquedaMinpuerto("1000", true);
    }
    vector<string> names = {"jeffrey", "betty", "katherine", "scott", "benjamin"};
    for (size_t i = 0; i < names.size(); i++) {
        int busquedaNames = program.busquedaOrdenador(names[i], false);
        if (busquedaNames != 0) {
            cout << "En el registro " << names[i] << " si tiene una compu" << endl;
        }
    }
    cout << endl;
    vector<string> servicios = {"gmail", "hotmail", "outlook", "prontonmail"};
    for (size_t i = 0; i < servicios.size(); i++) {
        int busquedaOrdenadores = program.busquedaServicio(servicios[i], false);
        if (busquedaOrdenadores != 0) {
            cout << "En el registro se ocupa el servicio: " << servicios[i] << endl;
        }
    }
    cout << endl;
    int reto = program.busquedaUsuarioCompleto("server.reto.com", false);
    if (reto != 0) {
        cout << "si hay un usuario llamado server.reto.com en el registo" << endl;
    } else {
        cout << "No hay un usuario llamado server.reto.com en el registo" << endl;
    }
    cout << endl;
    cout << "la Ip local de la red es: " << program.conseguirIpLocal() << endl;
    cout << endl;
    vector<string> serviciosTodos = program.GetAllServices();
    cout << "Se estan Ocupando los servicios:" << endl;
    for (size_t i = 0; i < serviciosTodos.size(); i++) {
        cout << serviciosTodos[i] << ", ";
    }
    cout << endl;
    cout << endl;
    vector<string> puertosActivos = program.getActivePortsDestiny();
    cout << "Puertos de destino activos:" << endl;
    for (size_t i = 0; i < puertosActivos.size(); i++) {
        cout << puertosActivos[i] << ", ";
    }
    cout << endl;
    cout << endl;
    int networkAnalisis;
    cout << "Do you want to do a full network analisis or single computer analisis. 0: full 1: single," << endl;
    cin >> networkAnalisis;
    cout << endl;
    if (networkAnalisis == 0) {
        program.computerAnalisis();
        cout << endl;
        cout << endl;
        program.fullConectionStatus(59);
        cout << endl;
        cout << endl;

    } else if (networkAnalisis == 1) {
        program.singleConectionAssessment(59);
        cout << endl;
        cout << endl;
    }
    cout << "the last 3 outgoing conections were: " << endl;
    vector<string> lastThree = program.getNOutOutgoingConections(59, 3);
    for (size_t i = 0; i < lastThree.size(); i++) {
        cout << "RegisterIndex: " << lastThree[i] << ", ";
    }
    cout << endl;
    cout << endl;
    cout << "All unique connected services" << endl;
    program.getStrangeHost();
    cout << endl;
    cout << endl;
    cout << "The computer IP is: " << program.getComputerIP("k9oggvetufjky45ogief") << endl;
    cout << endl;
    cout << endl;

    cout << "Number of computers with at least one conection: " << program.getComputerWConections() << endl;
    cout << endl;
    set<string> allUCIP = program.getComputerUniqueServices();
    cout << "All unique incoming conections: ";
    for (auto elem : allUCIP) {
        cout << elem << " , ";
    }
    cout << endl;
    cout << endl;
    int uniqueIncomingConnection;
    cout << "Do you want to print the unique incoming conections of every conputer: 0: no 1: yes" << endl;
    cin >> uniqueIncomingConnection;
    cout << endl;
    if (uniqueIncomingConnection == 1) {
        program.getComputerUniqueServicesIndividual();
        cout << endl;
        cout << endl;
    }

    bool fts = program.checkIfConnection("10.8.134.59", "210.245.116.19");
    bool sec = program.checkIfConnection("10.8.134.59", "63.5.179.78");
    if (fts) {
        cout << "A connection was made between 10.8.134.59 and 210.245.116.19" << endl;
    }
    if (sec) {
        cout << "A connection was made between 10.8.134.59 and 63.5.179.78" << endl;
    }

    cout << endl;
    cout << endl;
    cout << "All conections to a site in 21-8-2020: ";
    Fecha dia("21-8-2020");
    map<string, int> sitesConexionsDay = program.conexionesPorDia(dia);
    for (auto &x : sitesConexionsDay) {
        cout << "sitio: " << x.first << " conexiones: " << x.second << ",  ";
    }
    cout << endl;
    cout << endl;
    vector<string> values = program.top(5, "21-8-2020");
    for (size_t i = 0; i < values.size(); i++) {
        cout << i + 1 << ": " << values[i] << ", ";
    }
    cout << endl;
    cout << endl;
    vector<vector<string>> cronologia = program.ChronologyOfMostConections(5);

    vector<set<string>> setValues;
    for (size_t i = 0; i < cronologia.size(); i++) {
        set<string> vals;
        for (size_t j = 0; j < cronologia[i].size(); j++) {
            vals.insert(cronologia[i][j]);
        }
        setValues.push_back(vals);
    }
    map<string, int> record;
    for (size_t w = 0; w < cronologia.size(); w++) {
        for (size_t i = 0; i < cronologia[w].size(); i++) {
            for (size_t j = w + 1; j < cronologia[w].size(); j++) {
                set<string>::iterator search = setValues[j].find(cronologia[w][i]);
                map<string, int>::iterator searchDic = record.find(cronologia[w][i]);
                if (search != setValues[j].end() && searchDic == record.end()) {
                    record[cronologia[w][i]] = w;
                } else if (search == setValues[j].end() && searchDic != record.end()) {
                    record[cronologia[w][i]] = -1;
                }
            }
        }
    }
    for (auto &x : record) {
        if (x.second != -1) {
            cout << "El elemento " << x.first << " ha estado en el top apartir del " << program.diaRelativo(x.second, false) << endl;
        }
    }

    cout << endl;
    cout << endl;

    return (0);
}

int main() {
    terminal();
}
