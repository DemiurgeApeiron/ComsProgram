#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
#pragma onece;

template <class T>
class IP{
protected:
    T localIp;
    T userIP;
public:
    IP(T &IP);
    ~IP();
    string getLocalIp(){return localIp;}
    string getUserIP(){return userIP;}
};
template <class T>
IP<T>::IP(T &IP){
    vector <string> valores;
    stringstream check1(IP); 
    
    string intermediate; 

    while(getline(check1, intermediate, '.')) 
    { 
        valores.push_back(intermediate); 
    } 

    localIp = valores[0] + "." + valores[1] + "." + valores[2];
    userIP = valores[valores.size()-1];
}
template <class T>
IP<T>::~IP(){
}
