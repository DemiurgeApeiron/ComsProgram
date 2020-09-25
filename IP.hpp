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
    IP()=default;
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
        if(valores.size() == 4){
            this->localIp = valores[0] + "." + valores[1] + "." + valores[2];
            this->userIP = valores[valores.size()-1];
        }
        else{
            this->localIp= "0";
            this->userIP= "0";
        }
        
    }

    
}
template <class T>
IP<T>::~IP(){
}
