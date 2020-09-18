#include <iostream>
#include <vector>
using namespace std;
#pragma onece;

template <class T>
class HostName{
protected:
    T fullName;
    T name;
public:
    HostName(T &HostName);
    ~HostName();
    T getFullName(){return fullName;}
    T getName(){return name;}
};
template <class T>
HostName<T>::HostName(T &HostName){
    this-> fullName = HostName;

    vector <T> valores;
    stringstream check1(IP); 
    string intermediate; 
    while(getline(check1, intermediate, '.')) 
    { 
        valores.push_back(intermediate); 
    }
    this-> name = valores[0];
}
template <class T>
HostName<T>::~HostName(){
}
