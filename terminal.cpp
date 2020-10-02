/* 
programa para probar la funcionalidad de ComsProgram
javier alejandro martinez noe
27/9/20
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept> 
#include <sstream>
#include "Master.hpp"
#include "CsvReader.hpp"
using namespace std;

//funcion para imprimir el registro
template<class T>
void print(Master<T> &object){
    int resp;
    cout<<endl;
    cout<<"Espesifica cuantas filas quieres imprimir, 0 = All: "<<endl;
    cin >> resp;
    object.Display(resp);
    cout<<endl;
}
//funcion para añadir regitros
template<class T>
Master<T> addRegistro(vector<vector<T>> &_registros, Master<T> &_program){
    for(size_t i = 0; i < _registros.size();i++){
        _program.addRegister(_registros[i]);
    }
    return(_program);
}
//funcion para controlar el programa
template<class T>
int terminal(T a){
    Master<string> program;
    CSVReader reader("equipo5.csv");
    vector<vector<string> > regitros = reader.getData();
    program = addRegistro(regitros, program);

    cout<<"display head(5)"<<endl;
    program.Display(5);
    cout<<endl;
    cout<< "En total hay: " <<program.numeroDeRegistros()<< " Registros" <<endl;
    cout<<endl;
    int sorter;
    cout << "Do you want to sort? naturally the list is sorted but if you want to sort it will take time. 0: no, 1: yes" <<endl;
    cin >> sorter;
    bool sort;
    if(sorter == 1){
        sort = true;
    }
    else{
        sort = false;
    }
    if(sort){
        cout<<"sorting by time"<<endl;
        program.sortByTime();
        cout<<"display head(5)"<<endl;
        program.Display(5);
        cout<<endl;
    }
    cout<<endl;
    string diaRelativo = to_string(program.diaRelativo(2, sort));
    cout << "El segundo dia es: " << diaRelativo <<endl;
    int numRegistros = program.busquedaDia(diaRelativo, false);
    cout << "El segundo dia hay: " << numRegistros << " registros" <<endl;
    cout<<endl;
    int num = program.busquedaMinpuerto("1000", false);
    if(num != 0){
        cout<<"Si hay un puerto de destino menor a 1000"<<endl;
        cout <<"Hay " << num << " en el regitro con un puerto de destino menor a 1000"<<endl;
    }
    int print;
    cout << "Do you want to print the registers under 1000 in the port. 0: no, 1: yes" <<endl;
    cin >> print;
    cout<<endl;
    if(print == 1){
        program.busquedaMinpuerto("1000", true);
    }
    vector<string> names = {"jeffrey", "betty", "katherine", "scott", "benjamin"};
    for(size_t i = 0; i < names.size(); i++){
        int busquedaNames = program.busquedaOrdenador(names[i], false);
        if(busquedaNames != 0){
            cout << "En el registro " << names[i] << " si tiene una compu" << endl;
        }
    }
    cout<<endl;
    vector<string> servicios = {"gmail", "hotmail", "outlook", "prontonmail"};
    for(size_t i = 0; i < servicios.size(); i++){
        int busquedaOrdenadores = program.busquedaServicio(servicios[i], false);
        if(busquedaOrdenadores != 0){
            cout << "En el registro se ocupa el servicio: " << servicios[i] << endl;
        }
    }
    cout<<endl;
    int reto = program.busquedaUsuarioCompleto("server.reto.com", false);
    if(reto != 0){
        cout<< "si hay un usuario llamado server.reto.com en el registo" <<endl;
    }
    else{
        cout<< "No hay un usuario llamado server.reto.com en el registo" <<endl;
    }
    cout<<endl;
    cout << "la Ip local de la red es: " << program.conseguirIpLocal() <<endl;
    cout<<endl;
    vector<string> serviciosTodos = program.GetAllServices();
    cout<< "Se estan Ocupando los servicios:"<<endl;
    for(size_t i = 0; i < serviciosTodos.size(); i++){
        cout << serviciosTodos[i] << ", ";
    }
    cout<<endl;
    cout<<endl;
    vector<string> puertosActivos = program.getActivePortsDestiny();
    cout<< "Puertos de destino activos:"<<endl;
    for(size_t i = 0; i < puertosActivos.size(); i++){
        cout << puertosActivos[i] << ", ";
    }
    cout<<endl;
    cout<<endl;
    return(0);
    
}

int main(){
    terminal(1);
}  
