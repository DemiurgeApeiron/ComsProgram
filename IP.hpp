#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "DataBase.hpp"
using namespace std;
#pragma once

template <class T>
class IP: public DataBase<T>{
protected:
    T localIp;
    T userIP;
    T fullIP;
public:
    IP(T &IP);
    ~IP();
    string getLocalIp(){return localIp;}
    string getUserIP(){return userIP;}
    T display(){return fullIP;}
};
template <class T>
IP<T>::IP(T &IP){
    this->fullIP = IP;
    if(fullIP == "-"){
        this->localIp="0";
        this->userIP="0";
    }
    else{
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

    
}
template <class T>
IP<T>::~IP(){
}
