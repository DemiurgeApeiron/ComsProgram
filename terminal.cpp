#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept> 
#include <sstream>
#include "Master.hpp"
#include "CsvReader.hpp"
using namespace std;

//codigo obtenido de https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/#reading-from-csv
vector<vector<string>> readCsv(string filename){
    vector<vector<string>> result;
    ifstream myFile(filename);

    if(!myFile.is_open()) throw runtime_error("Could not open file");

    string line, colname;
    string val;

    if(myFile.good()){
        getline(myFile, line);
        stringstream ss(line);
        while(getline(ss, colname, ',')){
            result.push_back({vector<string> {}});
        }
    }
    while(getline(myFile, line))
    {
        stringstream ss(line);
        int colIdx = 0;
        while(ss >> val){
            result.at(colIdx).push_back(val);
            if(ss.peek() == ',') ss.ignore();
            colIdx++;
        }
    }
    myFile.close();

    return result;
}

template<class T>
void print(Master<T> &object){
    int resp;
    cout<<endl;
    cout<<"Espesifica cuantas filas quieres imprimir, 0 = All: "<<endl;
    cin >> resp;
    object.Display(resp);
    cout<<endl;
}
template<class T>
Master<T> addRegistro(vector<vector<T>> &_registros, Master<T> &_program){
    for(size_t i = 0; i < _registros.size();i++){
        _program.addRegister(_registros[i]);
    }
    return(_program);
}
template<class T>
int terminal(T a){
    Master<string> program;
    CSVReader reader("equipo5.csv");
    vector<vector<string> > regitros = reader.getData();
    string var = "11";
    int ind = regitros.size()*3/4;
    regitros = vector<vector<string>>(regitros.begin() , regitros.end()-(ind));

    program = addRegistro(regitros, program);

    cout<<"display head(5)"<<endl;
    program.Display(5);
    cout<<endl;
    cout<< "En total hay: " <<program.numeroDeRegistros()<< " Registros" <<endl;
    cout<<endl;
    cout<<"sorting by time"<<endl;
    program.sortByTime();
    cout<<"display head(5)"<<endl;
    program.Display(5);
    cout<<endl;
    string diaRelativo = to_string(program.diaRelativo(2));
    cout << "El segundo dia es: " << diaRelativo <<endl;
    int numRegistros = program.busquedaDia(diaRelativo, false);
    cout << "El segundo dia hay: " << numRegistros << " registros" <<endl;
    cout << "son:  "<<endl;
    program.busquedaDia(diaRelativo, false);
    cout<<endl;
    int num = program.busquedaMinpuerto("1000", false);
    if(num != 0){
        cout<<"Si hay un puerto de destino menor a 1000"<<endl;
    }
    cout<<endl;
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
    return(0);
    
}

int main(){
    terminal(1);
}  
