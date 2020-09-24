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
    cout<<"h1"<<endl;
    _program.Display(5);
    _program.sortByTime();
    cout<<"h2"<<endl;
    _program.Display(5);
    cout<<endl;
    string diaRelativo = to_string(_program.diaRelativo(2));
    cout << "el segundo dia es: " << diaRelativo <<endl;
    _program.busquedaDia(diaRelativo, false);
    cout<< _program.numeroDeRegistros()<<endl;
    int num = _program.busquedaMinpuerto("1000", false);
    if(num != 0){
        cout<<"si hay un puerto de destino menor a 1000"<<endl;
    }
    return(_program);
}
template<class T>
int terminal(T a){
    Master<string> program;
    CSVReader reader("equipo5.csv");
    vector<vector<string> > regitros = reader.getData();
    string var = "11";
    int ind = regitros.size()-5000;
    regitros = vector<vector<string>>(regitros.begin() , regitros.end()-(ind));

    program = addRegistro(regitros, program);
    /*cout<< "h1"<<endl;
    cout << program.numeroDeRegistros() <<endl;
    program.Display(0);
    print(program);
    program.sortByTime();*/
}

int main(){
    terminal(1);
}  
