#include <iostream>
#include <vector>
#include "Puerto.hpp"
#include "HostName.hpp"
#include "IP.hpp"
using namespace std;
#pragma onece;

template <class T>
class Master{
protected:
    vector<vector <T> > lista;
public:
    Master();
    void addRegister(std::vector<T> &_lista);
    vector<T> sort(bool (*compare)(T &a, T B));
    int numeroDeRegistros(){return(lista.size());}
    ~Master();
};
template <class T>
Master<T>::Master(){}

template <class T>
void Master<T>::addRegister(vector<T> &_lista){
    vector<T> v = {new IP(_lista[1]), new Puerto(_lista[2]), new HostName(_lista[3]), new IP(_lista[4]), new Puerto(_lista[5]), new HostName(_lista[6])}
    lista.push_back(v)
}
template <class T>
Master<T>::~Master(){
}

template <class T>
vector<T> Master<T>:: sort(bool (*compare)(T &a, T B)){
    for(size_t i = 0; i < arr.size()-1;i++){
        size_t min = i;
        for(size_t j = i+1; j < arr.size();j++){
            if((8*compare)(arr[j],arr[min])){
                min = j
            }
        }
        T temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}


